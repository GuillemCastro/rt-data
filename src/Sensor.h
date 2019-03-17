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

/**
 * A class to interface with a sensor. Provides methods
 * to manage sensor readings in background.
 */
class Sensor {

public:

    /**
     * Default constructor
     */
    Sensor() : started(false), stopped(false) {

    }

    /**
     * Starts the sensor and the internal reading thread.
     * Shall be overriden to configure the sensor.
     * @throws std::runtime_error if the sensor has been already started or if it was stopped.
     */
    virtual void start();

    /**
     * Stops the sensor and the internal reading thread.
     * Shall be overriden to release the sensor's resources.
     * @throws std::runtime_error if the sensor has been already stopped or if it was never started.
     */
    virtual void stop();

    /**
     * Is the sensor started?
     * @returns Whether or not the sensor has been started
     */
    virtual bool isStarted();

    /**
     * Is the sensor stopped?
     * @returns Whether or not the sensor has been stopped
     */
    virtual bool isStopped();

    /**
     * Fetch the read data by the sensor.
     * This interface allows sensors to perform "burst" reads, or
     * sensors that generate more than one data value.
     * @params res The vector where the fetched data will be stored.
     */
    virtual void fetch(std::vector<double>& res);

protected:

    /**
     * Internal read method. Must be overriden by a subclass.
     * THe results of the read must be saved to the `queue`.
     */
    virtual void read() = 0;

    /**
     * Internal thread-safe queue where the read data is stored. 
     */
    ConcurrentQueue<double> queue;

private:

    /**
     * Internal thread function. Calls the read() method periodically.
     */
    void run();

    std::atomic<bool> started;
    std::atomic<bool> stopped;

    std::thread sensor_thread;

};