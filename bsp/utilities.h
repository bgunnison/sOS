///
/// @file utilities.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief BSP selector for utilities.
///
/// @details Includes the active BSP utilities header based on SOS_BSP_* defines.
///
#pragma once

#if defined(SOS_BSP_WIN32)
#include "win32/utilities.h"
#elif defined(SOS_BSP_AVR)
#include "avr/utilities.h"
#else
#error "Define SOS_BSP_WIN32 or SOS_BSP_AVR"
#endif
