set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

set(AVR_TOOLCHAIN_DIR_DEFAULT "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/bin")
if(NOT EXISTS "${AVR_TOOLCHAIN_DIR_DEFAULT}/avr-gcc.exe")
  set(AVR_TOOLCHAIN_DIR_DEFAULT "C:/Program Files/Microchip/xc8/v2.36/avr/bin")
endif()

set(AVR_TOOLCHAIN_DIR "${AVR_TOOLCHAIN_DIR_DEFAULT}" CACHE PATH "Path to AVR toolchain bin directory")

set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN_DIR}/avr-gcc.exe")
set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN_DIR}/avr-g++.exe")
set(CMAKE_ASM_COMPILER "${AVR_TOOLCHAIN_DIR}/avr-gcc.exe")

set(CMAKE_OBJCOPY "${AVR_TOOLCHAIN_DIR}/avr-objcopy.exe")
set(CMAKE_OBJDUMP "${AVR_TOOLCHAIN_DIR}/avr-objdump.exe")
set(CMAKE_SIZE "${AVR_TOOLCHAIN_DIR}/avr-size.exe")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
