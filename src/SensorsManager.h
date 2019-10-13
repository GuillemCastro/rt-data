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
#include <chrono>

#include "Sensor.h"

/**
 * A manager for Sensors. Responsible of the correct life-cycle management
 * of the sensors. Will start, stop and fetch data from the sensors.
 */
class SensorsManager {

public:

    /**
     * Default constructor
     */
    SensorsManager() : started(false), broker(NULL) {

    }

    /**
     * Destructor
     */
    ~SensorsManager() {
        try {
            if (is_started()) {
                stop();
            }
        }
        catch (std::runtime_error&) {
            //Already stopped
        }
    }

    /**
     * Start the manager. It starts the internal thread, and the sensors
     * @throws std::runtime_error If the manager is stopped or already started
     */
    void start();

    /**
     * Stops the manager. It stops and joins the internal thread, and the sensors
     * @throws std::runtime_error If the manager is already stopped or not started
     */
    void stop();

    /**
     * Is the manager started?
     * @returns Whether or not the manager has been started
     */
    bool is_started() const;

    /**
     * Is the manager stopped?
     * @returns Whether or not the manager has been stopped
     */
    bool is_stopped() const;

    /**
     * Add a new sensor and if the manager is already started, start the sensor
     * @params sensor A pointer to the sensor to be added
     * @throws std::runtime_error If the manager is stopped
     */
    void add_sensor(std::shared_ptr<Sensor> sensor);

    /**
     * Remove a sensor from the manager
     * @params sensor A pointer to the sensor to be removed
     * Note: No exception is thrown if the manager is stopped
     */
    void remove_sensor(std::shared_ptr<Sensor> sensor);

    /**
     * Set the broker that will dispatch the data fetched by this manager
     * @param broker A pointer to a Broker
     */
    void set_broker(Broker* broker);

private:

    /**
     * Internal thread function. Fetch the read data by the sensors.
     */
    void run();

    std::vector<std::shared_ptr<Sensor> > sensors;

    std::atomic<bool> started;

    std::mutex sensor_mtx;

    std::thread fetch_thread;

    Broker* broker;

};