#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <unistd.h>

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
                sendData = new bool;
                *sendDataLen = sizeof(bool);
                *((bool*)sendData) = isFanRunning;
                printf("Should run fan: %d\n", isFanRunning);
                break;
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

int main()
{
    API_impl sAPI(true);

    while (true)
    {
        sleep(1);
        sAPI.CallbackWrapper();
        printf("Next!\n");
    }
    return 0;
}

