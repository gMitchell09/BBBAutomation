#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <unistd.h>

#include "SockAPI.hpp"

using namespace std;
class API;
class API_impl : public API
{
public:
    API_impl(bool isServer) : API(isServer) {}
};

int main()
{
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
                printf("Temp: %x\n", temp);
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
                bool shouldRunFan;
                time_t time;
                cAPI.CallFunction(API::ShouldRunFan, &time, sizeof(time), &shouldRunFan, sizeof(shouldRunFan));
                printf("Should run fan: %s\n", (shouldRunFan) ? "yes" : "no");
                break;
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
    }
}
