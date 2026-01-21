# sOS - simple Operating System

This repository contains a highly portable simple Operating System (sOS) to run tasks on a MCU.

## Features
- Task creation and deletion
- Round robin scheduling
- lightweight timers

## sOS API
- tasks
- timers

## MCUs
- AVR

## Builds

This repo keeps build tooling inside the `build/` directory:
- `build/win32` contains the Visual Studio solution/project for the Win32 example app.
- `build/avr` contains the CMake project and helper scripts for the AVR build.

### Win32 (Visual Studio)

Tools required:
- Visual Studio 2022 with the Desktop development with C++ workload.

Open the solution:
- `build/win32/sOS.sln`

Build:
- Select `Debug` or `Release`, then Build.

Output:
- `build/win32/bin/sOS.exe`

Notes:
- The Win32 build is only for the example app and host-side testing.

### AVR (CMake + avr-gcc)

Tools required:
- CMake 3.20+
- Ninja (recommended for fast builds)
- AVR GCC toolchain (Microchip/Atmel)
  - Default toolchain path used by CMake:
    `C:\Program Files (x86)\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin`
  - Fallback:
    `C:\Program Files\Microchip\xc8\v2.36\avr\bin`

Build (from a terminal in `build/avr`):
```bat
build.bat
```

Clean (removes all AVR build artifacts):
```bat
clean.bat
```

Output:
- `build/avr/bin/sOS_atmega1284p.hex`
- `build/avr/bin/sOS_atmega1284p.lst`

Configure MCU and clock:
- Edit `build/avr/CMakeLists.txt`:
  - `SOS_MCU` (default: `atmega1284p`)
  - `SOS_F_CPU` (default: `16000000UL`)

Notes:
- AVR build products and intermediate files live under `build/avr`.
- The CMake build tree is under `build/avr/obj`.
