///
/// @file keep_alive.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief Does some work to show the tasks are running
///
/// @details 
///
#pragma once
#include "types.h"
#include "sOS_timer_manager.h"
#include "sOS_task_manager.h"


class KeepAlive : public sOS::TaskObject
{
    public:
    
     // singleton
     static KeepAlive* GetInstance()
     {
         static KeepAlive instance;
         return &instance;
     }
    
    void Init(void);
    
    protected:
    BOOL RunTask(void);
    
    private:
    
    typedef enum
    {
        STATE_NONE,
        STATE_ERROR,
        STATE_START,
        STATE_RUN
    }State;
    
    State state;

    sOS::TaskManager *taskManager;
        
    sOS::Task *task;  
    
    sOS::Timer *timer;
    
    void Start(void);
    void Run(void);
};

