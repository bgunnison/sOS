///
/// @file types.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief AVR BSP basic types and interrupt stubs.
///
/// @details Provides fixed-width types, BOOL, and interrupt macro stubs
/// for the AVR build.
///
#pragma once

#include <stddef.h>
#include <stdint.h>

using BOOL = bool;
static constexpr BOOL TRUE = true;
static constexpr BOOL FALSE = false;

#define INTERRUPT_GLOBAL_ENABLE() ((void)0)
#define INTERRUPT_GLOBAL_DISABLE() ((void)0)
#define DISABLE_1MS_TIMER_INTERRUPT() ((void)0)
#define ENABLE_1MS_TIMER_INTERRUPT() ((void)0)
