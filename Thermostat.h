/* Thermostat.h
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
