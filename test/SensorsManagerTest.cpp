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

#include "SensorsManagerTest.h"
#include <iostream>

void SensorsManagerTest::setUp() {
    manager = std::make_shared<SensorsManager>();
}

void SensorsManagerTest::tearDown() {
    try {
        //If we delete the SensorsManager without joining
        //the thread, the tests will crash
        manager->stop();
    }
    catch (const std::exception) {
        //Either already stopped or not started
    }
}

void SensorsManagerTest::addSensorTest() {
    try {
        auto sensor = std::make_shared<SensorStub>();
        manager->addSensor(sensor);
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorsManagerTest::addSensorTestStopped() {
    bool received_exception = false;
    try {
        manager->start();
        manager->stop();
        auto sensor = std::make_shared<SensorStub>();
        manager->addSensor(sensor);
    }
    catch (const std::runtime_error) {
        received_exception = true;
    }
    if (!received_exception) {
        CPPUNIT_FAIL("Expected exception");
    }
}

void SensorsManagerTest::removeSensorTest() {
    try {
        auto sensor = std::make_shared<SensorStub>();
        manager->addSensor(sensor);
        manager->removeSensor(sensor);
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorsManagerTest::startTest() {
    try {
        manager->start();
        CPPUNIT_ASSERT(manager->isStarted());
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorsManagerTest::startTestTwoTimes() {
    bool received_exception = false;
    try {
        manager->start();
        manager->start();
    }
    catch (const std::runtime_error) {
        received_exception = true;
    }
    if (!received_exception) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void SensorsManagerTest::stopTest() {
    try {
        manager->start();
        manager->stop();
        CPPUNIT_ASSERT(manager->isStopped());
    }
    catch (const std::exception) {
        CPPUNIT_FAIL("No exception expected");
    }
}

void SensorsManagerTest::stopTestTwoTimes() {
    bool received_exception = false;
    try {
        manager->start();
        manager->stop();
        manager->stop();
    }
    catch (const std::runtime_error) {
        received_exception = true;
    }
    if (!received_exception) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void SensorsManagerTest::stopNoStartTest() {
    bool received_exception = false;
    try {
        manager->stop();
    }
    catch (const std::runtime_error) {
        received_exception = true;
    }
    if (!received_exception) {
        CPPUNIT_FAIL("Exception expected");
    }
}