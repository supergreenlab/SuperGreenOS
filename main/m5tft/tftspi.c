/*
 *  Author: LoBo (loboris@gmail.com, loboris.github)
 *
 *  Module supporting SPI TFT displays based on ILI9341 & ILI9488 controllers
 * 
 * HIGH SPEED LOW LEVEL DISPLAY FUNCTIONS
 * USING DIRECT or DMA SPI TRANSFER MODEs
 *
 */

#include <string.h>
#include "tftspi.h"
#include "esp_system.h"
#include "freertos/task.h"
#include "esp_heap_caps.h"
#include "soc/spi_reg.h"
#include "../core/log/log.h"


// ====================================================
// ==== Global variables, default values ==============

uint32_t max_rdclock = 8000000;

// Default display dimensions
int _width = DEFAULT_TFT_DISPLAY_WIDTH;
int _height = DEFAULT_TFT_DISPLAY_HEIGHT;

// Spi device handles for display
spi_lobo_device_handle_t disp_spi = NULL;

// ====================================================


static color_t *trans_cline = NULL;
static uint8_t _dma_sending = 0;

// RGB to GRAYSCALE constants
// 0.2989  0.5870  0.1140
#define GS_FACT_R 0.2989
#define GS_FACT_G 0.4870
#define GS_FACT_B 0.2140

// ==== Functions =====================

//------------------------------------------------------
esp_err_t IRAM_ATTR wait_trans_finish(uint8_t free_line)
{
  // Wait for SPI bus ready
  while (disp_spi->host->hw->cmd.usr);
  if ((free_line) && (trans_cline)) {
    free(trans_cline);
    trans_cline = NULL;
  }
  if (_dma_sending) {
    //Tell common code DMA workaround that our DMA channel is idle. If needed, the code will do a DMA reset.
    if (disp_spi->host->dma_chan) spi_lobo_dmaworkaround_idle(disp_spi->host->dma_chan);

    // Reset DMA
    disp_spi->host->hw->dma_conf.val |= SPI_OUT_RST|SPI_IN_RST|SPI_AHBM_RST|SPI_AHBM_FIFO_RST;
    disp_spi->host->hw->dma_out_link.start=0;
    disp_spi->host->hw->dma_in_link.start=0;
    disp_spi->host->hw->dma_conf.val &= ~(SPI_OUT_RST|SPI_IN_RST|SPI_AHBM_RST|SPI_AHBM_FIFO_RST);
    disp_spi->host->hw->dma_conf.out_data_burst_en=1;
    _dma_sending = 0;
  }
  return ESP_OK;
}

//-------------------------------
esp_err_t IRAM_ATTR disp_select()
{
  wait_trans_finish(1);
  return spi_lobo_device_select(disp_spi, 0);
}

//---------------------------------
esp_err_t IRAM_ATTR disp_deselect()
{
  wait_trans_finish(1);
  return spi_lobo_device_deselect(disp_spi);
}

//---------------------------------------------------------------------------------------------------
static void IRAM_ATTR _spi_transfer_start(spi_lobo_device_handle_t spi_dev, int wrbits, int rdbits) {
  // Load send buffer
  spi_dev->host->hw->user.usr_mosi_highpart = 0;
  spi_dev->host->hw->mosi_dlen.usr_mosi_dbitlen = wrbits-1;
  spi_dev->host->hw->user.usr_mosi = 1;
  if (rdbits) {
    spi_dev->host->hw->miso_dlen.usr_miso_dbitlen = rdbits;
    spi_dev->host->hw->user.usr_miso = 1;
  }
  else {
    spi_dev->host->hw->miso_dlen.usr_miso_dbitlen = 0;
    spi_dev->host->hw->user.usr_miso = 0;
  }
  // Start transfer
  spi_dev->host->hw->cmd.usr = 1;
  // Wait for SPI bus ready
  while (spi_dev->host->hw->cmd.usr);
}

