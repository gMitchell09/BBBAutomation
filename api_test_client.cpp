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
    API_impl cAPI(false);

    float temp = 99.0f;
    printf("&temp: %p\n", &temp);
    cAPI.CallFunction(API::ReadTemp, NULL, 0, &temp, sizeof(temp));
    printf("Temp: %x\n", temp);
    printf("Current temperature is: %f\n", temp);
}
