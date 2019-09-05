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
        int priority = Thread::get_max_scheduling_priority(SchedulingPolicy::RT_ROUND_ROBIN) - 1;
        this->sensor_thread.set_scheduling_policy(SchedulingPolicy::RT_ROUND_ROBIN, priority);
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

bool Sensor::is_started() const {
    return started;
}

bool Sensor::is_stopped() const {
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

std::string Sensor::get_name() const {
    return name;
}

std::string Sensor::get_topic() const {
    return topic;
}

uint64_t Sensor::get_sampling_rate() const {
    return sampling_rate;
}

void Sensor::set_name(const std::string& name) {
    this->name = name;
}

void Sensor::set_topic(const std::string& topic) {
    this->topic = topic;
}

void Sensor::set_sampling_rate(uint64_t rate) {
    this->sampling_rate = rate;
}