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

#include "SensorStub.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class SensorTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(SensorTest);
    CPPUNIT_TEST(startTest);
    CPPUNIT_TEST(stopTest);
    CPPUNIT_TEST(fetchTest);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp();

    void tearDown();

    void startTest();

    void stopTest();

    void fetchTest();

private:

    std::shared_ptr<Sensor> sensor;

};

CPPUNIT_TEST_SUITE_REGISTRATION( SensorTest );