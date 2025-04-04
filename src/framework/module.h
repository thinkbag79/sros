#ifndef _MODULE_H_
#define _MODULE_H_

#include <pthread.h>
#include <map>

#include "message.h"
#include "../application/message_module_type.h"

class System;

class Module
{
public:
    void start();
    void stop();
    void setSystem(System *sys);
    void setThreadParam(int priority, size_t stack);
    void insertMessage(const Message &msg);

protected:
    Module() : running(true), system(nullptr), threadPriority(0), stackSize(0) {}
    void add_timer(MessageType messageType, int interval);
    void remove_timer(MessageType messageType);
    void sendMessage(ModuleType moduleType, const Message &msg);
    
    virtual void onStart() = 0;
    virtual void onStop() = 0;
    virtual void processMessage(const Message &msg) = 0;

private:
    MessageQueue queue;
    pthread_t worker;
    bool running;
    System *system;
    std::map<MessageType, int> timerIntervals;
    std::map<MessageType, std::chrono::steady_clock::time_point> lastTimer;
    int threadPriority;
    size_t stackSize;

    static void* runHelper(void* context);
    void* run();
};

#endif /* _MODULE_H_ */