///
/// @file product.cpp
/// @copyright Brian Gunnison (c) 2026
///
/// @brief main class implementation example for sOS
///
/// @details 
///

#include "types.h"
#include "logging.h"
#include "sOS_timer_manager.h"
#include "sOS_task_manager.h"

#include "keep_alive.h"
#include "LED_blinker.h"
#include "product.h"

static void LogVersion()
{
    DebugLog("sOS example build");
}

int main(void)
{
    Product::GetInstance()->Init();
    Product::GetInstance()->MainLoop();
}



void Product::Init()
{
    //Turn on interrupts
    INTERRUPT_GLOBAL_ENABLE();
    
    sOS::TimerManager::GetInstance()->Init();
    
    ErrorLEDBlinker::GetInstance()->Init();
    
    taskManager = sOS::TaskManager::GetInstance();
    taskManager->Init();
    
    // add life LED task, never deleted
    taskManager->AddActiveTask((sOS::TaskObject *)&BlinkLifeTask, "LifeLED");

    LogVersion();
   
    KeepAlive::GetInstance()->Init();

    DebugLog("Product Initialized");
}


void Product::MainLoop()
{
    while(TRUE)
    {
        taskManager->RunNextTask(); // runs one active task per call           
    }
}  



  


