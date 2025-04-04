#include "system.h"
#include "module.h"

void System::registerModule(ModuleType type, Module *module, int priority, size_t stack)
{
    modules[type] = module;
    module->setSystem(this);
    module->setThreadParam(priority, stack);
}

void System::startAll()
{
    for (auto &pair : modules)
    {
        pair.second->start();
    }
}

void System::stopAll()
{
    for (auto &pair : modules)
    {
        pair.second->stop();
    }
}

void System::brokerMessage(ModuleType moduleType, const Message &msg)
{
    if (modules.find(moduleType) != modules.end())
    {
        modules[moduleType]->insertMessage(msg);
    }
}