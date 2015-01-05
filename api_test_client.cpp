/* api_test_client.cpp - Client testbed for message passing API
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
//                    cAPI.CallFunction(API::ShouldRunFan, &tickCount, sizeof(tickCount), &shouldRunFan, sizeof(shouldRunFan));

                    shouldRunFan = cAPI.t_func<bool, time_t>(API::ShouldRunFan, tickCount);
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
