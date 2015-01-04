#ifndef GUICONTROLLER_HPP
#define GUICONTROLLER_HPP

/* GUIController.hpp 
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

#include <shared_ptr>

// Forward decl to improve preprocess/compile time.
class Thermostat;
class NetworkListener;

class GUIController
{
public:
    GUIController(std::shared_ptr<Thermostat> therm, std::shared_ptr<NetworkListener>);
    float getOutdoorTemperature();
    float getIndoorTemperature();
    float getOutdoorHumidity();
    float getIndoorHumidity();

    bool isACRunning();
    bool isHeatRunning();
    bool isFanRunning();
private:
    std::shared_ptr<Thermostat> m_thermostat;
    std::shared_ptr<NetworkListener> m_networkListener;
}

#endif


