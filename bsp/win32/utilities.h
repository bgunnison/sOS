///
/// @file utilities.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Win32 BSP timing utilities.
///
/// @details Provides timestamp and millisecond delay helpers.
///
#pragma once

#include "types.h"

#include <chrono>
#include <thread>

inline uint32_t GetTimestamp()
{
    static const auto start = std::chrono::steady_clock::now();
    const auto now = std::chrono::steady_clock::now();
    return static_cast<uint32_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
}

inline void DelayMS(uint16_t time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}
