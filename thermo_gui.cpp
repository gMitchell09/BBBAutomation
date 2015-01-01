/* thermo_gui.cpp - Main application interface
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

#include <gtkmm.h>
#include <iostream>

#include "BlackLib/BlackLib.h"

#define UI_FILE "thermo_layout.xml"

#define LED0 BlackLib::GPIO_30
#define LED1 BlackLib::GPIO_31
#define LED2 BlackLib::GPIO_60
#define LED3 BlackLib::GPIO_51

void toggleLed();


BlackLib::BlackGPIO *gpio[4];

void initializeGPIO()
{
    gpio[0] = new BlackLib::BlackGPIO(LED0, BlackLib::output);
    gpio[1] = new BlackLib::BlackGPIO(LED1, BlackLib::output);
    gpio[2] = new BlackLib::BlackGPIO(LED2, BlackLib::output);
    gpio[3] = new BlackLib::BlackGPIO(LED3, BlackLib::output);

}

void destroyGPIO()
{
    for (int i = 0; i < 4; i++)
        delete gpio[i];
}

int main(int argc, char *argv[])
{
    initializeGPIO();

    Gtk::Main kit(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder;
    try {
        builder = Gtk::Builder::create_from_file(UI_FILE);
    }
    catch (const Glib::FileError &ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    Gtk::Window *main_win = NULL;
    builder->get_widget("MainWindow", main_win);
    Gtk::Button *button1;
    builder->get_widget("button1", button1);

    button1->signal_clicked().connect(sigc::ptr_fun(&toggleLed));

	if (main_win) {
        kit.run(*main_win);
    }

    destroyGPIO();
    return 0;
}

void toggleLed() {
    gpio[0]->toggleValue();
    gpio[1]->toggleValue();
    gpio[2]->toggleValue();
    gpio[3]->toggleValue();
}
