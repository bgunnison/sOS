///
/// @file gpio.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief BSP selector for GPIO.
///
/// @details Includes the active BSP GPIO header based on SOS_BSP_* defines.
///
#pragma once

#if defined(SOS_BSP_WIN32)
#include "win32/gpio.h"
#elif defined(SOS_BSP_AVR)
#include "avr/gpio.h"
#else
#error "Define SOS_BSP_WIN32 or SOS_BSP_AVR"
#endif
