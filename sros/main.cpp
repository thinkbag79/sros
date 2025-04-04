#include <cstdio>
#include <signal.h>
#include <unistd.h>

#include "framework/system.h"
#include "testmodules.h"

volatile sig_atomic_t running = 1;

void signalHandler(int signum)
{
    running = 0;
}

int main()
{
    printf("\nstart program\n");

    signal(SIGINT, signalHandler); // 종료 신호 처리

    ModuleA moduleA;
    ModuleB moduleB;
    ModuleC moduleC;

    System system;

    system.registerModule(ModuleType::MODULE_A, &moduleA, 0, 0);
    system.registerModule(ModuleType::MODULE_B, &moduleB, 0, 0);
    system.registerModule(ModuleType::MODULE_C, &moduleC, 0, 0);

    system.startAll();

    while (running)
    {
        usleep(1000 * 1000);
    }

    system.stopAll();

    printf("\nexit program\n");

    return 0;
}