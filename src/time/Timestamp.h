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

#include <chrono>
#include <cstdint>

#include "time/Duration.h"

/**
 * A class representing a point in time. 
 */
class Timestamp {

public:

    //Default constructor
    Timestamp() = default;

    /**
     * Constructor with an integral time as nanos
     */
    explicit Timestamp(uint64_t nanos) : nanos(nanos) {

    }

    /**
     * Copy constructors
     */
    Timestamp(const Timestamp& other) : nanos(other.nanos) {

    }

    /**
     * Assignment operator
     */
    Timestamp& operator=(const Timestamp& other) {
        if (this != &other) {
            this->nanos = other.nanos;
        }
        return *this;
    }

    /**
     * Get the current time with with the highest possible
     * resolution.
     * @returns a timestamp representing the current time.
     */
    static Timestamp now();

    /**
     * Get a Timestamp from an integer point in time.
     * @params time A point in time in integer type
     * @params uints The units of the point in time
     * @returns a Timestamp representing the point in time 
     */
    static Timestamp fromDuration(uint64_t time, TimeUnit units) {
        uint64_t nanos = TimeUnit::convert(time, units, TimeUnit::nanoseconds);
        return Timestamp(nanos);
    }

    /**
     * Return an integer representing the number of seconds
     * since epoch (implementation specific)
     */
    uint64_t toSeconds() const;

    /**
     * Return an integer representing the number of milliseconds
     * since epoch (implementation specific)
     */
    uint64_t toMillis() const;


    /**
     * Return an integer representing the number of microseconds
     * since epoch (implementation specific)
     */
    uint64_t toMicros() const;

    /**
     * Return an integer representing the number of nanoseconds
     * since epoch (implementation specific)
     */
    uint64_t toNanos() const;

    /**
     * Substract two timestamps
     * @param other Another timestamp
     * @returns the duration between the two timestamps
     */
    Duration operator-(const Timestamp& other) {
        Duration d(other.nanos, nanos);
        return d;
    }


    /**
     * Add a unit of time to a timestamp
     * @param time The time to add to the timestamp
     * @param unit The time units
     * @returns a new Timestamp with the sum of the old timestamp and the passed time
     */
    Timestamp plus(uint64_t time, const TimeUnit& unit) {
        uint64_t nanos = TimeUnit::convert(time, unit, TimeUnit::nanoseconds);
        return Timestamp(this->nanos + nanos);
    }

    /**
     * Substract a unit of time to a timestamp
     * @param time The time to substract to the timestamp
     * @param unit The time units
     * @returns a new Timestamp with the substraction of the passed time to the old timestamp
     */
    Timestamp minus(uint64_t time, const TimeUnit& unit) {
        uint64_t nanos = TimeUnit::convert(time, unit, TimeUnit::nanoseconds);
        return Timestamp(this->nanos - nanos);
    }

    /**
     * Add a unit of time to a timestamp
     * @param duration A time duration to add to the timestamp
     * @returns a new Timestamp with the sum of the old timestamp and the passed duration
     */
    Timestamp operator+(const Duration& duration) const {
        return Timestamp(this->nanos + duration.toNanos());
    }

    /**
     * Substract a unit of time to a timestamp
     * @param duration A time duration to substract from the timestamp
     * @returns a new Timestamp with the substraction of the passed duration to the old timestamp
     */
    Timestamp operator-(const Duration& duration) const {
        return Timestamp(this->nanos - duration.toNanos());
    }

    /**
     * Compare if the timestamp is older than another timestamp
     * A timestamp is older if it represents an older point in time
     */
    bool operator<(const Timestamp& other) const {
        return (nanos < other.nanos);
    }

    /**
     * Compare if the timestamp is newer than another timestamp
     * A timestamp is older if it represents an older point in time
     */
    bool operator>(const Timestamp& other) const {
        return (nanos > other.nanos);
    }

    /**
     * Compare if two timestamps are equal
     * Two timestamps are equal if they represent the same point in time
     */
    bool operator==(const Timestamp& other) const {
        return (nanos == other.nanos);
    }

    /**
     * epoch is the start of the time representation (i.e. time 0).
     * Implementation specific but usually represents 1970-01-01T00:00:00
     */
    static const Timestamp epoch;

private:

    uint64_t nanos; 

};