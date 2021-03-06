/* api_test.cpp - Server testbed for messaging
 * -----------------------------------------------------------------------------
 * Copyright (C) 2015 George Mitchell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <signal.h>

#include "SockAPI.hpp"

using namespace std;

bool isFanRunning;

class API;
class API_impl : public API
{
public:
    API_impl(bool isServer) : API(isServer) {}
    virtual void Callback(API_CALL call, const void *rcvData, const size_t rcvDataLen, void *&sendData, int *sendDataLen)
    {
        switch (call)
        {
            case ReadTemp:
                printf("ReadTemp!!\n");
                sendData = new float;
                *((float*)sendData) = 81.5f;
                *sendDataLen = sizeof(float);
                printf("exiting func\n");
                break;
            case ShouldRunFan:
                {
                    printf("Should run fan?\n");
                    time_t tickCount;
                    memcpy((void*)&tickCount, rcvData, rcvDataLen);
                    struct tm *time = localtime(&tickCount);
                    sendData = new bool;
                    *sendDataLen = sizeof(bool);
                    *((bool*)sendData) = isFanRunning;
                    printf("Should run fan: %d\n", isFanRunning);
                    break;
                }
            case EnableFan:
                isFanRunning = true;
                printf("Enable fan\n");
                break;
            case DisableFan:
                isFanRunning = false;
                printf("Disable fan\n");
                break;
            default:
                printf("Other!!\n");
                break;
        }
    }
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

    API_impl sAPI(true);

    while (true)
    {
        sleep(1);
        sAPI.CallbackWrapper();
    }
    return 0;
}

