#include <chrono>

#include "module.h"
#include "system.h"

void *Module::runHelper(void *context)
{
    return ((Module *)context)->run();
}

void *Module::run()
{
    onStart();

    while (running)
    {
        Message msg;

        if (queue.pop(msg))
        {
            processMessage(msg);

            if (msg.data != nullptr)
                delete[] static_cast<char *>(msg.data);
        }

        auto now = std::chrono::steady_clock::now();
        for (auto &[messageType, interval] : timerIntervals)
        {
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTimer[messageType]).count() >= interval)
            {
                lastTimer[messageType] = now;
                Message timerMsg{messageType, nullptr, 0};
                queue.push(timerMsg);
            }
        }

        // usleep(1);
    }

    onStop();

    return nullptr;
}

void Module::start()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (stackSize > 0)
    {
        pthread_attr_setstacksize(&attr, stackSize);
    }

    pthread_create(&worker, &attr, runHelper, this);

    if (threadPriority > 0)
    {
        sched_param sch;
        sch.sched_priority = threadPriority;
        pthread_setschedparam(worker, SCHED_FIFO, &sch);
    }
    pthread_attr_destroy(&attr);
}

void Module::stop()
{
    running = false;
    pthread_join(worker, nullptr);
}

void Module::setSystem(System *sys)
{
    system = sys;
}

void Module::setThreadParam(int priority, size_t stack)
{
    threadPriority = priority;
    stackSize = stack;
}

void Module::add_timer(MessageType messageType, int milli_interval)
{
    timerIntervals[messageType] = milli_interval;
    lastTimer[messageType] = std::chrono::steady_clock::now();
}

void Module::remove_timer(MessageType messageType)
{
    timerIntervals.erase(messageType);
    lastTimer.erase(messageType);
}

void Module::sendMessage(ModuleType moduleType, const Message &msg)
{
    if (system)
    {
        system->brokerMessage(moduleType, msg);
    }
}

void Module::insertMessage(const Message &msg)
{
    queue.push(msg);
}