// Send 1 byte display command, display must be selected
//------------------------------------------------
void IRAM_ATTR disp_spi_transfer_cmd(int8_t cmd) {
  // Wait for SPI bus ready
  while (disp_spi->host->hw->cmd.usr);

  // Set DC to 0 (command mode);
  gpio_set_level(PIN_NUM_DC, 0);

  disp_spi->host->hw->data_buf[0] = (uint32_t)cmd;
  _spi_transfer_start(disp_spi, 8, 0);
}

// Send command with data to display, display must be selected
//----------------------------------------------------------------------------------
void IRAM_ATTR disp_spi_transfer_cmd_data(int8_t cmd, uint8_t *data, uint32_t len) {
  // Wait for SPI bus ready
  while (disp_spi->host->hw->cmd.usr);

  // Set DC to 0 (command mode);
  gpio_set_level(PIN_NUM_DC, 0);

  disp_spi->host->hw->data_buf[0] = (uint32_t)cmd;
  _spi_transfer_start(disp_spi, 8, 0);

  if ((len == 0) || (data == NULL)) return;

  // Set DC to 1 (data mode);
  gpio_set_level(PIN_NUM_DC, 1);

  uint8_t idx=0, bidx=0;
  uint32_t bits=0;
  uint32_t count=0;
  uint32_t wd = 0;
  while (count < len) {
    // get data byte from buffer
    wd |= (uint32_t)data[count] << bidx;
    count++;
    bits += 8;
    bidx += 8;
    if (count == len) {
      disp_spi->host->hw->data_buf[idx] = wd;
      break;
    }
    if (bidx == 32) {
      disp_spi->host->hw->data_buf[idx] = wd;
      idx++;
      bidx = 0;
      wd = 0;
    }
    if (idx == 16) {
      // SPI buffer full, send data
      _spi_transfer_start(disp_spi, bits, 0);

      bits = 0;
      idx = 0;
      bidx = 0;
    }
  }
  if (bits > 0) _spi_transfer_start(disp_spi, bits, 0);
}

// Set the address window for display write & read commands, display must be selected
//---------------------------------------------------------------------------------------------------
static void IRAM_ATTR disp_spi_transfer_addrwin(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2) {
  uint32_t wd;

  taskDISABLE_INTERRUPTS();
  // Wait for SPI bus ready
  while (disp_spi->host->hw->cmd.usr);
  gpio_set_level(PIN_NUM_DC, 0);

  disp_spi->host->hw->data_buf[0] = (uint32_t)TFT_CASET;
  disp_spi->host->hw->user.usr_mosi_highpart = 0;
  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = 7;
  disp_spi->host->hw->user.usr_mosi = 1;
  disp_spi->host->hw->miso_dlen.usr_miso_dbitlen = 0;
  disp_spi->host->hw->user.usr_miso = 0;

  disp_spi->host->hw->cmd.usr = 1; // Start transfer

  wd = (uint32_t)(x1>>8);
  wd |= (uint32_t)(x1&0xff) << 8;
  wd |= (uint32_t)(x2>>8) << 16;
  wd |= (uint32_t)(x2&0xff) << 24;

  while (disp_spi->host->hw->cmd.usr); // wait transfer end
  gpio_set_level(PIN_NUM_DC, 1);
  disp_spi->host->hw->data_buf[0] = wd;
  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = 31;
  disp_spi->host->hw->cmd.usr = 1; // Start transfer

  while (disp_spi->host->hw->cmd.usr);
  gpio_set_level(PIN_NUM_DC, 0);
  disp_spi->host->hw->data_buf[0] = (uint32_t)TFT_PASET;
  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = 7;
  disp_spi->host->hw->cmd.usr = 1; // Start transfer

  wd = (uint32_t)(y1>>8);
  wd |= (uint32_t)(y1&0xff) << 8;
  wd |= (uint32_t)(y2>>8) << 16;
  wd |= (uint32_t)(y2&0xff) << 24;

  while (disp_spi->host->hw->cmd.usr);
  gpio_set_level(PIN_NUM_DC, 1);

  disp_spi->host->hw->data_buf[0] = wd;
  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = 31;
  disp_spi->host->hw->cmd.usr = 1; // Start transfer
  while (disp_spi->host->hw->cmd.usr);
  taskENABLE_INTERRUPTS();
}

