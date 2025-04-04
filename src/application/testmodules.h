#include "framework/module.h"
#include <iostream>

class ModuleA : public Module
{
protected:
    void onStart() override
    {
    }

    void onStop() override
    {
    }
    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_EVENT)
        {
            std::cout << "ModuleA timer event, ID: " << std::endl;
        }
    }
};

class ModuleB : public Module
{
protected:
    void onStart() override
    {
    }

    void onStop() override
    {
    }

    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_EVENT)
        {
            std::cout << "ModuleB timer event, ID: " << std::endl;
        }
    }
};

class ModuleC : public Module
{
protected:
    void onStart() override
    {
    }

    void onStop() override
    {
    }

    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_EVENT)
        {
            std::cout << "ModuleC timer event, ID: " << std::endl;
        }
    }
};