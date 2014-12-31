#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <unistd.h>
#include <signal.h>

#include "SockAPI.hpp"

using namespace std;
class API;
class API_impl : public API
{
public:
    API_impl(bool isServer) : API(isServer) {}
};

static void user_signal(int signo) {
    printf("Caught signal: %d\n", signo);
}

static void kill_app(int signo) {
    printf("Killing app with signal: %d\n", signo);
    exit(signo);
}

static void fuck_you(int signo) {
    printf("Fuck. You. %d\n", signo);
    exit(signo);
}

int main()
{
    signal(SIGUSR1, user_signal);
    signal(SIGUSR2, user_signal);
    signal(SIGKILL, kill_app);
    signal(SIGABRT, kill_app);
    signal(SIGQUIT, kill_app);
    signal(SIGTERM, kill_app);
    signal(SIGSTOP, kill_app);
    signal(SIGTSTP, kill_app);
    signal(SIGPIPE, fuck_you);

    while (1)
    {
        API_impl cAPI(false);
        char c = getchar();
        switch (c)
        {
            case 'r':
            case 'R':
                float temp;
                printf("&temp: %p\n", &temp);
                cAPI.CallFunction(API::ReadTemp, NULL, 0, &temp, sizeof(temp));
                printf("Current temperature is: %f\n", temp);
                break;
            case 'a':
            case 'A':
                break;
            case 'b':
            case 'B':
                break;
            case 'c':
            case 'C':
                break;
            case 'h':
            case 'H':
                break;
            case 'f':
            case 'F':
                {
                    bool shouldRunFan;
                    time_t tickCount = time(NULL);
                    cAPI.CallFunction(API::ShouldRunFan, &tickCount, sizeof(tickCount), &shouldRunFan, sizeof(shouldRunFan));
                    printf("Should run fan: %s\n", (shouldRunFan) ? "yes" : "no");
                    break;
                }
            case 'e':
            case 'E':
                cAPI.CallFunction(API::EnableFan);
                printf("Fan enabled\n");
                break;
            case 'd':
            case 'D':
                cAPI.CallFunction(API::DisableFan);
                printf("Fan disabled\n");
                break;
        }
        sleep(1);
    }
}
