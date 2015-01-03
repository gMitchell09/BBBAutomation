/* MainWindow.cpp 
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

#include "MainWindow.hpp"

MainWindow::MainWindow(Glib::RefPtr<Gtk::Builder> &builder)
{
    listener = NULL;
    builder->get_widget("button1", button1);
    button1->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::go));
    show_all();
}

void MainWindow::go()
{
    if (listener != NULL) return;

    listener = new NetworkListener();
    listener->sig_done.connect(sigc::mem_fun(*this, &MainWindow::listenerDone));
    listener->start();

    button1->set_sensitive(false);
    button1->set_label("Working...");
}

void MainWindow::listenerDone()
{
    delete listener;
    listener = NULL;
    button1->set_sensitive(true);
    button1->set_label("Go!");
}

