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
            TimerData *timerData = static_cast<TimerData *>(msg.data);
            std::cout << "ModuleA timer event, ID: " << timerData->timerID << std::endl;
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
            TimerData *timerData = static_cast<TimerData *>(msg.data);
            std::cout << "ModuleB timer event, ID: " << timerData->timerID << std::endl;
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
            TimerData *timerData = static_cast<TimerData *>(msg.data);
            std::cout << "ModuleC timer event, ID: " << timerData->timerID << std::endl;
        }
    }
};