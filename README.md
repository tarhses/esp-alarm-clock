# ESP32 Alarm Clock

This is still a work in progress.

It has been tested with ESP-IDF version 4.3.2.

## Build

`idf.py build`

## Install

`idf.py flash`

## Debug

`idf.py monitor`

## Configuration

`idf.py menuconfig`

```
Compiler options --> Optimization Level -> Optimize for performance (-O2)
Component config --> Wi-Fi --> WiFi NVS flash --> Off
Component config --> FAT Filesystem support --> Long filename buffer in heap
```
