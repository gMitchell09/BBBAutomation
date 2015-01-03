#ifndef MYWINDOW_HPP
#define MYWINDOW_HPP

/* MyWindow.hpp 
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

class MyWindow : public Gtk::Window {
 
  public:
    MyWindow () : thrashHive("Go!") {
      bee = NULL;
      thrashHive.signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::go));
      add(thrashHive);
      show_all();
    }
 
    void go () {
      if(bee != NULL)
        return;
 
      bee = new Worker();
      bee->sig_done.connect(sigc::mem_fun(*this, &MyWindow::beeDone));
      bee->start();
 
      thrashHive.set_sensitive(false);
      thrashHive.set_label("Working");
    }
 
    void beeDone () {
      delete bee;
      bee = NULL;
      thrashHive.set_sensitive(true);
      thrashHive.set_label("Go!");
    }
 
  private:
    Gtk::Button thrashHive;
    Worker * bee;
 
};

#endif
