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

#include "SensorsManager.h"

void SensorsManager::addSensor(std::shared_ptr<Sensor> sensor) {
    if (stopped) {
        throw std::runtime_error("Cannot add a new Sensor to a stopped SensorsManager");
    }
    //Avoid adding a sensor while fetching data from sensors
    std::unique_lock<std::mutex> lck(sensor_mtx);
    sensors.push_back(sensor);
    if (started) {
        sensor->start();
    }
}

void SensorsManager::removeSensor(std::shared_ptr<Sensor> sensor) {
    std::unique_lock<std::mutex> lck(sensor_mtx);
    for (int i = 0; i < sensors.size(); ++i) {
        if (sensors[i] == sensor) {
            sensors.erase(sensors.begin() + i);
        }
    }
}

void SensorsManager::start() {
    if (started || stopped) {
        throw std::runtime_error("Cannot start already started or stopped SensorsManager");
    }
    for (auto& sensor : sensors) {
        if (!sensor->isStarted() && !sensor->isStopped()) {
            sensor->start();
        }
    }
    fetch_thread = std::thread(&SensorsManager::run, this);
    started = true;
}

void SensorsManager::stop() {
    if (!started || stopped) {
        throw std::runtime_error("Cannot stop not started or already stopped SensorsManager");
    }
    for (auto& sensor : sensors) {
        if (!sensor->isStopped() && sensor->isStarted()) {
            sensor->stop();
        }
    }
    stopped = true;
    fetch_thread.join();
}

void SensorsManager::run() {

    std::unique_lock<std::mutex> lck(sensor_mtx);
    while (!stopped) {
        lck.lock();
        for (auto& sensor : sensors) {
            std::vector<double> res;
            sensor->fetch(res);
        }
        lck.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

}

void SensorsManager::isStarted() {
    return started;
}

void SensorsManager::isStopped() {
    return stopped;
}