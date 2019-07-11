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
    this->sensor_thread = Thread(&Sensor::run, this);
    try {
        int priority = Thread::getMaxSchedulingPriority(SchedulingPolicy::RT_ROUND_ROBIN) - 1;
        this->sensor_thread.setSchedulingPolicy(SchedulingPolicy::RT_ROUND_ROBIN, priority);
    }
    catch (std::runtime_error& ex) {
        Log::log(WARNING) << "[" << name << "] While setting the sensor's thread scheduling policy an exception was thrown: " << ex.what();
        Log::log(WARNING) << "[" << name << "] Are you running as sudo?";
    }
    this->started = true;
}

void Sensor::stop() {
    if (!started || stopped) {
        throw std::runtime_error("Sensor not started or already stopped!");
    }
    this->stopped = true;
    this->sensor_thread.join();
}

bool Sensor::isStarted() const {
    return started;
}

bool Sensor::isStopped() const {
    return stopped;
}

void Sensor::run() {
    while (!stopped) {
        this->read();
        std::this_thread::sleep_for(std::chrono::nanoseconds(sampling_rate));
    }
}

void Sensor::fetch(Broker* broker) {
    while (!queue.empty()) {
        std::shared_ptr<Data> data = queue.pop();
        broker->dispatch(topic, data);
    }
}

std::string Sensor::getName() const {
    return name;
}

std::string Sensor::getTopic() const {
    return topic;
}

uint64_t Sensor::getSamplingRate() const {
    return sampling_rate;
}

void Sensor::setName(const std::string& name) {
    this->name = name;
}

void Sensor::setTopic(const std::string& topic) {
    this->topic = topic;
}

void Sensor::setSamplingRate(uint64_t rate) {
    this->sampling_rate = rate;
}