///
/// @file LED_blinker.h
/// @copyright Tricontinent Scientific (c) 2023
///
/// @brief LED blinker tasks for example apps.
///
/// @details 
///

#pragma once
#include "types.h"
#include "utilities.h"
#include "gpio.h"
#include "sOS_task_manager.h"



class LifeLEDBlinker : public sOS::TaskObject
{
    protected:
    BOOL RunTask() { BlinkLifeLED(); return TRUE;}
    
    private:
    
    void BlinkLifeLED(void)
    {
        static uint32_t lastBlink = 0;
        
        if (GetTimestamp() - lastBlink > 1000)
        {
            lastBlink = GetTimestamp();
            GPIO_LIFE_LED_TOGGLE();
        }
    }
};

// called in background loop always
extern LifeLEDBlinker BlinkLifeTask; 


class ErrorLEDBlinker : public sOS::TaskObject
{
    public:
    
    void Init(void) 
    { 
        blinks = 0; 
        task = NULL;
        blinkCounter = 0;
        offTime = 0;
        timer = sOS::TimerManager::GetInstance()->GetTimer();
    }
    
    // singleton
    static ErrorLEDBlinker* GetInstance()
    {
        static ErrorLEDBlinker instance;
        return &instance;
    }
    
    typedef enum
    {
        KEEP_ALIVE_ERROR = 2,
        SELFTEST_ERROR = 4,
        FIRMWARE_ERROR = 6,
    }RedLEDError;

    void Start(RedLEDError b)
    {
        if (blinks != 0)
        {
            return;
        }
           
        state = ON; 
        blinkCounter = 0;        
        blinks = b;
        
        offTime = (BLINK_TIME - (blinks * ON_TIME))/(blinks - 1);
        task = sOS::TaskManager::GetInstance()->AddActiveTask((sOS::TaskObject *) this, "ErrorLED");   
    }
    
    void Stop(void)
    {
        GPIO_ERROR_LED_OFF();
        blinks = 0;
        sOS::TaskManager::GetInstance()->DeleteActiveTask(task);
    }
    
    protected:
    BOOL RunTask() { BlinkErrorLED(); return TRUE;}
    
    private:
    
    sOS::Task *task;
    
    uint16_t offTime;
    uint8_t blinks;
    uint8_t blinkCounter;
    
    // we blink for 3 seconds in a 5 second period. 
    static const uint16_t BLINK_TIME = 3000;
    static const uint16_t REST_TIME = 3000;
    static const uint16_t ON_TIME = 100;
    
    typedef enum
    {
        ON,
        OFF,
        REST,
        
    }STATE;
        
    STATE state;
    sOS::Timer *timer;
    
    void BlinkErrorLED(void)
    {
        if (timer->Expired() == FALSE)
        {
            return;
        }
                    
        switch (state)
        {
            case ON:
                GPIO_ERROR_LED_ON();
                timer->Start(ON_TIME);
                state = OFF;
                blinkCounter++;
                break;
            
            case OFF:
                GPIO_ERROR_LED_OFF();
                if (blinkCounter == blinks)
                {
                    state = REST;
                    timer->Start(REST_TIME);
                    blinkCounter = 0;
                    break;
                }
            
                timer->Start(offTime);
                state = ON;
                break;
            
            case REST:
                timer->Start(REST_TIME);
                state = ON;
                break;
            
            default:
                break;

        }            
    }
};