//-----------------------------------------------------------
static void IRAM_ATTR _dma_send(uint8_t *data, uint32_t size)
{
  //Fill DMA descriptors
  
  spi_lobo_dmaworkaround_transfer_active(disp_spi->host->dma_chan); //mark channel as active
  spi_lobo_setup_dma_desc_links(disp_spi->host->dmadesc_tx, size, data, false);
  disp_spi->host->hw->user.usr_mosi_highpart=0;
  disp_spi->host->hw->dma_out_link.addr=(int)(&disp_spi->host->dmadesc_tx[0]) & 0xFFFFF;
  disp_spi->host->hw->dma_out_link.start=1;
  disp_spi->host->hw->user.usr_mosi_highpart=0;

  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = (size * 8) - 1;

  _dma_sending = 1;
  // Start transfer
  disp_spi->host->hw->cmd.usr = 1;
}

//---------------------------------------------------------------------------
static void IRAM_ATTR _direct_send(color_t *color, uint32_t len, uint8_t rep)
{
  uint32_t cidx = 0;	// color buffer index
  uint32_t wd = 0;
  int idx = 0;
  int bits = 0;
  int wbits = 0;

  taskDISABLE_INTERRUPTS();
  color_t _color = color[0];

  while (len) {
    // ** Get color data from color buffer **
    if (rep == 0) {
      _color = color[cidx];
    }

    wd |= (uint32_t)_color.r << wbits;
    wbits += 8;
    if (wbits == 32) {
      bits += wbits;
      wbits = 0;
      disp_spi->host->hw->data_buf[idx++] = wd;
      wd = 0;
    }
    wd |= (uint32_t)_color.g << wbits;
    wbits += 8;
    if (wbits == 32) {
      bits += wbits;
      wbits = 0;
      disp_spi->host->hw->data_buf[idx++] = wd;
      wd = 0;
    }
    wd |= (uint32_t)_color.b << wbits;
    wbits += 8;
    if (wbits == 32) {
      bits += wbits;
      wbits = 0;
      disp_spi->host->hw->data_buf[idx++] = wd;
      wd = 0;
    }
    len--;					// Decrement colors counter
    if (rep == 0) cidx++;	// if not repeating color, increment color buffer index
  }
  if (bits) {
    while (disp_spi->host->hw->cmd.usr);						// Wait for SPI bus ready
    disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = bits-1;	// set number of bits to be sent
    disp_spi->host->hw->cmd.usr = 1;							// Start transfer
  }
  taskENABLE_INTERRUPTS();
}

// ================================================================
// === Main function to send data to display ======================
// If  rep==true:  repeat sending color data to display 'len' times
// If rep==false:  send 'len' color data from color buffer to display
// ** Device must already be selected and address window set **
// ================================================================
//----------------------------------------------------------------------------------------------
static void IRAM_ATTR _TFT_pushColorRep(color_t *color, uint32_t len, uint8_t rep, uint8_t wait)
{
  if (len == 0) return;
  if (!(disp_spi->cfg.flags & LB_SPI_DEVICE_HALFDUPLEX)) return;

  // Send RAM WRITE command
  gpio_set_level(PIN_NUM_DC, 0);
  disp_spi->host->hw->data_buf[0] = (uint32_t)TFT_RAMWR;
  disp_spi->host->hw->mosi_dlen.usr_mosi_dbitlen = 7;
  disp_spi->host->hw->cmd.usr = 1;		// Start transfer
  while (disp_spi->host->hw->cmd.usr);	// Wait for SPI bus ready

  gpio_set_level(PIN_NUM_DC, 1);								// Set DC to 1 (data mode);

  if ((len*24) <= 512) {

    _direct_send(color, len, rep);

  }
  else if (rep == 0)  {
    // ==== use DMA transfer ====
    // ** Prepare data
    _dma_send((uint8_t *)color, len*3);
  }
  else {
    // ==== Repeat color, more than 512 bits total ====

    color_t _color;
    uint32_t buf_colors;
    int buf_bytes, to_send;

    /*
       to_send = len;
       while (to_send > 0) {
       wait_trans_finish(0);
       _direct_send(color, ((to_send > 21) ? 21 : to_send), rep);
       to_send -= 21;
       }
       */

    buf_colors = ((len > (_width*2)) ? (_width*2) : len);
    buf_bytes = buf_colors * 3;

    // Prepare color buffer of maximum 2 color lines
    trans_cline = heap_caps_malloc(buf_bytes, MALLOC_CAP_DMA);
    if (trans_cline == NULL) return;

    // Prepare fill color
    _color = color[0];

    // Fill color buffer with fill color
    for (uint32_t i=0; i<buf_colors; i++) {
      trans_cline[i] = _color;
    }

    // Send 'len' colors
    to_send = len;
    while (to_send > 0) {
      wait_trans_finish(0);
      _dma_send((uint8_t *)trans_cline, ((to_send > buf_colors) ? buf_bytes : (to_send*3)));
      to_send -= buf_colors;
    }
  }

  if (wait) wait_trans_finish(1);
}

