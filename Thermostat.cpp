#include <iostream>
#include <algorithm>
#include <cstdlib>
#include "thermo.h"
#include "BlackLib/BlackLib.h"

Thermostat::Thermostat(BlackLib::BlackGPIO *tempPin)
{
    m_tempPin = tempPin;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 24; ++j)
        {
            m_schedule[i][j] = -1.0f;
        }
    }
}

float Thermostat::ReadTemp() 
{
    // do thermo reading stuff here.
    // for now, let's use random.
    srand(NULL);
    return static_cast<float>((rand()) / (static_cast<float>(RAND_MAX)/30)) + 50.0f;
}

void Thermostat::AddSchedule(float temp, time_t begin, time_t end)
{
    struct tm *beginTime = localtime(&begin);
    struct tm *endTime = localtime(&end);

    size_t endInt = endTime->tm_wday * 24 + endTime->tm_hour;
    size_t beginInt = beginTime->tm_wday * 24 + beginTime->tm_hour;

    for (int i = beginInt; i < endInt; ++i)
    {
        m_schedule[i/24][i%24] = temp;
    }
}

void Thermostat::RemoveSchedule(time_t begin, time_t end)
{
    this->AddSchedule(-1, begin, end);
}

bool Thermostat::ShouldRunHeat(time_t time)
{
    float targetTemp = this->TargetTemp(time);    
    if (targetTemp == -1) return false;
    if (ReadTemp() < targetTemp) return true;
}

bool Thermostat::ShouldRunAC(time_t time)
{
    float targetTemp = this->TargetTemp(time);    
    if (targetTemp == -1) return false;
    if (ReadTemp() < targetTemp) return true;
}

float Thermostat::TargetTemp(time_t time)
{
    struct tm *currentTime = localtime(&time);

    size_t timeInt = currentTime->tm_wday * 24 + currentTime->tm_hour;
    float targetTemp = m_schedule[currentTime->tm_wday][currentTime->tm_hour];
    
    return targetTemp;
}

void Thermostat::EnableFan()
{
    m_manualFan = true;
}

void Thermostat::DisableFan()
{
    m_manualFan = false;
}

bool Thermostat::ShouldRunFan(time_t time)
{
    return m_manualFan || ShouldRunAC(time) || ShouldRunHeat(time);
}

void Thermostat::PrintSchedule()
{
    std::cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\t" << std::endl;
    for (int i = 0; i < 24; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            std::cout << m_schedule[j][i] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
