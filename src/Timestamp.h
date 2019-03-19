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

#include <chrono>
#include <cstdint>

/**
 * A class representing a point in time. 
 */
class Timestamp {

public:

    Timestamp() = default;

    template <typename T>
    Timestamp(std::chrono::time_point<T> time) : time(time) {

    }

    /**
     * Get the current time with with the highest possible
     * resolution.
     * @returns a timestamp representing the current time.
     */
    static Timestamp now();

    /**
     * Return an integer representing the number of seconds
     * since 1970-01-01T00:00:00
     */
    uint64_t toSeconds();

    /**
     * Return an integer representing the number of milliseconds
     * since 1970-01-01T00:00:00
     */
    uint64_t toMillis();


    /**
     * Return an integer representing the number of microseconds
     * since 1970-01-01T00:00:00
     */
    uint64_t toMicros();

    /**
     * Return an integer representing the number of nanoseconds
     * since 1970-01-01T00:00:00
     */
    uint64_t toNanos();

private:

    template <typename T>
    uint64_t toDuration() {
        auto secs = std::chrono::time_point_cast<T>(time);
        auto since_epoch = secs.time_since_epoch();
        auto value = std::chrono::duration_cast<T>(since_epoch);
        return value.count();
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> time; 

};