// Write 'len' color data to TFT 'window' (x1,y2),(x2,y2) from given buffer
// ** Device must already be selected **
//-----------------------------------------------------------------------------------
void IRAM_ATTR send_data(int x1, int y1, int x2, int y2, uint32_t len, color_t *buf)
{
  if (disp_select() != ESP_OK) return;
  // ** Send address window **
  x1+=1; y1+=26; x2+=1; y2+=26; // FIXME This hack fixes positioning issue on M5StickC

  disp_spi_transfer_addrwin(x1, x2, y1, y2);
  _TFT_pushColorRep(buf, len, 0, 0);
  disp_deselect();
}

//---------------------------------------------------------------------------
// Companion code to the initialization table.
// Reads and issues a series of LCD commands stored in byte array
//---------------------------------------------------------------------------
static void commandList(spi_lobo_device_handle_t spi, const uint8_t *addr) {
  uint8_t  numCommands, numArgs, cmd;
  uint16_t ms;

  numCommands = *addr++;				// Number of commands to follow
  while(numCommands--) {				// For each command...
    cmd = *addr++;						// save command
    numArgs  = *addr++;					// Number of args to follow
    ms       = numArgs & TFT_CMD_DELAY;	// If high bit set, delay follows args
    numArgs &= ~TFT_CMD_DELAY;			// Mask out delay bit

    disp_spi_transfer_cmd_data(cmd, (uint8_t *)addr, numArgs);

    addr += numArgs;

    if(ms) {
      ms = *addr++;              // Read post-command delay time (ms)
      if(ms == 255) ms = 500;    // If 255, delay for 500 ms
      vTaskDelay(ms / portTICK_RATE_MS);
    }
  }
}

