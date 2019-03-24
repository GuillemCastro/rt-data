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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "time/Timestamp.h"

class TimestampTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TimestampTest);
    CPPUNIT_TEST(secondsTest);
    CPPUNIT_TEST(millisTest);
    CPPUNIT_TEST(microsTest);
    CPPUNIT_TEST(nanosTest);
    CPPUNIT_TEST(durationTest);
    CPPUNIT_TEST(comparatorsTest);
    CPPUNIT_TEST(arithmeticTest);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp();

    void tearDown();

    void secondsTest();

    void millisTest();

    void microsTest();

    void nanosTest();

    void durationTest();

    void comparatorsTest();

    void arithmeticTest();

private:

};

CPPUNIT_TEST_SUITE_REGISTRATION( TimestampTest );