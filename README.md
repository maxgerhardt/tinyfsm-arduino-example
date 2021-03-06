# tinyfsm: Arduino Example

Based on the library at https://github.com/digint/tinyfsm and the elevator example thereof.

Builds a modified version of the example with the Arduino framework.

This example builds for an Arduino Uno and and a Bluepill (STM32F103C8).

Simply clone this repo and use "Open Project" in the PlatformIO Home screen to open it, or use [the CLI](https://docs.platformio.org/en/latest/core/index.html) directly (e.g. `pio run -e uno -t upload` etc).

```
Building .pio\build\uno\firmware.hex
Checking size .pio\build\uno\firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [===       ]  27.3% (used 560 bytes from 2048 bytes)
Flash: [==        ]  15.5% (used 4988 bytes from 32256 bytes)
[..]

Building .pio\build\genericSTM32F103C8\firmware.bin
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [          ]   4.1% (used 848 bytes from 20480 bytes)
Flash: [==        ]  18.5% (used 12104 bytes from 65536 bytes

Environment         Status    Duration
------------------  --------  ------------
uno                 SUCCESS   00:00:02.154
genericSTM32F103C8  SUCCESS   00:00:07.923
===================== 2 succeeded in 00:00:10.077 ===================== 
```

Example output (serial monitor)

```
Executing task in folder bluepill_f103c8_128k_repro: C:\Users\Max\AppData\Local\Programs\Python\Python38\Scripts\platformio.exe device monitor --environment uno <

--- Available filters and text transformations: colorize, debug, default, direct, hexlify, log2file, nocontrol, printable, send_on_enter, time
--- More details at http://bit.ly/pio-monitor-filters
--- Miniterm on COM33  115200,8,N,1 ---
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H ---
c=Call, f=FloorSensor, a=Alarm, q=Quit ? 
Motor: stopped
Motor: stopped
c
Floor ? 
1
Motor: moving up
c=Call, f=FloorSensor, a=Alarm, q=Quit ? 
f
Floor ? 
1
Reached floor 1
Motor: stopped
c=Call, f=FloorSensor, a=Alarm, q=Quit ? 
```