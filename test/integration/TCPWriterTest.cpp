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

#include <io/TCPWriter.h>
#include <Data.h>

#include <iostream>

int main() {
    std::string origin = "test";
    Timestamp time = Timestamp::now();
    TCPWriter writer("127.0.0.1", 5005);
    std::shared_ptr<Data> d = std::make_shared<Data>(time, origin);
    writer.write(d);
    writer.write(d);
}