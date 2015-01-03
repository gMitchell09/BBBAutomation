/* NetworkListener.cpp 
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

#include "NetworkListener.hpp"

NetworkListener::NetworkListener() : thread(0), stop(false) {}

void NetworkListener::start()
{
    thread = Glib::Thread::create(sigc::mem_fun(*this, &NetworkListener::run), true);
}

NetworkListener::~NetworkListener()
{
    {
        Glib::Mutex::Lock lock(mutex);
        stop = true;
    }
    if (thread) thread->join();
}

void NetworkListener::run()
{
    while (true)
    {
        {
            Glib::Mutex::Lock lock (mutex);
            if (stop) break;
        }

        sleep(5);
        std::cout << "Thread write!" << std::endl;
        sig_done();
        break;
    }
}

