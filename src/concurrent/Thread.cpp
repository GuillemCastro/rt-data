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

#include "Thread.h"

int Thread::convert_policy(SchedulingPolicy policy) {
    int sched_policy;
    switch (policy) {
        case DEFAULT:
            sched_policy = SCHED_OTHER;
            break;
        case RT_FIFO:
            sched_policy = SCHED_FIFO;
            break;
        case RT_ROUND_ROBIN:
            sched_policy = SCHED_RR;
            break;
        default:
            sched_policy = SCHED_OTHER;
            break;
    }
    return sched_policy;
}

void Thread::set_scheduling_policy(SchedulingPolicy policy, int priority) {
    int sched_policy = convert_policy(policy);
    sched_param params;
    params.sched_priority = priority; // Ignored if policy is not RT Round Robin or FIFO
    int ret = pthread_setschedparam(this->native_handle(), sched_policy, &params);
    if (ret) {
        throw std::runtime_error(std::strerror(errno));
    }
}

SchedulingPolicy Thread::get_current_scheduling_policy() {
    int policy;
    sched_param params;
    int ret = pthread_getschedparam(this->native_handle(), &policy, &params);
    if (ret) {
        throw std::runtime_error(std::strerror(errno));
    }
    return (SchedulingPolicy)policy;
}

int Thread::get_current_priority() {
    int policy;
    sched_param params;
    int ret = pthread_getschedparam(this->native_handle(), &policy, &params);
    if (ret) {
        throw std::runtime_error(std::strerror(errno));
    }
    return params.sched_priority;
}

int Thread::get_min_scheduling_priority(SchedulingPolicy policy) {
    int sched_policy = convert_policy(policy);
    return sched_get_priority_min(sched_policy);
}

int Thread::get_max_scheduling_priority(SchedulingPolicy policy) {
    int sched_policy = convert_policy(policy);
    return sched_get_priority_max(sched_policy);
}

SchedulingPolicy this_thread::get_current_scheduling_policy() {
    pthread_t me = pthread_self();
    int policy;
    sched_param params;
    int ret = pthread_getschedparam(me, &policy, &params);
    if (ret) {
        throw std::runtime_error(std::strerror(errno));
    }
    return (SchedulingPolicy)policy;
}

int this_thread::get_current_priority() {
    pthread_t me = pthread_self();
    int policy;
    sched_param params;
    int ret = pthread_getschedparam(me, &policy, &params);
    if (ret) {
        throw std::runtime_error(std::strerror(errno));
    }
    return params.sched_priority;
}