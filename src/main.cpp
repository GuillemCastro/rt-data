/**
 * rt-data
 * Copyright (C) 2019 Guillem Castro
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <signal.h>
#include <unistd.h>
#include <iostream>

#include "Application.h"
#include "Log.h"

bool stopped = false;

void signal_handler(int signo);

int main() {
    //Capture Ctrl+C
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        std::cerr << "ERROR: Cant set SIGINT signal handler. Exiting." << std::endl;
        exit(2);
    }

    Log::init();

    Application app;
    app.setup();
    while(!stopped) {
        app.loop();
    }
}

void signal_handler(int signo) {
    if (signo == SIGINT) {
        stopped = true;
    }
}
