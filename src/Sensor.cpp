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

#include "Sensor.h"

void Sensor::start() {
    if (started || stopped) {
        throw std::runtime_error("Sensor already started or stopped!");
    }
    this->sensor_thread = std::thread(&Sensor::run, this);
    this->started = true;
}

void Sensor::stop() {
    if (!started || stopped) {
        throw std::runtime_error("Sensor not started or already stopped!");
    }
    this->stopped = true;
    this->sensor_thread.join();
}

bool Sensor::isStarted() {
    return started;
}

bool Sensor::isStopped() {
    return stopped;
}

void Sensor::run() {
    while (!stopped) {
        this->read();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}