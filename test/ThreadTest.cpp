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

#include "ThreadTest.h"

void ThreadTest::minPriorityTest() {
    int default_priority = Thread::getMinSchedulingPriority(DEFAULT);
    int fifo_priority = Thread::getMinSchedulingPriority(RT_FIFO);
    int round_robin_priority = Thread::getMinSchedulingPriority(RT_ROUND_ROBIN);
    CPPUNIT_ASSERT(default_priority == 0);
    CPPUNIT_ASSERT(fifo_priority == 1);
    CPPUNIT_ASSERT(round_robin_priority == 1);    
}

void ThreadTest::maxPriorityTest() {
    int default_priority = Thread::getMaxSchedulingPriority(DEFAULT);
    int fifo_priority = Thread::getMaxSchedulingPriority(RT_FIFO);
    int round_robin_priority = Thread::getMaxSchedulingPriority(RT_ROUND_ROBIN);
    CPPUNIT_ASSERT(default_priority == 0);
    // May only pass on Linux. POSIX only requires 32 different values between max and min priorities
    CPPUNIT_ASSERT(fifo_priority == 99); 
    CPPUNIT_ASSERT(round_robin_priority == 99);
}

void ThreadTest::setPriorityTest() {
    Thread th([]{});
    // Allowed values for the priority are 1 to 99 for RT_ROUND_ROBIN and RT_FIFO
    int priority = 5;
    th.setSchedulingPolicy(RT_ROUND_ROBIN, priority);
    int real_priority = th.getCurrentPriority();
    CPPUNIT_ASSERT(priority == real_priority);
    th.join();
}

void ThreadTest::setPolicyTest() {
    Thread th([]{});    
    int priority = 5;
    SchedulingPolicy policy = RT_ROUND_ROBIN;
    th.setSchedulingPolicy(policy, priority);
    SchedulingPolicy real_policy = th.getCurrentSchedulingPolicy();
    CPPUNIT_ASSERT(policy == real_policy);
    th.join();
}

void ThreadTest::priorityBoundsTest() {
    Thread th([]{});
    int min_priority = 1, max_priority = 99;
    th.setSchedulingPolicy(RT_ROUND_ROBIN, min_priority);
    int real_priority = th.getCurrentPriority();
    CPPUNIT_ASSERT(real_priority == min_priority);
    th.setSchedulingPolicy(RT_ROUND_ROBIN, max_priority);
    real_priority = th.getCurrentPriority();
    CPPUNIT_ASSERT(real_priority == max_priority);
    th.join();
}