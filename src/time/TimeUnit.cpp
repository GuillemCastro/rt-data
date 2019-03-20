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

#include "time/TimeUnit.h"

const TimeUnit TimeUnit::seconds      = TimeUnit(1000000000);

const TimeUnit TimeUnit::milliseconds = TimeUnit(1000000);

const TimeUnit TimeUnit::microseconds = TimeUnit(1000);

const TimeUnit TimeUnit::nanoseconds  = TimeUnit(1);

uint64_t TimeUnit::convert(uint64_t value, TimeUnit original, TimeUnit destination) {
    return (original * value) / destination;
}
