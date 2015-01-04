/* GUIController.cpp 
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

#include "GUIController.hpp"

using namespace std; // I'm lazy

GUIController::GUIController(shared_ptr<Thermostat> therm, shared_ptr<NetworkListener> net)
{
    m_thermostat = therm;
    m_networkListener = net;
}

float GUIController::getOutdoorTemperature() { return -1.0f; }
float GUIController::getIndoorTemperature() { return -1.0f; }
float GUIController::getOutdoorHumidity() { return -1.0f; }
float GUIController::getIndoorHumidity() { return -1.0f; }

bool GUIController::isACRunning() { return false; }
bool GUIController::isHeatRunning() { return false; }
bool GUIController::isFanRunning() { return false; }

