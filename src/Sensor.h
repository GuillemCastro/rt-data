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
#include <memory>

#include "concurrent/ConcurrentQueue.h"
#include "utils/Configuration.h"
#include "Data.h"
#include "Broker.h"
#include "concurrent/Thread.h"

/**
 * A class to interface with a sensor. Provides methods
 * to manage sensor readings in background.
 */
class Sensor {

public:

    /**
     * Default constructor
     */
    Sensor() : name("unknown"), topic("default"), sampling_rate(10000), started(false), stopped(false) {

    }

    /**
     * Constructor with all configurable parameters.
     * @param name The name of the sensor. Used to identify it.
     * @param topic The topic this sensor will publish its data to.
     * @param rate The rate in nanoseconds at which this sensor will be read.
     */
    Sensor(const std::string& name, const std::string& topic, uint64_t rate) : name(name), topic(topic), sampling_rate(rate), started(false), stopped(false)  {

    }

    /**
     * Constructor with configuration object
     * @param config The node containing the configuration for this sensor
     */
    explicit Sensor(Configuration& config) : 
        name(config["name"].get<std::string>()),
        topic(config["topic"].get<std::string>()),
        sampling_rate(config["sampling_rate"].get<uint64_t>()),
        started(false),
        stopped(false) {

    }

    /**
     * Destructor
     */
    virtual ~Sensor() {
        try {
            stop();
        }
        catch (std::runtime_error&) {
            //Already stopped
        }
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
    virtual bool isStarted() const;

    /**
     * Is the sensor stopped?
     * @returns Whether or not the sensor has been stopped
     */
    virtual bool isStopped() const;

    /**
     * Fetch the read data by the sensor.
     * This interface allows sensors to perform "burst" reads, or
     * sensors that generate more than one data value.
     * @params broker The Broker where the data will be sent.
     */
    virtual void fetch(Broker* broker);

    /**
     * Get the name of this sensor
     * @returns The name of the sensor
     */
    std::string getName() const;

    /**
     * Get the topic of this sensor
     * @returns The topic this sensor is publishing to
     */
    std::string getTopic() const;

    /**
     * Get the sampling rate (in nanoseconds) for this second
     * @returns The sampling rate in nanoseconds
     */
    uint64_t getSamplingRate() const;

    /**
     * Set the name of this sensor. It does not need to be unique, but the combination of sensor name and topic shall be unique.
     * @param name An string identifier for this sensor
     */
    void setName(const std::string& name);

    /**
     * Set the topic this sensor will publish to. The combination of sensor name and topic shall be unique. 
     * @param name An string identifying a topic. 
     */
    void setTopic(const std::string& topic);

    /**
     * Set the sampling rate for the reading of this sensor. In nanoseconds.
     * @param rate The sampling rate in nanoseconds at which the sensor will be read.
     */
    void setSamplingRate(uint64_t rate);

protected:

    /**
     * Internal read method. Must be overriden by a subclass.
     * The results of the read must be saved to the `queue`.
     */
    virtual void read() = 0;

    /**
     * The name of the sensor. Used to populate the origin field from Data.
     * If not set, defaults to "unknown".
     */
    std::string name;

    /**
     * The topic where this sensor will publish its data.
     * If not set, defaults to "default".
     */
    std::string topic;

    /**
     * The sampling rate in nanoseconds.
     * Each interval of `sampling_rate` nanoseconds the sensor will be read.
     */
    uint64_t sampling_rate;

    /**
     * Internal thread-safe queue where the read data is stored. 
     */
    ConcurrentQueue<std::shared_ptr<Data>> queue;

private:

    /**
     * Internal thread function. Calls the read() method periodically.
     */
    void run();

    std::atomic<bool> started;
    std::atomic<bool> stopped;

    Thread sensor_thread;

};