///
/// @file logging.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief AVR BSP logging stubs.
///
/// @details Logging is a no-op for bare-metal builds by default.
///
#pragma once

inline void DebugLog(const char* /*format*/, ...)
{
}

inline void DebugLogError(const char* /*format*/, ...)
{
}
