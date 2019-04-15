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

#include "../Sensor.h"
#include "../Log.h"

#include <fstream>

class AnalogSensor : public Sensor {

public:

    /**
     * Constructor for AnalogSensor
     * @param file The device file that manages the sensor
     * @param topic The topic this sensor will publish to
     * @param sensorName A short identifier for the sensor
     * @param samplingRate The rate that will be used to sample the sensor in nanos
     * @param zeroValue The voltage at which the ADC reads the lowest value
     * @param spanValue The voltage ath which the ADC reads the highest value
     * @param scale  The maximum value that can be read by the sensor
     * @param quantizationBits The resolution of the ADC in bits
     * @param zeroVoltage The lowest possible voltage at which the ADC reads a value (tipically 0)
     * @param spanVoltage The maximum possible voltage at which the ADC reads a value (tipically 5 or 3.3)
     */
    AnalogSensor(std::string file, 
        std::string topic, 
        std::string sensorName,
        int samplingRate,
        double zeroValue,
        double spanValue,
        double scale,
        int quantizationBits,
        double zeroVoltage,
        double spanVoltage ) : Sensor(), file(file), topic(topic), sensor_name(sensorName), sampling_rate(samplingRate),
        zero_value(zeroValue), span_value(spanValue), scale(scale), quantization_bits(quantizationBits), zero_voltage(zeroVoltage),
        span_voltage(spanVoltage) {
            zero = (double)(1 << quantization_bits) * (zero_value - zero_voltage) / span_voltage;
            span = (double)(1 << quantization_bits) * (span_value) / span_voltage;
    }

    /**
     * Starts the sensor.
     * @throws std::runtime_error if the sensor has been already started or if it was stopped.
     */
    virtual void start() override;

    /**
     * Stops the sensor.
     * @throws std::runtime_error if the sensor has been already stopped or if it was never started.
     */
    virtual void stop() override;

    /**
     * Fetch the read data by the sensor and send it to a Broker.
     * @params broker The Broker where the data will be sent.
     */
    virtual void fetch(Broker* broker) override;

protected:

    /**
     * Internal read method
     */
    virtual void read() override;

private:

    std::string file;
    std::string topic;
    std::string sensor_name;
    int sampling_rate;
    double zero_value;
    double span_value;
    double scale;
    int quantization_bits;
    double zero_voltage;
    double span_voltage;

    double zero, span;


};

class AnalogData : public Data {

public:

    AnalogData() : Data(), value(0.0) {

    }

    explicit AnalogData(double value) : Data(), value(value) {

    }

    AnalogData(const std::string& origin, double value) : Data(origin), value(value) {

    }

    AnalogData(const Timestamp& time, const std::string& origin, double value) : Data(time, origin), value(value) {

    }

    /**
     * Serialize the AnalogData. Do not call directly.
     * @param object The resulting SerializedObject where the data must be saved.
     */
    virtual void serialize(SerializedObject* object) override;

    /**
     * Deserialize the AnalogData. Do not call directly.
     * @param object The SerializedObject to load the data from.
     */
    virtual void deserialize(SerializedObject* object) override;

    double getValue();

    void setValue(double value);

private:

    double value;

};