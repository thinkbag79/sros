#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

#include "../message_module_type.h"

struct Message
{
    MessageType type;
    void *data;
    size_t size;
};

class MessageQueue
{
private:
    std::queue<Message> queue;
    std::mutex mutex;
    std::condition_variable cv;

public:
    void push(const Message &msg)
    {
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(msg);
        cv.notify_one();
    }

    bool pop(Message &msg)
    {
        std::unique_lock<std::mutex> lock(mutex);
        cv.wait(lock, [this]{ return !queue.empty(); });
        msg = queue.front();
        queue.pop();
        return true;
    }
};

#endif /* _MESSAGE_H_ */