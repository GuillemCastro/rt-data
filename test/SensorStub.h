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
#include "Broker.h"

class DoubleData : public Data {

public:

    DoubleData(double value) : value(value), Data() {

    }

    double getValue() {
        return value;
    }

private:

    double value;

};

class IntData : public Data {

public:

    IntData(int value) : value(value), Data() {

    }

    int getValue() {
        return value;
    }

private:

    int value;

};

class SensorStub : public Sensor {

public:

    using Sensor::Sensor;

    const static double TEST_VALUE;

    void fetch(Broker* broker);


private:

    virtual void read() override {
        std::shared_ptr<Data> data = std::make_shared<DoubleData>(TEST_VALUE);
        this->queue.push(data);
    }

};