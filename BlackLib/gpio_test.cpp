#include "BlackLib.h"
#include <iostream>

#define USR0 BlackLib::GPIO_30
#define USR1 BlackLib::GPIO_31
#define USR2 BlackLib::GPIO_60
#define USR3 BlackLib::GPIO_51

using namespace BlackLib;
using namespace std;
int main()
{
    cout << "woot!" << endl;
    BlackGPIO led0(USR0, output);
    BlackGPIO led1(USR1, output);
    BlackGPIO led2(USR2, output);
    BlackGPIO led3(USR3, output);
   
    BlackGPIO *leds[4];
    leds[0] = new BlackGPIO(USR0, output);
    leds[1] = new BlackGPIO(USR1, output);
    leds[2] = new BlackGPIO(USR2, output);
    leds[3] = new BlackGPIO(USR3, output);

    cout << leds[0]->getValue() << endl;

    int currentLed = 0;
    while (true)
    {
        std::cout << "in" << std::endl;
        leds[currentLed]->setValue(high);
        sleep(1);
        leds[currentLed]->setValue(low);
        currentLed++;
        currentLed %= 4;

        std::cout << currentLed << std::endl;
    }

    return 0;
}
