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
    virtual void Callback(API_CALL call, const void *rcvData, const size_t rcvDataLen, void *sendData, int *sendDataLen)
    {
        switch (call)
        {
            case ReadTemp:
                printf("ReadTemp!!\n");
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
    API_impl cAPI(false);

    cAPI.CallFunction(API::ReadTemp);
    sleep(1);
    sAPI.CallbackWrapper();
}
