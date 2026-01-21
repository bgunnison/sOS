///
/// @file keep_alive.cpp
/// @copyright Brian Gunnison (c) 2026
///
/// @brief keep alive implemenation
///
/// @details verifies each AMC is booted periodically
///
#include <stdio.h>

#include "types.h"
#include "logging.h"
#include "sOS_task_manager.h"
#include "sOS_timer_manager.h"
#include "keep_alive.h"


void KeepAlive::Init(void)
{
    taskManager = sOS::TaskManager::GetInstance();
    task = taskManager->AddActiveTask((sOS::TaskObject *)this, "KeepAlive");
    
    timer = sOS::TimerManager::GetInstance()->GetTimer();

    timer->Start(1000); // wait 1 sec before self-test starts for AMCs to boot
    
    state = STATE_START;
}



void KeepAlive::Start(void)
{ 
    // we wait so all the AMCs can boot
    if (timer->Expired() == FALSE)
    {
        return;
    }
       
    state = STATE_RUN;
}  


void KeepAlive::Run(void)
{
    // we ping periodically
    if (timer->Expired() == FALSE)
    {
        return;
    }
    
    timer->Start(1000); // check every 1 sec 
 
    state = STATE_RUN;
}



BOOL KeepAlive::RunTask(void)
{
    switch(state)
    {        
        case STATE_START:
            Start();
            break;
            
        case STATE_RUN:
            Run();
            break;
            
        case STATE_ERROR:
            break;
                  
        default:
            DebugLogError("KeepAlive::RunTask: Bad state");
            taskManager->DeleteActiveTask(task);
            return FALSE;
    }
    
    return TRUE;
}




 
