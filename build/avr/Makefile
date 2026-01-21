MCU = atmega1284p
F_CPU = 16000000UL

TARGET = sOS_avr
BUILD_DIR ?= build/avr
WINPATH = $(subst /,\\,$(1))

AVR_GXX = avr-g++
AVR_OBJCOPY = avr-objcopy
AVR_SIZE = avr-size

CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -DSOS_BSP_AVR -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti
CXXFLAGS += -I./bsp -I./src -I./examples
CXXFLAGS += -std=gnu++17 -Wall -Wextra

LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections

SRCS = \
	examples/LED_blinker.cpp \
	examples/keep_alive.cpp \
	examples/product.cpp \
	src/sOS_task_manager.cpp \
	src/sOS_timer_manager.cpp

OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

ELF = $(BUILD_DIR)/$(TARGET).elf
HEX = $(BUILD_DIR)/$(TARGET).hex

all: $(ELF) size

$(ELF): $(OBJS)
	$(AVR_GXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@if not exist "$(call WINPATH,$(dir $@))" mkdir "$(call WINPATH,$(dir $@))"
	$(AVR_GXX) $(CXXFLAGS) -c $< -o $@

hex: $(HEX)

$(HEX): $(ELF)
	$(AVR_OBJCOPY) -O ihex -R .eeprom $< $@

size: $(ELF)
	$(AVR_SIZE) -C --mcu=$(MCU) $<

clean:
	@rmdir /s /q "$(call WINPATH,$(BUILD_DIR))" 2>NUL || exit 0
