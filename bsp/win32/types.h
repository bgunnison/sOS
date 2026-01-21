///
/// @file types.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Win32 BSP basic types and interrupt stubs.
///
/// @details Provides fixed-width types, BOOL, and no-op interrupt macros
/// for the Win32 build.
///
#pragma once

#include <cstddef>
#include <cstdint>

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;

using BOOL = bool;
static constexpr BOOL TRUE = true;
static constexpr BOOL FALSE = false;

#define INTERRUPT_GLOBAL_ENABLE() ((void)0)
#define INTERRUPT_GLOBAL_DISABLE() ((void)0)
#define DISABLE_1MS_TIMER_INTERRUPT() ((void)0)
#define ENABLE_1MS_TIMER_INTERRUPT() ((void)0)
