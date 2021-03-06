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

#include "AnalogSensor.h"

void AnalogSensor::start() {
    Sensor::start();
}

void AnalogSensor::stop() {
    Sensor::stop();
}

void AnalogSensor::read() {
    std::string buff;
    double value;

    std::ifstream fp(file);
    if (fp.fail()) {
        Log::log(WARNING) << "[" << name << "] Failed to open the file " << file;
        return;
    }

    fp >> buff;
    if (fp.fail()) {
        Log::log(WARNING) << "[" << name << "] Failed to read from file " << file;
        return;
    }

    value = (std::stoi(buff) - zero) * (scale / span);

    Log::log(INFO) << "[" << name << "] Read value " << value;

    std::shared_ptr<Data> data = std::make_shared<AnalogData>(name, value);
    queue.push(data);
}

void AnalogData::serialize(SerializedObject* object) {
    Data::serialize(object);
    object->put("analog_value", value);
}

void AnalogData::deserialize(SerializedObject* object) {
    Data::deserialize(object);
    value = object->get_double("analog_value");
}

double AnalogData::get_value() const {
    return value;
}

void AnalogData::set_value(double value) {
    this->value = value;
}