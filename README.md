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


# Misc

## BLE characteristic to key table

Extracted from [SuperGreenApp/src/utils/ble.h](https://github.com/supergreenlab/SuperGreenApp/blob/master/src/utils/ble.js#L44).

Install LightBlue for [iOS](https://itunes.apple.com/us/app/lightblue-explorer/id557428110?mt=8) and [android](https://play.google.com/store/apps/details?id=com.punchthrough.lightblueexplorer&hl=en) for direct access.

| uuid                                 | name                   | type         |
| ------------------------------------ | ---------------------- | ------------ |
| a6317732-8c0e-ee6e-68ee-61f13d4f8b25 | name                   | stringValue  |
| 40f9ee4f-e19e-4a8a-aa33-b4aae23b6a9b | time                   | intValue     |
| 8ff6dfd2-3bd6-feb4-43ec-de5663122894 | state                  | intValue     |
| 6df781fe-6dce-5234-1870-6a972114c596 | ledInfo                | ledInfoValue |
| 4291ec1b-65df-19c4-c5f1-e4259071fc00 | led_0_duty             | intValue     |
| 4291ec1b-65df-19c4-c5f1-e4259071fc01 | led_1_duty             | intValue     |
| 4291ec1b-65df-19c4-c5f1-e4259071fc02 | led_2_duty             | intValue     |
| 4291ec1b-65df-19c4-c5f1-e4259071fc03 | led_3_duty             | intValue     |
| 4291ec1b-65df-19c4-c5f1-e4259071fc04 | led_4_duty             | intValue     |
| 4291ec1b-65df-19c4-c5f1-e4259071fc05 | led_5_duty             | intValue     |
| 5f5ea840-3aa9-0a7b-343d-415ab2faa9f3 | timerType              | intValue     |
| b2286094-8299-a967-db89-ee856e365789 | timerOutput            | intValue     |
| e867f9a6-4ab7-09da-ef26-19f350ed4ba1 | onHour                 | intValue     |
| 7528a50b-dd3b-f714-62f5-7167f1791347 | onMin                  | intValue     |
| 5dafb88c-9d7e-ab6b-0253-12294c35beae | offHour                | intValue     |
| 086aa1e1-d9ab-2d22-4110-4f3f05efd3d4 | offMin                 | intValue     |
| 3867a37c-85a9-338c-40ac-96d4ee586841 | simulatedTime          | intValue     |
| 829bfbd2-a7e1-4c16-b7e2-4a8fd6261f40 | startDateMonth         | intValue     |
| 547af7e1-6a8c-4fbc-b568-9c3f194cdc1e | startDateDay           | intValue     |
| 495600fd-947d-4157-a996-20780ad1d81a | durationDays           | intValue     |
| 6f01cd48-a405-45e5-99db-0de8b5ca2e7f | simulationDurationDays | intValue     |
| 1f450234-f101-4f57-ba39-304b053b95a2 | startedAt              | intValue     |
| 372fda1c-6d67-cbda-f083-ae31b50e06ee | wifiStatus             | intValue     |
| 6ca36981-9c55-74a5-5415-e16bc1c3fe17 | wifiSsid               | stringValue  |
| f7e40b10-6cfe-a6f1-fea0-cc6e82535db9 | wifiPassword           | stringValue  |
| 7072326b-95b0-4822-a5e1-b2cc47875ae5 | stretch                | intValue     |
| a66375f6-7677-ba29-46b7-0fde55b0db61 | ledDim                 | intValue     |
| 03b7cea7-bedc-e37f-1bfd-7f2ab70a5e7b | blower                 | intValue     |
