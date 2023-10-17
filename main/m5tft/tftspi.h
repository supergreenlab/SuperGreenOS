/*
 * 
 * HIGH SPEED LOW LEVEL DISPLAY FUNCTIONS USING DIRECT TRANSFER MODE
 *
 */

#ifndef _TFTSPI_H_
#define _TFTSPI_H_

#include "tftspi.h"
#include "spi_master_lobo.h"
#include "sdkconfig.h"

#ifdef __cplusplus
extern "C" {
#endif

  // === Screen orientation constants ===
#define PORTRAIT  0
#define LANDSCAPE 1
#define PORTRAIT_FLIP 2
#define LANDSCAPE_FLIP  3

  // ** Set the correct configuration for M5StickC TFT
  // ---------------------------------------------------------
#define DEFAULT_TFT_DISPLAY_WIDTH   80
#define DEFAULT_TFT_DISPLAY_HEIGHT  160
#define DISP_COLOR_BITS_24          0x66
#define DEFAULT_GAMMA_CURVE         0
#define DEFAULT_SPI_CLOCK           26000000
#define TFT_INVERT_ROTATION         0
#define TFT_INVERT_ROTATION1        1
#define TFT_INVERT_ROTATION2        1
#define TFT_RGB_BGR                 0x08

#define PIN_NUM_MISO -1   // SPI MISO
#define PIN_NUM_MOSI 15   // SPI MOSI
#define PIN_NUM_CLK  13   // SPI CLOCK pin
#define PIN_NUM_CS   5    // Display CS pin
#define PIN_NUM_DC   23   // Display command/data pin

#define PIN_NUM_RST  18   // GPIO used for RESET control (#16)


  // ##############################################################
  // #### Global variables                                     ####
  // ##############################################################

  // ==== Converts colors to grayscale if 1 =======================
  extern uint8_t gray_scale;

  // ==== Spi clock for reading data from display memory in Hz ====
  extern uint32_t max_rdclock;

  // ==== Display dimensions in pixels ============================
  extern int _width;
  extern int _height;

  // ==== Spi device handles for display =========
  extern spi_lobo_device_handle_t disp_spi;

  // ##############################################################

  // 24-bit color type structure
  typedef struct __attribute__((__packed__)) {
    //typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  } color_t ;

  // ==== Display commands constants ====
#define TFT_INVOFF     0x20
#define TFT_INVONN     0x21
#define TFT_DISPOFF    0x28
#define TFT_DISPON     0x29
#define TFT_MADCTL     0x36
#define TFT_PTLAR      0x30
#define TFT_ENTRYM     0xB7

#define TFT_CMD_NOP     0x00
#define TFT_CMD_SWRESET   0x01
#define TFT_CMD_RDDID   0x04
#define TFT_CMD_RDDST   0x09

#define TFT_CMD_SLPIN   0x10
#define TFT_CMD_SLPOUT    0x11
#define TFT_CMD_PTLON   0x12
#define TFT_CMD_NORON   0x13

#define TFT_CMD_RDMODE    0x0A
#define TFT_CMD_RDMADCTL  0x0B
#define TFT_CMD_RDPIXFMT  0x0C
#define TFT_CMD_RDIMGFMT  0x0D
#define TFT_CMD_RDSELFDIAG  0x0F

#define TFT_CMD_GAMMASET  0x26

#define TFT_CMD_FRMCTR1   0xB1
#define TFT_CMD_FRMCTR2   0xB2
#define TFT_CMD_FRMCTR3   0xB3
#define TFT_CMD_INVCTR    0xB4
#define TFT_CMD_DFUNCTR   0xB6

#define TFT_CMD_PWCTR1    0xC0
#define TFT_CMD_PWCTR2    0xC1
#define TFT_CMD_PWCTR3    0xC2
#define TFT_CMD_PWCTR4    0xC3
#define TFT_CMD_PWCTR5    0xC4
#define TFT_CMD_VMCTR1    0xC5
#define TFT_CMD_VMCTR2    0xC7

#define TFT_CMD_RDID1   0xDA
#define TFT_CMD_RDID2   0xDB
#define TFT_CMD_RDID3   0xDC
#define TFT_CMD_RDID4   0xDD

#define TFT_CMD_GMCTRP1   0xE0
#define TFT_CMD_GMCTRN1   0xE1

#define TFT_CMD_POWERA    0xCB
#define TFT_CMD_POWERB    0xCF
#define TFT_CMD_POWER_SEQ 0xED
#define TFT_CMD_DTCA    0xE8
#define TFT_CMD_DTCB    0xEA
#define TFT_CMD_PRC     0xF7
#define TFT_CMD_3GAMMA_EN 0xF2

#define ST_CMD_VCOMS       0xBB
#define ST_CMD_FRCTRL2      0xC6
#define ST_CMD_PWCTR1   0xD0

#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR  0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1  0xC0
#define ST7735_PWCTR2  0xC1
#define ST7735_PWCTR3  0xC2
#define ST7735_PWCTR4  0xC3
#define ST7735_PWCTR5  0xC4
#define ST7735_VMCTR1  0xC5

#define ST7735_RDID1   0xDA
#define ST7735_RDID2   0xDB
#define ST7735_RDID3   0xDC
#define ST7735_RDID4   0xDD
#define ST7735_NOP     0x00
#define ST7735_SWRESET 0x01
#define ST7735_RDDID   0x04
#define ST7735_RDDST   0x09

#define ST7735_SLPIN   0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON   0x12
#define ST7735_NORON   0x13
#define ST7735_PWCTR6  0xFC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define MADCTL_MY  0x80
#define MADCTL_MX  0x40
#define MADCTL_MV  0x20
#define MADCTL_ML  0x10
#define MADCTL_MH  0x04

#define TFT_CASET   0x2A
#define TFT_PASET   0x2B
#define TFT_RAMWR   0x2C
#define TFT_RAMRD   0x2E
#define TFT_CMD_PIXFMT  0x3A

#define TFT_CMD_DELAY 0x80

  static const uint8_t  Rcmd1[] = {
    16,
    ST7735_SWRESET, TFT_CMD_DELAY,  //  1: Software reset, 0 args, w/delay
    150,             //     150 ms delay
    ST7735_SLPOUT, TFT_CMD_DELAY,  //  2: Out of sleep mode, 0 args, w/delay
    120,             //     500 ms delay
    ST7735_FRMCTR1,
    3,  //  3: Frame rate ctrl - normal mode, 3 args:
    0x05,
    0x3C,
    0x3C,  //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR2,
    3,  //  4: Frame rate control - idle mode, 3 args:
    0x05,
    0x3C,
    0x3C,  //     Rate = fosc/(1x2+40) * (LINE+2C+2D)
    ST7735_FRMCTR3,
    6,  //  5: Frame rate ctrl - partial mode, 6 args:
    0x05,
    0x3C,
    0x3C,  //     Dot inversion mode
    0x05,
    0x3C,
    0x3C,  //     Line inversion mode
    ST7735_INVCTR,
    2,  //  6: Display inversion ctrl, 1 arg, no delay:
    0x03,
    0x02,  //     No inversion
    ST7735_PWCTR1,
    3,  //  7: Power control, 3 args, no delay:
    0xA4,
    0x04,  //     -4.6V
    0x84,  //     AUTO mode
    ST7735_PWCTR2,
    1,     //  8: Power control, 1 arg, no delay:
    0xC5,  //     VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD
    ST7735_PWCTR3,
    2,     //  9: Power control, 2 args, no delay:
    0x0D,  //     Opamp current small
    0x00,  //     Boost frequency
    ST7735_PWCTR4,
    2,     // 10: Power control, 2 args, no delay:
    0x8D,  //     BCLK/2, Opamp current small & Medium low
    0x6A,
    ST7735_PWCTR5,
    2,  // 11: Power control, 2 args, no delay:
    0x8D,
    0xEE,
    ST7735_VMCTR1,
    1,  // 12: Power control, 1 arg, no delay:
    0x21,
    ST7735_PWCTR6,
    1,
    0x80,
    0xf0,
    1,
    0x11,
    0xD6,
    1,
    0xCB,
    TFT_INVONN,
    0,  // 13: Don't invert display, no args, no delay
    TFT_MADCTL,
    1,     // 14: Memory access control (directions), 1 arg:
    0xC8,  //     row addr/col addr, bottom to top refresh
    TFT_CMD_PIXFMT,
    1,      // 15: set color mode, 1 arg, no delay:
    0x06
  };

  // Init for 7735R, part 2 (green tab only)
  // ---------------------------------------
  static const uint8_t Rcmd2green[] = {
    2,            //  2 commands in list:
    TFT_CASET  , 4      ,   //  1: Column addr set, 4 args, no delay:
    0x00, 0x02,       //     XSTART = 0
    0x00, 0x7F+0x02,      //     XEND = 129
    TFT_PASET  , 4      ,     //  2: Row addr set, 4 args, no delay:
    0x00, 0x01,       //     XSTART = 0
    0x00, 0x9F+0x01     //     XEND = 160
  };

  // Init for 7735R, part 2 (red tab only)
  // -------------------------------------
  static const uint8_t Rcmd2red[] = {
    2,            //  2 commands in list:
    TFT_CASET  , 4      ,     //  1: Column addr set, 4 args, no delay:
    0x00, 0x00,       //     XSTART = 0
    0x00, 0x7F,       //     XEND = 127
    TFT_PASET  , 4      ,     //  2: Row addr set, 4 args, no delay:
    0x00, 0x00,       //     XSTART = 0
    0x00, 0x9F        //     XEND = 159
  };

  // Init for 7735R, part 3 (red or green tab)
  // -----------------------------------------
  static const uint8_t Rcmd3[] = {
    4,  //  4 commands in list:
    ST7735_GMCTRP1,
    16,  //  1: 16 args, no delay:
    0x0D,
    0x0C,
    0x0C,
    0x0E,
    0x0E,
    0x00,
    0x00,
    0x00,
    0x00,
    0x09,
    0x23,
    0x31,
    0x00,
    0x0C,
    0x03,
    0x1A,
    ST7735_GMCTRN1,
    16,  //  2: 16 args, no delay:
    0x0A,
    0x05,
    0x06,
    0x07,
    0x08,
    0x01,
    0x00,
    0x00,
    0x00,
    0x05,
    0x20,
    0x2E,
    0x00,
    0x0A,
    0x01,
    0x1A,
    ST7735_NORON, TFT_CMD_DELAY,  //  3: Normal display on, no args, w/delay
    10,              //     10 ms delay
    TFT_DISPON, TFT_CMD_DELAY,  //  4: Main screen turn on, no args w/delay
    100
  };

  // ==== Public functions =========================================================

  // == Low level functions; usually not used directly ==
  esp_err_t wait_trans_finish(uint8_t free_line);
  void disp_spi_transfer_cmd(int8_t cmd);
  void disp_spi_transfer_cmd_data(int8_t cmd, uint8_t *data, uint32_t len);
  void drawPixel(int16_t x, int16_t y, color_t color, uint8_t sel);
  void send_data(int x1, int y1, int x2, int y2, uint32_t len, color_t *buf);
  void TFT_pushColorRep(int x1, int y1, int x2, int y2, color_t data, uint32_t len);
  int read_data(int x1, int y1, int x2, int y2, int len, uint8_t *buf, uint8_t set_sp);
  color_t readPixel(int16_t x, int16_t y);

  // Deactivate display's CS line
  //========================
  esp_err_t disp_deselect();

  // Activate display's CS line and configure SPI interface if necessary
  //======================
  esp_err_t disp_select();


  // Find maximum spi clock for successful read from display RAM
  // ** Must be used AFTER the display is initialized **
  //======================
  uint32_t find_rd_speed();


  // Change the screen rotation.
  // Input: m new rotation value (0 to 3)
  //=================================
  void _tft_setRotation(uint8_t rot);

  // Initialize all pins used by display driver
  // ** MUST be executed before SPI interface initialization
  //=================
  void TFT_PinsInit();

  // Perform display initialization sequence
  // Sets orientation to landscape; clears the screen
  // * All pins must be configured
  // * SPI interface must already be setup
  // * 'tft_disp_type', 'COLOR_BITS', '_width', '_height' variables must be set
  //======================
  void TFT_display_init();

  // ===============================================================================

#ifdef __cplusplus
  }
#endif

#endif
