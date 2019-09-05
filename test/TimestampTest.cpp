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

#include "TimestampTest.h"
#include <iostream>
#include <thread>
#include <chrono>

void TimestampTest::setUp() {

}

void TimestampTest::tearDown() {

}

void TimestampTest::secondsTest() {
    Timestamp test(1000000000); //1 second in nanos
    CPPUNIT_ASSERT(1 == test.to_seconds());
}

void TimestampTest::millisTest() {
    Timestamp test(1000000); //1 millisecond in nanos
    CPPUNIT_ASSERT(1 == test.to_millis());
}

void TimestampTest::microsTest() {
    Timestamp test(1000); //1 millisecond in nanos
    CPPUNIT_ASSERT(1 == test.to_micros());
}

void TimestampTest::nanosTest() {
    Timestamp test(1); //1 millisecond in nanos
    CPPUNIT_ASSERT(1 == test.to_nanos());
}

void TimestampTest::durationTest() {
    Timestamp t(100);
    Duration test = t - Timestamp::epoch;
    CPPUNIT_ASSERT(100 == test.to_nanos());
}

void TimestampTest::comparatorsTest() {
    Timestamp now = Timestamp::now();
    CPPUNIT_ASSERT(now > Timestamp::epoch);
    CPPUNIT_ASSERT(Timestamp::epoch < now);
    CPPUNIT_ASSERT(now == now);
}

void TimestampTest::arithmeticTest() {
    Timestamp test(100);
    Timestamp result = test.plus(100, TimeUnit::nanoseconds);
    CPPUNIT_ASSERT(200 == result.to_nanos());
    Timestamp test2(200);
    Timestamp result2 = test2.minus(100, TimeUnit::nanoseconds);
    CPPUNIT_ASSERT(100 == result2.to_nanos());
}