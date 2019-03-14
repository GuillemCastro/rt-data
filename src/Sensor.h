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

#pragma once

#include <vector>
#include <atomic>
#include <thread>
#include "concurrent/ConcurrentQueue.h"

class Sensor {

public:

    Sensor() : started(false), stopped(false) {

    }

    virtual void start();

    virtual void stop();

    virtual bool isStarted();

    virtual bool isStopped();

    virtual void fetch(std::vector<double>& res);

protected:

    virtual void read() = 0;

    ConcurrentQueue<double> queue;

private:

    void run();

    std::atomic<bool> started;
    std::atomic<bool> stopped;

    std::thread sensor_thread;

};