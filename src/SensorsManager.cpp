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

void SensorsManager::add_sensor(std::shared_ptr<Sensor> sensor) {
    //Avoid adding a sensor while fetching data from sensors
    std::unique_lock<std::mutex> lck(sensor_mtx);
    sensors.push_back(sensor);
    if (started) {
        sensor->start();
    }
}

void SensorsManager::remove_sensor(std::shared_ptr<Sensor> sensor) {
    std::unique_lock<std::mutex> lck(sensor_mtx);
    for (std::size_t i = 0; i < sensors.size(); ++i) {
        if (sensors[i] == sensor) {
            sensors.erase(sensors.begin() + i);
        }
    }
}

void SensorsManager::start() {
    if (started) {
        throw std::runtime_error("Cannot start already started SensorsManager");
    }
    std::unique_lock<std::mutex> lck(sensor_mtx);
    for (auto& sensor : sensors) {
        if (!sensor->is_started() && !sensor->is_stopped()) {
            sensor->start();
        }
    }
    fetch_thread = std::thread(&SensorsManager::run, this);
    started = true;
}

void SensorsManager::stop() {
    if (!started) {
        throw std::runtime_error("Cannot stop not started or already stopped SensorsManager");
    }
    std::unique_lock<std::mutex> lck(sensor_mtx);
    for (auto& sensor : sensors) {
        if (!sensor->is_stopped() && sensor->is_started()) {
            sensor->stop();
        }
    }
    started = false;
    fetch_thread.join();
}

void SensorsManager::run() {
    //Defer to avoid deadlock
    std::unique_lock<std::mutex> lck(sensor_mtx, std::defer_lock);
    while (started) {
        lck.lock();
        if (broker != NULL) {
            for (auto& sensor : sensors) {
                sensor->fetch(broker);
            }
        }
        lck.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool SensorsManager::is_started() const {
    return started;
}

bool SensorsManager::is_stopped() const {
    return !started;
}

void SensorsManager::set_broker(Broker* broker) {
    this->broker = broker;
}