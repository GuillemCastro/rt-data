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

#pragma once

#include <stdexcept>
#include <thread>
#include <sched.h>
#include <pthread.h>
#include <cstring>

/**
 * Scheduling policies
 * RT_FIFO and RT_ROUND_ROBIN are real-time schedulings
 * Any real-time thread has more priority than non-real-time threads
 * A real-time thread is the one that has a real-time scheduling (RT_FIFO or RT_ROUND_ROBIN)
 */
enum SchedulingPolicy {
    DEFAULT = 0,
    // Real-time FIFO (first in, first out), a 
    // scheduling policy based on a queue
    RT_FIFO,
    // Real-time Round-robin
    RT_ROUND_ROBIN
};

/**
 * An extension of the std::thread class with some utility methods
 * to manage the scheduling of the underlying thread
 */
class Thread : public std::thread {

public:

    using std::thread::thread;

    /**
     * Set the scheduling policy and priority for the current thread
     * The priority in non-real-time threads is ignored
     * @param policy The SchedulingPolicy for this thread
     * @param priority The priority for this thread between 0 (min priority) and 99 (max priority)
     */
    void set_scheduling_policy(SchedulingPolicy policy, int priority);

    /**
     * Get the current scheduling policy for the current thread
     * @returns The policy used by the scheduler for this thread
     */
    SchedulingPolicy get_current_scheduling_policy();

    /**
     * Get the current priority for the current thread
     * @returns The priority used by the scheduler for this thread
     */
    int get_current_priority();

    /**
     * Get the minimum priority for a given SchedulingPolicy
     * @param policy A SchedulingPolicy
     * @returns The minimum priority for the given policy (tipically 0)
     */
    static int get_min_scheduling_priority(SchedulingPolicy policy);

    /**
     * Get the maximum priority for a given SchedulingPolicy
     * @param policy A SchedulingPolicy
     * @returns The maximum priority for the given policy
     */
    static int get_max_scheduling_priority(SchedulingPolicy policy);

private:

    static int convert_policy(SchedulingPolicy policy);

};

/**
 * This namespace contains methods to manage the executing (current) thread
 * It "extends" the std::this_thread namespace 
 */
namespace this_thread {

    /**
     * Get the current scheduling policy for the current thread
     * @returns The policy used by the scheduler for this thread
     */
    SchedulingPolicy get_current_scheduling_policy();

    /**
     * Get the current priority for the current thread
     * @returns The priority used by the scheduler for this thread
     */
    int get_current_priority();

};