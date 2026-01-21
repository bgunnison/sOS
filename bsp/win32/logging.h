///
/// @file logging.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Win32 BSP logging helpers.
///
/// @details Provides DebugLog and DebugLogError implementations for Win32.
///
#pragma once

#include <cstdarg>
#include <cstdio>

inline void DebugLog(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");
    va_end(args);
    fflush(stdout);
}

inline void DebugLogError(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    fprintf(stderr, "ERROR: ");
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
    fflush(stderr);
}
