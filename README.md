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

## Basic concept

This code is made to be as compile-time as possible, in order to keep a low memory footprint and to keep memory-related error away.

This is to respond to the 2 main limitations:

- esp32 in its most widely available is only 4mB flash capable, espressif's libraries eat most of the 1,5mB available for the actual firmware.
- while the code will never really be complicated, it has to run for months without interruptions, thus avoiding any possibility of memory leakage seems wise for now.

The firmware is mostly composed of 2 parts: a `key/value store` and `workers`

### Key/Value store

Espressif provides a flash-backed key/value store called [nvs](https://dl.espressif.com/doc/esp-idf/latest/api-reference/storage/nvs_flash.html) which will hold all the configuration and (nearly) anything that is currently happening inside the box.

Most of these keys and values are accessible via 2 means of transport, ble, and http (coming soon).

For example, there is a key `TIMER_T` that tells which type of timer is currently activated. And if the value is `1`, the "classic" timer is selected, then the keys `ON_H` and `ON_M` will tell the hour and minute at which the light goes on, `OFF_H` and `OFF_M` are for off jours and minutes.

While http access is under development right now, ble already works, see below for a list of available characteristics available with there corresponding keys.

### Workers

Workers are like threads that continuously run in the background, most folders under the `main/` directory are workers.

Their role is to ensure that the state described by the key/value store is the actual state of the SuperGreenDriver in the real world.

For example, if you change the time of sunrise or sunset, the worker of the timer will pick the change up and change the state of the leds accordingly.

A worker in its most simple form is nothing more than an empty `while (true)` loop: (like an Arduino sketch)

```c

void worker_task(void *param) {
  while (true) {}
}

```

Most worker have a `wait(30s)` in there body. Every 30s they re-apply the desired state according to there related key/values.

This avoids error-prone event-driven development: whatever happens it'll get back on it's feet, even if you mess with the key/values through ble or http.

And it makes it nearly as easy as creating and Arduino sketch to create a new worker.

## Quick start

Follow the [get-started guide from espressif](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/).

For now, the firmware handles multiple configurations at compile time, the current repository is not shipped with any configuration.
For the project to compile, you need to clone at `main/conf` one of the configuration repositories below:

- [SuperGreenOSConf-Chronic2Leds](https://github.com/supergreenlab/SuperGreenOSConf-Chronic2Leds)
- [SuperGreenOSConf-Chronic3Leds](https://github.com/supergreenlab/SuperGreenOSConf-Chronic3Leds)
- [SuperGreenOSConf-SGD2Leds](https://github.com/supergreenlab/SuperGreenOSConf-SGD2Leds)
- [SuperGreenOSConf-SGD3Leds](https://github.com/supergreenlab/SuperGreenOSConf-SGD3Leds)

