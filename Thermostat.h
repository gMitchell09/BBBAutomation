#ifndef THERMO_H
#define THERMO_H

#include <vector>
#include <ctime>
#include "BlackLib/BlackLib.h"

using namespace std;

class Thermostat {
public:
    
    Thermostat(BlackLib::BlackGPIO *tempPin);

    float ReadTemp();
    void AddSchedule(float temp, time_t begin, time_t end);
    void RemoveSchedule(time_t being, time_t end);

    bool ShouldRunHeat(time_t time);
    bool ShouldRunAC(time_t time);
    bool ShouldRunFan(time_t time);

    float TargetTemp(time_t time);
    void EnableFan();
    void DisableFan();

    void PrintSchedule();

private:
    BlackLib::BlackGPIO *m_tempPin;
    float m_schedule[7][24];
    bool m_manualFan;
};

#endif
