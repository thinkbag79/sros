#ifndef _MESSAGE_MODULE_TYPE_H_
#define _MESSAGE_MODULE_TYPE_H_

enum class ModuleType
{
    MODULE_A,
    MODULE_B,
    MODULE_C
};

enum class MessageType
{
    TIMER_EVENT,
    INT_ARRAY,
    CV_MAT,
};

struct TimerData
{
    int timerID;
};

#endif /* _MESSAGE_MODULE_TYPE_H_ */