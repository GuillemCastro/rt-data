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

#include "Duration.h"

uint64_t Duration::to_seconds() const {
    return TimeUnit::convert(to_nanos(), TimeUnit::nanoseconds, TimeUnit::seconds);
}

uint64_t Duration::to_millis() const {
    return TimeUnit::convert(to_nanos(), TimeUnit::nanoseconds, TimeUnit::milliseconds);
}

uint64_t Duration::to_micros() const {
    return TimeUnit::convert(to_nanos(), TimeUnit::nanoseconds, TimeUnit::microseconds);
}

uint64_t Duration::to_nanos() const {
    return (nanos_end - nanos_start);
}