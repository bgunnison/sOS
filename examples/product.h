///
/// @file product.h
/// @copyright Brian Gunnison (c) 2026
///
/// @brief main class for the example sOS API
///
/// @details 
///
#pragma once
#include "sOS_task_manager.h"

// only one
class Product
{
    
public:

    // singleton
    static Product* GetInstance()
    {
        static Product instance;
        return &instance;
    }


    /// @brief Initializes the product
    void Init(void);
    void MainLoop();

private:
    sOS::TaskManager* taskManager;


};
