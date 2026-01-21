///
/// @file sOS_timer_manager.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Manages timers for handling timeouts, delays, etc.
///
/// @details The TimerManager manages a set of Timer objects that provide
/// timing services to other components of the system. This is useful for
/// implementing timeouts, delays, and other time-based functionalities.
///
#pragma once
#include "types.h"
#include "logging.h"

namespace sOS
{
// A Timer object represents a single timer.
class Timer
{
    public:

    /// @brief Initializes the Timer object.
    /// @details Resets start and expiration fields.
    void Init(void);
    
    /// @brief Starts the Timer with a specified duration.
    /// @param msec Duration in milliseconds.
    void Start(uint32_t msec);
    
    /// @brief Checks if the Timer has expired.
    /// Note that this is only accurate if the method is called frequently.
    /// @return TRUE when the timeout has elapsed.
    BOOL Expired(void);

    /// @brief Checks if the Timer has expired and returns the time passed.
    /// Note that this is only accurate if the method is called frequently.
    /// @param timePassed Elapsed time since start in milliseconds.
    /// @return TRUE if expired, otherwise FALSE.
    BOOL Expired(uint32_t &timePassed);
    
    /// @brief Returns the Timer's expiration tick count.
    uint32_t GetExpireTicks(void) { return expireTicks; }

    private:
    
    static const uint32_t MAX_VALUE = 0xFFFFFFFF;

    /// @brief The tick count when the Timer was started.
    uint32_t startTime;

    /// @brief The tick count when the Timer will expire.
    uint32_t expireTicks;
};

// The TimerManager manages all the Timer objects.
class TimerManager
{
    public:

    /// @brief Singleton instance of the TimerManager.
    static TimerManager* GetInstance()
    {
        static TimerManager instance;
        return &instance;
    }

    /// @brief Initializes the TimerManager.
    /// @details Resets the timer pool and prepares all Timer objects.
    void Init(void);

    /// @brief Provides a new Timer object.
    /// If no more Timers are available, this function logs an error and returns NULL.
    /// @return Pointer to a free Timer, or NULL when exhausted.
    Timer *GetTimer(void)
    {
        if (nextTimer == NUM_TIMERS)
        {
            DebugLogError("Out of timers - Add more");
            return NULL;
        }

        return &timers[nextTimer++];
    }

    /// @brief Returns current system timestamp in milliseconds.
    uint32_t GetTimestamp();

    private:
    
    /// @brief Total number of Timer objects in the pool.
    static const uint8_t NUM_TIMERS = 64; // not very expensive...
    /// @brief Storage for Timer objects.
    Timer timers[NUM_TIMERS]; 
        
    /// @brief Index of the next available Timer.
    uint8_t nextTimer;

};
} // namespace sOS
