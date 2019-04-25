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

int Thread::convertPolicy(SchedulingPolicy policy) {
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

void Thread::setSchedulingPolicy(SchedulingPolicy policy, int priority) {
    int sched_policy = convertPolicy(policy);
    sched_param params;
    params.sched_priority = priority; // Ignored if policy is not RT Round Robin or FIFO
    if (pthread_setschedparam(this->native_handle(), sched_policy, &params)) {
        throw std::runtime_error(std::strerror(errno));
    }
}

SchedulingPolicy Thread::getCurrentSchedulingPolicy() {
    int policy;
    sched_param params;
    if (pthread_getschedparam(this->native_handle(), &policy, &params)) {
        throw std::runtime_error(std::strerror(errno));
    }
    return (SchedulingPolicy)policy;
}

int Thread::getCurrentPriority() {
    int policy;
    sched_param params;
    if (pthread_getschedparam(this->native_handle(), &policy, &params)) {
        throw std::runtime_error(std::strerror(errno));
    }
    return params.sched_priority;
}

int Thread::getMinSchedulingPriority(SchedulingPolicy policy) {
    int sched_policy = convertPolicy(policy);
    return sched_get_priority_min(sched_policy);
}

int Thread::getMaxSchedulingPriority(SchedulingPolicy policy) {
    int sched_policy = convertPolicy(policy);
    return sched_get_priority_max(sched_policy);
}