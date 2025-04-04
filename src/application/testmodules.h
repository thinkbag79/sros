#include "framework/module.h"
#include <iostream>

class ModuleA : public Module
{
protected:
    void onStart() override
    {
        printf("module A start\n");

        add_timer(MessageType::TIMER_1SEC, 1);
        add_timer(MessageType::TIMER_5SEC, 5000);
    }

    void onStop() override
    {
        printf("module A stop\n");
    }
    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_1SEC)
        {
            std::cout << "ModuleA timer 1sec event" << std::endl;

            Message msg{MessageType::MSG_COW, nullptr, 0};
            sendMessage(ModuleType::MODULE_B, msg);            
        }
        else if (msg.type == MessageType::TIMER_5SEC)
        {
            std::cout << "ModuleA timer 5sec event" << std::endl;
        }
        else if(msg.type == MessageType::MSG_DOG)
        {
            std::cout << "ModuleA : receive DOG" << std::endl;
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
        if (msg.type == MessageType::TIMER_1SEC)
        {
            std::cout << "ModuleB timer event, ID: " << std::endl;
        }
        else if(msg.type == MessageType::MSG_COW)
        {
            std::cout << "ModuleB : receive COW" << std::endl;

            Message msg{MessageType::MSG_DOG, nullptr, 0};
            sendMessage(ModuleType::MODULE_A, msg); 
        }
    }
};

class ModuleC : public Module
{
protected:
    void onStart() override
    {
        add_timer(MessageType::TIMER_5SEC, 5000);
        printf("module C start\n");
    }

    void onStop() override
    {
        printf("module C stop\n");
    }

    void processMessage(const Message &msg) override
    {
        if (msg.type == MessageType::TIMER_5SEC)
        {
            std::cout << "ModuleC timer event, ID: " << std::endl;
        }
    }
};