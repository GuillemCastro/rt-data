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

#include "Timestamp.h"
#include "TimeUnit.h"

const Timestamp Timestamp::epoch = Timestamp(0);

Timestamp Timestamp::now() {
    auto now = std::chrono::high_resolution_clock::now();
    auto secs = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
    auto since_epoch = secs.time_since_epoch();
    auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(since_epoch);
    return Timestamp(value.count());
}

uint64_t Timestamp::toSeconds() const {
    return TimeUnit::convert(nanos, TimeUnit::nanoseconds, TimeUnit::seconds);
}

uint64_t Timestamp::toMillis() const {
    return TimeUnit::convert(nanos, TimeUnit::nanoseconds, TimeUnit::milliseconds);
}

uint64_t Timestamp::toMicros() const {
    return TimeUnit::convert(nanos, TimeUnit::nanoseconds, TimeUnit::microseconds);
}

uint64_t Timestamp::toNanos() const {
    return this->nanos;
}