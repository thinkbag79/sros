#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <map>
#include <cstddef>
#include "../application/message_module_type.h"

class Module;
class Message;

class System
{
private:
    std::map<ModuleType, Module *> modules;

public:
    void registerModule(ModuleType type, Module *module, int priority, size_t stack);
    void startAll();
    void stopAll();
    void brokerMessage(ModuleType moduleType, const Message &msg);
};

#endif /* _SYSTEM_H_ */