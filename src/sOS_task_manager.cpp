///
/// @file task_manager.cpp
/// @copyright Brian Gunnison (c) 2026
///
/// @brief init task list, runs active tasks
///
/// @details 
///

#include "types.h"
#include "config.h"
#include "utilities.h"
#include "logging.h"
#include "sOS_task_manager.h"


#if PLATFORM_AVR
// a obscure linker error:
// __cxa_pure_virtual function is an error handler that is invoked when a pure virtual function is called.
//If you are writing a C++ application that has pure virtual functions you must supply your own __cxa_pure_virtual error handler function.
// Arduino toolchain don't provide a libstdc++.
extern "C" void __cxa_pure_virtual() { while (1); } // A  'loud' implementation

// Minimal guard support for static local initialization on bare metal.
extern "C" {
    typedef int __guard;
    int __cxa_guard_acquire(__guard *g)
    {
        if (*g)
        {
            return 0;
        }
        *g = 1;
        return 1;
    }

    void __cxa_guard_release(__guard * /*g*/) {}
    void __cxa_guard_abort(__guard * /*g*/) {}
}
#endif


void sOS::Task::Init(sOS::Task *prev, sOS::Task *next)
{
    taskprev = prev;
    tasknext = next;
    SetTaskObject(NULL);
}

sOS::Task::TaskError sOS::Task::CallTask(void)
{     
    if (activeTaskObj == NULL)
    {
        DebugLogError("Task obj is NULL");
        return TASK_ERROR_NULL_TASK;
    }   
         
    if (activeTaskObj->RunTask() == FALSE)
    {
        return TASK_ERROR_FATAL;
    }
    return TASK_ERROR_NONE;
}   


   
void sOS::TaskManager::Init(void)
{
    // link all the free tasks singly as we pop off the top and push to the top. 
    sOS::Task *nt = NULL;
    for (uint8_t i = 0; i < NUM_TASKS - 1; i++)
    {
        nt = &tasks[i+1];
        tasks[i].Init(NULL, nt);
    }
    
    nt->Init(NULL, NULL);
    
    freeTaskList = &tasks[0];
    activeTaskList = NULL;
    currentActiveTask = NULL;
    
    peakTaskTime = 0;
    
    taskTimer = sOS::TimerManager::GetInstance()->GetTimer();
}  

sOS::Task *sOS::TaskManager::GetNewTask()
{
    if (freeTaskList == NULL)
    {
        DebugLogError("Out of free tasks");
        return NULL;
    }

    // pop off free list and return
    sOS::Task *ft = freeTaskList;
    freeTaskList = ft->GetNextTask();
    ft->Init(NULL, NULL);
    return ft;
}    
  

sOS::Task *sOS::TaskManager::AddActiveTask(TaskObject *taskObj, const char* name)
{
    sOS::Task *task = GetNewTask();
    if (task == NULL || taskObj == NULL)
    {
        DebugLogError("Adding NULL task object");
        FreeTask(task);
        return NULL;
    }
    
    DebugLog("%s - Adding task: %p, obj: %p", name, task, taskObj);

    task->SetTaskObject(taskObj);
    
    if (activeTaskList == NULL)
    {
       activeTaskList = task; 
       currentActiveTask = task;
       return task;
    }
    
    // push on top of list
    activeTaskList->SetPrevTask(task);
    task->SetNextTask(activeTaskList);
    activeTaskList = task;
    
    if (activeTaskList->GetPrevTask() != NULL)
    {
        DebugLogError("%s - prev task is not NULL",__FUNCTION__);
    }
    
    return task;
}

BOOL sOS::TaskManager::IsActiveTask(sOS::Task *task)
{
    sOS::Task *activeTask = activeTaskList;
    while (TRUE)
    {
        if (activeTask == NULL)
        {
            return FALSE;
        }
        
        if (task == activeTask)
        {
            return TRUE;
        }
        
        activeTask = activeTask->GetNextTask();
    }
    
    return FALSE;
    
}


void sOS::TaskManager::FreeTask(sOS::Task *task)
{
    if (task == NULL)
    {
        return;
    }
    
    task->Init(NULL, NULL);
    
    if (freeTaskList == NULL)
    {
        freeTaskList = task;
        return;
    } 
    
    task->SetNextTask(freeTaskList);
    freeTaskList = task;
}

void sOS::TaskManager::DeleteActiveTask(sOS::Task *&task)
{
    if (task == NULL)
    {
        DebugLogError("Deleting NULL task");
        return;
    }

    //DebugLog("Deleting task: %p", task);
    while(TRUE)
    {    
        // on top
        if (task->GetPrevTask() == NULL)
        {
            activeTaskList = task->GetNextTask();
            if (activeTaskList != NULL)
            {
                activeTaskList->SetPrevTask(NULL);
            }
            break;
        }
    
        // bottom
        if (task->GetNextTask() == NULL)
        {
            task->GetPrevTask()->SetNextTask(NULL);
            break;
        }
    
        // middle
        task->GetPrevTask()->SetNextTask(task->GetNextTask());
        task->GetNextTask()->SetPrevTask(task->GetPrevTask());
        break;
    } 
    
    
    FreeTask(task);
    task = NULL;
    
    currentActiveTask = activeTaskList; 

}    

// runs one task at a time
void sOS::TaskManager::RunNextTask()
{
    if (activeTaskList == NULL)
    {
        DebugLogError("Active task is NULL cannot run");
        return; // should always be active tasks...
    }
    
    if (currentActiveTask == NULL)
    {
        DebugLogError("Current Active task is NULL cannot run");
        return; // should always be active tasks...
    }
    
    uint32_t taskTime = 0;

    taskTimer->Start(TASK_TIMEOUT_WARNING);
    
    sOS::Task::TaskError taskError = currentActiveTask->CallTask();
    if (taskError == sOS::Task::TASK_ERROR_NULL_TASK)
    {
        DebugLogError("NULL task error");
    }
        
    if (taskTimer->Expired(taskTime) == TRUE)
    {
        DebugLogError("Task took too long: %lu msec", taskTime);
    }
    
    if (taskTime > peakTaskTime)
    {
        peakTaskTime = taskTime;
        DebugLog("Peak task time: %d msec", peakTaskTime);
    }
    
    if (taskError == sOS::Task::TASK_ERROR_FATAL)
    {
        DebugLogError("Object task returned fatal");
        DeleteActiveTask(currentActiveTask);  
        currentActiveTask = activeTaskList;     
    }
    else
    {
        currentActiveTask = currentActiveTask->GetNextTask();
        if (currentActiveTask == NULL)
        {
            currentActiveTask = activeTaskList;
        }
    }        
}
