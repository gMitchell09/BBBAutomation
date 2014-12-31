BBBAutomation
=============
Main focus at the moment is transparent message passing between the REST server and the actual application.  Current setup:

_Client_
```
int main()
{
    API cAPI(/* isServer */ false);
    float temperature;
    cAPI.CallFunction(API::ReadTemp, NULL, 0, &temp, sizeof(temperature));
    printf("Current temperature: %f", temperature);
}
```

_Server_
```
class API_impl : public API
{
public:
    API_impl(bool isServer) : API(isServer) {}
    virtual void Callback(API_CALL call, const void *rcvData, const size_t rcvDataLen, 
        void *&sendData, int *sendDataLen)
    {
        if (call == API::ReadTemp)
        {
            sendData = new float;
            *((float*)sendData) = 81.5f;
            *sendDataLen = sizeof(float);
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
    }
    return 0;
}
```
