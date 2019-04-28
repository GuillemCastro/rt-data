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

#include "SensorTest.h"

const std::string SensorTest::NAME = "sensor_name";
const std::string SensorTest::TOPIC = "sensor_topic";
const uint64_t SensorTest::RATE = 10;

void SensorTest::setUp() {
    nlohmann::json file = {
        {"name", NAME},
        {"topic", TOPIC},
        {"sampling_rate", RATE}
    };
    config = std::make_shared<JSONConfiguration>(file);
    sensor = std::make_shared<SensorStub>();
}

void SensorTest::tearDown() {
    try {
        sensor->stop();
    }
    catch (const std::exception) {
        //Either already stopped or not started
    }
    sensor.reset();
}

void SensorTest::startTest() {
    try {
        sensor->start();
        CPPUNIT_ASSERT(sensor->isStarted());
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorTest::stopTest() {
    try {
        sensor->start();
        sensor->stop();
        CPPUNIT_ASSERT(sensor->isStopped());
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorTest::configTest() {
    SensorStub sensor(config);
    CPPUNIT_ASSERT(sensor.getName() == NAME);
    CPPUNIT_ASSERT(sensor.getTopic() == TOPIC);
    CPPUNIT_ASSERT(sensor.getSamplingRate() == RATE);
}