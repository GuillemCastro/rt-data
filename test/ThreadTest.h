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

#include "concurrent/Thread.h"

class ThreadTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(ThreadTest);
    CPPUNIT_TEST(minPriorityTest);
    CPPUNIT_TEST(maxPriorityTest);
    //CPPUNIT_TEST(setPriorityTest);
    //CPPUNIT_TEST(setPolicyTest);
    //CPPUNIT_TEST(priorityBoundsTest);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp() {}

    void tearDown() {}

    void minPriorityTest();

    void maxPriorityTest();

    void setPriorityTest();

    void setPolicyTest();

    void priorityBoundsTest();

private:



};

CPPUNIT_TEST_SUITE_REGISTRATION( ThreadTest );