#include "framework/module.h"
#include <iostream>

class ModuleA : public Module
{
protected:
    void onStart() override
    {
        printf("module A start\n");

        add_timer(MessageType::TIMER_EVENT, 1000);
    }

    void onStop() override
    {
        printf("module A stop\n");
    }
    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_EVENT)
        {
            std::cout << "ModuleA timer event" << std::endl;
        }
    }
};

class ModuleB : public Module
{
protected:
    void onStart() override
    {
        printf("module B start\n");
    }

    void onStop() override
    {
        printf("module B stop\n");
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
        printf("module C start\n");
    }

    void onStop() override
    {
        printf("module C stop\n");
    }

    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_EVENT)
        {
            std::cout << "ModuleC timer event, ID: " << std::endl;
        }
    }
};