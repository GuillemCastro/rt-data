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

#include "DurationTest.h"
#include <iostream>

void DurationTest::conversionTest() {
    Duration test(1000000000);
    CPPUNIT_ASSERT(1 == test.toSeconds());
    CPPUNIT_ASSERT(1000 == test.toMillis());
    CPPUNIT_ASSERT(1000000 == test.toMicros());
    CPPUNIT_ASSERT(1000000000 == test.toNanos());
}