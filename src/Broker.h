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

#include <thread>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <functional>
#include <stdexcept>
#include <mutex>

#include "Data.h"
#include "concurrent/ThreadPool.h"

class Broker {

public:

    /**
     * Default constructor
     */
    Broker() : started(false), stopped(false) {

    }

    /**
     * Destructor. Stops the broker.
     */
    ~Broker() {
        try {
            stop();
        }
        catch (std::runtime_error&) {
            //Already stopped
        }
    }

    /**
     * Start the Broker
     */
    void start();

    /**
     * Stop the Broker. No more events will be dispatched after.
     */
    void stop();

    /**
     * Is the Broker started?
     * @returns returs wheter the Broker is started or not
     */
    bool isStarted();

    /**
     * Is the Broker stopped?
     * @returns returs wheter the Broker is stopped or not
     */
    bool isStopped();

    /**
     * Subscribe a listener to a topic
     * @param topic The topic to subscribe to
     * @param listener A function that will be executed when an event from the passed
     *      topic is dispatched.
     */
    void subscribe(std::string topic, std::function<void(std::string, std::shared_ptr<Data>)> listener);

    /**
     * Dipatch an event to a topic with an associated data
     * @param topic The topic where the event will be dispatched
     * @param data The data associated with the event
     */
    void dispatch(std::string topic, std::shared_ptr<Data> data);

private:

    std::atomic<bool> started, stopped;

    std::unordered_map<std::string, std::vector<std::function<void(std::string, std::shared_ptr<Data>)>>> listeners;

    std::mutex mtx;

    ThreadPool pool;

};