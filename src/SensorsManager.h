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

#include <memory>
#include <vector>
#include <atomic>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <condition_variable>
#include <chrono>

#include "Sensor.h"

class SensorsManager {

public:

    SensorsManager() : started(false), stopped(false) {

    }

    void start();

    void stop();

    bool isStarted();

    bool isStopped();

    void addSensor(std::shared_ptr<Sensor> sensor);

private:

    void run();

    std::vector<std::shared_ptr<Sensor> > sensors;

    std::atomic<bool> started;
    std::atomic<bool> stopped;

    std::mutex sensor_mtx;

    std::thread fetch_thread;

};