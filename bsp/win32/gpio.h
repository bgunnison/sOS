///
/// @file gpio.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Win32 BSP GPIO stubs.
///
/// @details Provides LED toggle/on/off helpers for host builds.
///
#pragma once

#include "logging.h"

inline void BspLifeLedToggle()
{
    static bool state = false;
    state = !state;
    DebugLog("Life LED: %s", state ? "ON" : "OFF");
}

inline void BspErrorLedOn()
{
    DebugLog("Error LED: ON");
}

inline void BspErrorLedOff()
{
    DebugLog("Error LED: OFF");
}

#define GPIO_LIFE_LED_TOGGLE() BspLifeLedToggle()
#define GPIO_ERROR_LED_ON() BspErrorLedOn()
#define GPIO_ERROR_LED_OFF() BspErrorLedOff()
