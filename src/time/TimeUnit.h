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

#include <cstdint>

/**
 * A class to represent a time unit (seconds, millis, ...)
 */
class TimeUnit {

public:

    /**
     * Constructor for TimeUnit
     * @param nanos The number of nanoseconds that this unit will have
     * Example: one millisecond has 10^6 nanoseconds
     */
    explicit TimeUnit(uint64_t nanos) : nNanos(nanos) {
    
    }

    /**
     * A TimeUnit representing seconds
     */
    static const TimeUnit seconds;

    /**
     * A TimeUnit representing milliseconds
     */
    static const TimeUnit milliseconds;

    /**
     * A TimeUnit representing microseconds
     */
    static const TimeUnit microseconds;

    /**
     * A TimeUnit representing nanoseconds
     */
    static const TimeUnit nanoseconds; 

    /**
     * Convert a time from one TimeUnit to another
     * @param value An integer representing a time value
     * @param original The TimeUnit of the value
     * @param destination The destination TimeUnit
     * @returns The value converted from the original TimeUnit to the destination TimeUnit
     */
    static uint64_t convert(uint64_t value, TimeUnit original, TimeUnit destination);

private:

    friend uint64_t operator/(uint64_t value, TimeUnit& other) {
        return value / other.nNanos;
    }

    uint64_t operator/(const TimeUnit& other) {
        return this->nNanos / other.nNanos;
    }

    uint64_t operator*(const TimeUnit& other) {
        return this->nNanos * other.nNanos;
    }

    uint64_t operator*(uint64_t other) {
        return this->nNanos * other;
    }

    uint64_t operator/(uint64_t other) {
        return this->nNanos / other;
    }

    uint64_t nNanos;

};