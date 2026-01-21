///
/// @file config.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief BSP selector for configuration.
///
/// @details Includes the active BSP config header based on SOS_BSP_* defines.
///
#pragma once

#if defined(SOS_BSP_WIN32)
#include "win32/config.h"
#elif defined(SOS_BSP_AVR)
#include "avr/config.h"
#else
#error "Define SOS_BSP_WIN32 or SOS_BSP_AVR"
#endif
