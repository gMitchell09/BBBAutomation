#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

/* MainWindow.hpp
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

class GUIController;
class NetworkListener;

class MainWindow : public Gtk::Window
{
public:
    MainWindow(BaseObjectType* winObj, Glib::RefPtr<Gtk::Builder> &builder);

    void go();
    void listenerDone();
private:
    Gtk::Button *button1;
    NetworkListener *listener;
    GUIController *m_controller;
};

#endif


