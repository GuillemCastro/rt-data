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

#include "Broker.h"

void Broker::start() {
    if (started || stopped) {
        throw std::runtime_error("Cannot start already started or stopped Broker");
    }
    this->started = true;
}

void Broker::stop() {
    if (!started || stopped) {
        throw std::runtime_error("Cannot stop not started or already stopped Broker");
    }
    pool.join();
    this->stopped = true;
}

bool Broker::isStarted() {
    return started;
}

bool Broker::isStopped() {
    return stopped;
}

void Broker::subscribe(std::string topic, std::shared_ptr<Listener> listener) {
    if (stopped) {
        throw std::runtime_error("Cannot subscribe to a stopped Broker");
    }
    std::unique_lock<std::mutex> lck(mtx);
    listeners[topic].push_back(listener);
}

void Broker::dispatch(std::string topic, std::shared_ptr<Data> data) {
    if (!started || stopped) {
        throw std::runtime_error("Cannot dispatch before starting or after stopping the Broker");
    }
    std::unique_lock<std::mutex> lck(mtx);
    for (auto listener : listeners[topic]) {
        pool.addJob([this, listener, topic, data]() {
            listener->handle(topic, data);
        });
    }
}