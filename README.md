![SuperGreenLab](assets/sgl.png?raw=true "SuperGreenLab")

# SuperGreenOS

The firmware that runs the [SuperGreenDriver](https://github.com/supergreenlab/SuperGreenDriver).

Based on [esp-idf](https://github.com/espressif/esp-idf) from espressif, and FreeRTOS.

Only runs on esp32.

I've mostly been woking with either:

- [Espressif ESP32 Development Board - Developer Edition](https://www.adafruit.com/product/3269)  
  Simple, but does not allow to flash the actual SuperGreenDriver.
- [Espressif ESP32 WROVER KIT - V3](https://www.adafruit.com/product/3384)  
  this one allows to debug through xtensa-esp32-elf-gdb and to flash the actual SuperGreenDriver.

## Quick start

Follow the [get-started guide from espressif](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/).

For now, the firmware handles multiple configurations at compile time, the current repository is not shipped with any configuration.
For the project to compile, you need to clone at `main/conf` one of the configuration repositories below:

- [SuperGreenOSConf-Chronic2Leds](https://github.com/supergreenlab/SuperGreenOSConf-Chronic2Leds)
- [SuperGreenOSConf-Chronic3Leds](https://github.com/supergreenlab/SuperGreenOSConf-Chronic3Leds)
- [SuperGreenOSConf-SGD2Leds](https://github.com/supergreenlab/SuperGreenOSConf-SGD2Leds)
- [SuperGreenOSConf-SGD3Leds](https://github.com/supergreenlab/SuperGreenOSConf-SGD3Leds)