//==================================
void _tft_setRotation(uint8_t rot) {
  uint8_t rotation = rot & 3; // can't be higher than 3
  uint8_t send = 1;
  uint8_t madctl = 0;
  uint16_t tmp;

  if ((rotation & 1)) {
    // in landscape modes must be width > height
    if (_width < _height) {
      tmp = _width;
      _width  = _height;
      _height = tmp;
    }
  }
  else {
    // in portrait modes must be width < height
    if (_width > _height) {
      tmp = _width;
      _width  = _height;
      _height = tmp;
    }
  }
#if TFT_INVERT_ROTATION
  switch (rotation) {
    case PORTRAIT:
      madctl = (MADCTL_MV | TFT_RGB_BGR);
      break;
    case LANDSCAPE:
      madctl = (MADCTL_MX | TFT_RGB_BGR);
      break;
    case PORTRAIT_FLIP:
      madctl = (MADCTL_MV | TFT_RGB_BGR);
      break;
    case LANDSCAPE_FLIP:
      madctl = (MADCTL_MY | TFT_RGB_BGR);
      break;
  }
#elif TFT_INVERT_ROTATION1
  switch (rotation) {
    case PORTRAIT:
      madctl = (MADCTL_MY | MADCTL_MX | TFT_RGB_BGR); // TFT_MAD_MH missing?? see m5stickc arduino code https://github.com/yishii/M5StickC/blob/01e2aebc95def57aab3fef7c64956c3ca702bad7/src/utility/ST7735_Rotation.h
      break;
    case LANDSCAPE:
      madctl = (MADCTL_MY | MADCTL_MV | TFT_RGB_BGR);
      break;
    case PORTRAIT_FLIP:
      madctl = (TFT_RGB_BGR);
      break;
    case LANDSCAPE_FLIP:
      madctl = (MADCTL_MX | MADCTL_MV | TFT_RGB_BGR);
      break;
  }
#elif TFT_INVERT_ROTATION2
  switch (rotation) {
    case PORTRAIT:
      madctl = (MADCTL_MX | MADCTL_MV | TFT_RGB_BGR);
      break;
    case LANDSCAPE:
      madctl = (TFT_RGB_BGR);
      break;
    case PORTRAIT_FLIP:
      madctl = (MADCTL_MY | MADCTL_MV | TFT_RGB_BGR);
      break;
    case LANDSCAPE_FLIP:
      madctl = (MADCTL_MY | MADCTL_MX | TFT_RGB_BGR);
      break;
  }
#else
  switch (rotation) {
    case PORTRAIT:
      madctl = (MADCTL_MX | TFT_RGB_BGR);
      break;
    case LANDSCAPE:
      madctl = (MADCTL_MV | TFT_RGB_BGR);
      break;
    case PORTRAIT_FLIP:
      madctl = (MADCTL_MY | TFT_RGB_BGR);
      break;
    case LANDSCAPE_FLIP:
      madctl = (MADCTL_MX | MADCTL_MY | MADCTL_MV | TFT_RGB_BGR);
      break;
  }
#endif
  if (send) {
    if (disp_select() == ESP_OK) {
      disp_spi_transfer_cmd_data(TFT_MADCTL, &madctl, 1);
      disp_deselect();
    }
  }

}

void TFT_setRotation(uint8_t rot) {
	if (rot > 3) {
		uint8_t madctl = (rot & 0xF8); // for testing, manually set MADCTL register
		if (disp_select() == ESP_OK) {
			disp_spi_transfer_cmd_data(TFT_MADCTL, &madctl, 1);
			disp_deselect();
		}
	}
	else {
		_tft_setRotation(rot);
	}
}

//=================
void TFT_PinsInit()
{
  gpio_pad_select_gpio(PIN_NUM_CS); // Route all used pins to GPIO control
  gpio_set_direction(PIN_NUM_CS, GPIO_MODE_OUTPUT);
  gpio_set_level(PIN_NUM_CS, 0);

  gpio_pad_select_gpio(PIN_NUM_MOSI); // Route all used pins to GPIO control
  gpio_set_direction(PIN_NUM_MOSI, GPIO_MODE_OUTPUT);

  gpio_pad_select_gpio(PIN_NUM_CLK); // Route all used pins to GPIO control
  gpio_set_direction(PIN_NUM_CLK, GPIO_MODE_OUTPUT);

  gpio_pad_select_gpio(PIN_NUM_DC); // Route all used pins to GPIO control
  gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
  gpio_set_level(PIN_NUM_DC, 0);

  gpio_pad_select_gpio(PIN_NUM_RST);
  gpio_set_direction(PIN_NUM_RST, GPIO_MODE_OUTPUT);
  gpio_set_level(PIN_NUM_RST, 0);
}

// Initialize the display
// ====================
void TFT_display_init()
{
  esp_err_t ret;

  //Reset the display
  gpio_set_level(PIN_NUM_RST, 0);
  vTaskDelay(100 / portTICK_RATE_MS);
  gpio_set_level(PIN_NUM_RST, 1);

  vTaskDelay(150 / portTICK_RATE_MS);

  ret = disp_select();
  assert(ret==ESP_OK);

  commandList(disp_spi, Rcmd1);
  commandList(disp_spi, Rcmd2green);
  commandList(disp_spi, Rcmd3);

  ret = disp_deselect();
  assert(ret==ESP_OK);
}
