cmake_minimum_required(VERSION 3.20)

project(sOS_avr LANGUAGES C CXX)

set(SOS_MCU atmega1284p CACHE STRING "AVR MCU")
set(SOS_F_CPU 16000000UL CACHE STRING "CPU frequency")
get_filename_component(SOS_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(SOS_AVR_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}/bin")
set(SOS_AVR_HEX "${SOS_AVR_OUT_DIR}/sOS_${SOS_MCU}.hex")
set(SOS_AVR_LST "${SOS_AVR_OUT_DIR}/sOS_${SOS_MCU}.lst")

add_executable(sOS_avr
    ${SOS_SOURCE_DIR}/examples/LED_blinker.cpp
    ${SOS_SOURCE_DIR}/examples/keep_alive.cpp
    ${SOS_SOURCE_DIR}/examples/product.cpp
    ${SOS_SOURCE_DIR}/src/sOS_task_manager.cpp
    ${SOS_SOURCE_DIR}/src/sOS_timer_manager.cpp
)

target_include_directories(sOS_avr PRIVATE
    ${SOS_SOURCE_DIR}/bsp/avr
    ${SOS_SOURCE_DIR}/src
    ${SOS_SOURCE_DIR}/examples
)

target_compile_definitions(sOS_avr PRIVATE
    SOS_BSP_AVR
    F_CPU=${SOS_F_CPU}
)

target_compile_options(sOS_avr PRIVATE
    -mmcu=${SOS_MCU}
    -Os
    -ffunction-sections
    -fdata-sections
    -fno-exceptions
    -fno-rtti
    -Wall
    -Wextra
    -std=gnu++17
)

target_link_options(sOS_avr PRIVATE
    -mmcu=${SOS_MCU}
    -Wl,--gc-sections
)

set_target_properties(sOS_avr PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SOS_AVR_OUT_DIR}
)

add_custom_command(
    OUTPUT ${SOS_AVR_HEX} ${SOS_AVR_LST}
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom $<TARGET_FILE:sOS_avr> ${SOS_AVR_HEX}
    COMMAND ${CMAKE_OBJDUMP} -h -S $<TARGET_FILE:sOS_avr> > ${SOS_AVR_LST}
    DEPENDS sOS_avr
    COMMENT "Generating HEX and LST outputs"
)

add_custom_target(sos_avr_hex ALL
    DEPENDS ${SOS_AVR_HEX} ${SOS_AVR_LST}
)

add_custom_target(sos_avr_size
    COMMAND ${CMAKE_SIZE} -C --mcu=${SOS_MCU} $<TARGET_FILE:sOS_avr>
    DEPENDS sOS_avr
    COMMENT "AVR size"
)
