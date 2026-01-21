///
/// @file timer_manager.cpp
/// @copyright Brian Gunnison (c) 2026
///
/// @brief manages timeout timers and msec time
///
/// @details Manages time
///
#include "types.h"
#include "logging.h"
#include "utilities.h"
#include "sOS_timer_manager.h"


namespace sOS
{
// Called at power up
void Timer::Init()
{
    startTime = 0;
    expireTicks = 0;
}

// Returns TRUE if counter time has expired, Non-zero arg starts the counter
// CAREFULL, counter is only checked when this function is called, timer could  wrap
// if not called often enough
void Timer::Start(uint32_t mS)
{    
    // make access atomic
    DISABLE_1MS_TIMER_INTERRUPT();
    startTime = ::GetTimestamp();
    ENABLE_1MS_TIMER_INTERRUPT();
    
    expireTicks = mS;
}


// Returns TRUE if counter time has expired, Non-zero arg starts the counter
// CAREFULL, counter is only checked when this function is called, timer could  wrap
// if not called often enough
BOOL Timer::Expired()
{
     uint32_t delta;
    
    // make access atomic
    DISABLE_1MS_TIMER_INTERRUPT();
    uint32_t myTimerMS = ::GetTimestamp();
    ENABLE_1MS_TIMER_INTERRUPT();
        
    if (startTime > myTimerMS)    //timer must have wrapped
    {
        delta = myTimerMS;
        delta += MAX_VALUE - startTime;
    }
    else
    {
        delta = myTimerMS - startTime;
    }
    
    if (delta >= expireTicks)
    {
        return TRUE;
    }
    
    return FALSE;
}

BOOL Timer::Expired(uint32_t &timePassed)
{
    uint32_t delta;
    
    // make access atomic
    DISABLE_1MS_TIMER_INTERRUPT();
    uint32_t myTimerMS = ::GetTimestamp();
    ENABLE_1MS_TIMER_INTERRUPT();
    
    if (startTime  > myTimerMS)    //timer must have wrapped
    {
        delta = myTimerMS;
        delta += MAX_VALUE - startTime;
    }
    else
    {
        delta = myTimerMS - startTime;
    }
    
    if (delta > expireTicks)
    {
        timePassed = delta;
        return TRUE;
    }
    
    timePassed = delta;
    return FALSE;
}


    
// Called at power up 
void TimerManager::Init(void)
{
    
    for (uint8_t i = 0; i < NUM_TIMERS; i++)
    {
        timers[i].Init();
    }
    
    nextTimer = 0;

   // DebugLog("Initialized timer manager");
}


uint32_t TimerManager::GetTimestamp()
{
    // atomic sample
    INTERRUPT_GLOBAL_DISABLE();
    uint32_t myTimerMS = ::GetTimestamp();
    INTERRUPT_GLOBAL_ENABLE();

    return myTimerMS;
}
} // namespace sOS
