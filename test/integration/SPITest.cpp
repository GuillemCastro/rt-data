/*
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

#include "io/SPI.h"

#include <iostream>

int main() {
    SPI spi("/dev/spidev0.0", 1000000);
    spi.open();
    spi.write('c');
    uint8_t c = spi.read();
    std::cout << (char) c << " - " << (int)c << std::endl;
    std::vector<uint8_t> buf = {'h','e','l','l','o'};
    spi.write(buf);
}