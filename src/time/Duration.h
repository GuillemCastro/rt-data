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

#include "time/TimeUnit.h"

/**
 * A class to represent the time duration between
 * two time points.
 */
class Duration {

public:

    //Default constructor
    Duration() = default;

    /**
     * Duration constructor with two points in time
     * @param nanosStart the start time point in nanoseconds
     * @param nanosEnd the end time point in nanoseconds
     */
    Duration(uint64_t nanosStart, uint64_t nanosEnd) : nanos_start(nanosStart), nanos_end(nanosEnd) {

    }

    /**
     * Duration constructor with a duration integral
     * @param value An integral representing a time duration
     * @param units The time unit of the time value
     */
    Duration (uint64_t value, const TimeUnit& units) : nanos_start(0), nanos_end(TimeUnit::convert(value, units, TimeUnit::nanoseconds)) {

    }

    /**
     * Copy constructor
     */
    Duration(const Duration& other) : nanos_start(other.nanos_start), nanos_end(other.nanos_end) {

    }

    /**
     * Assignment operator
     */
    Duration& operator=(const Duration& other) {
        if (this != &other) {
            this->nanos_start = other.nanos_start;
            this->nanos_end = other.nanos_end;
        }
        return *this;
    }

    /**
     * Get the duration value as an integral representing seconds
     */
    uint64_t toSeconds() const;

    /**
     * Get the duration value as an integral representing milliseconds
     */
    uint64_t toMillis() const;

    /**
     * Get the duration value as an integral representing microseconds
     */
    uint64_t toMicros() const;

    /**
     * Get the duration value as an integral representing nanoseconds
     */
    uint64_t toNanos() const;

private:

    uint64_t nanos_start;

    uint64_t nanos_end;

};