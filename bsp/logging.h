///
/// @file logging.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief BSP selector for logging.
///
/// @details Includes the active BSP logging header based on SOS_BSP_* defines.
///
#pragma once

#if defined(SOS_BSP_WIN32)
#include "win32/logging.h"
#elif defined(SOS_BSP_AVR)
#include "avr/logging.h"
#else
#error "Define SOS_BSP_WIN32 or SOS_BSP_AVR"
#endif
