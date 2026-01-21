///
/// @file sOS_task_manager.h
/// @copyright Brian Gunnison(c) 2026
///
/// @brief Manages and schedules tasks for execution.
///
/// @details This file contains the sOS::TaskObject, sOS::Task, and sOS::TaskManager classes.
/// TaskObjects are base objects that other classes inherit from to create executable tasks.
/// sOS::Tasks manage these TaskObjects. The TaskManager is responsible for creating, deleting,
/// and executing these tasks.
///
#pragma once

#include "sOS_timer_manager.h"

namespace sOS
{

    // a task typically waiting for something to complete, running a state machine
    // tasks are doubly linked in a active task list where their current state is called
    // or linked in a free task list awaiting use.

    // Classes inherit from this so the TaskManager can call its RunTask.
    class TaskObject
    {
    public:

        /// @brief Virtual function to be overridden by the inheriting class.
        /// Represents the task to be run.
        /// @return TRUE to keep task active, FALSE to indicate fatal error.
        virtual BOOL RunTask() = 0;
    };

    class Task
    {
    public:

        /// @brief Initializes a task node and clears its task object.
        /// @param prev Previous task in the list.
        /// @param next Next task in the list.
        void Init(Task* prev, Task* next);

        /// @brief Defines potential errors in a sOS::Task.
        typedef enum
        {
            TASK_ERROR_NONE,
            TASK_ERROR_NULL_TASK,
            TASK_ERROR_FATAL    // if task obj runs into something where it can't delete its task
        }TaskError;

        /// @brief Sets the task object to be run by this task node.
        /// @param taskObj Task object instance to execute.
        void SetTaskObject(TaskObject* taskObj) { activeTaskObj = taskObj; }

        /// @brief Executes the task object.
        /// @return sOS::TaskError indicating task execution result.
        TaskError CallTask(void);

        /// @brief Gets the previous task in the task list.
        Task* GetPrevTask(void) { return taskprev; }

        /// @brief Gets the next task in the task list.
        Task* GetNextTask(void) { return tasknext; }

        /// @brief Sets the previous task in the task list.
        void SetPrevTask(Task* task) { taskprev = task; }

        /// @brief Sets the next task in the task list.
        void SetNextTask(Task* task) { tasknext = task; }


    private:

        Task* taskprev;
        Task* tasknext;

        /// @brief Task object to execute when scheduled (NULL if unused).
        TaskObject* activeTaskObj;
    };

    // only one
    // RunTasks called in main loop to call invoke current state in each active task
    // tasks are allocated out of the free tasks and put in the active tasks
    // tasks are doubly linked so they can be taken out of the middle of the active list.
    class TaskManager
    {
    public:

        /// @brief Singleton instance of the TaskManager.
        static TaskManager* GetInstance()
        {
            static TaskManager instance;
            return &instance;
        }

        /// @brief Initializes the TaskManager.
        /// @details Links the free list and acquires the task timing guard.
        void Init(void);

        /// @brief Adds a new active task to the task list.
        /// @param taskObj Task object to execute.
        /// @param name Optional debug name (may be unused).
        /// @return Pointer to the allocated task node or NULL on failure.
        Task* AddActiveTask(TaskObject* taskObj, const char* name);

        /// @brief Deletes an active task from the task list.
        /// @param task Reference to task pointer; set to NULL on success.
        void DeleteActiveTask(Task*& task); // nulls task pointer

        /// @brief Checks if a task is active.
        /// @param task Task node to verify.
        /// @return TRUE if task is in the active list.
        BOOL IsActiveTask(Task* task);

        /// @brief Executes the next task in the list.
        /// @details Uses round-robin scheduling across active tasks.
        void RunNextTask(void);

    private:

        /// @brief Timer used to detect slow task execution.
        Timer* taskTimer;
        /// @brief Longest observed task runtime in milliseconds.
        uint16_t peakTaskTime;

        /// @brief Total number of task slots in the pool.
        static const uint8_t NUM_TASKS = 32;
        /// @brief Storage for all task nodes.
        Task tasks[NUM_TASKS];
        /// @brief Head of free task list.
        Task* freeTaskList;
        /// @brief Head of active task list.
        Task* activeTaskList;
        /// @brief Current task in round-robin schedule.
        Task* currentActiveTask;

        /// @brief Allocates a task node from the free list.
        Task* GetNewTask();
        /// @brief Returns a task node to the free list.
        void FreeTask(Task* task);
    };
} // namespace sOS
