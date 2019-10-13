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

#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <cstring>

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

/**
 * \class I2C
 * 
 * \brief A class to control the I2C ports of your board
 * 
 * An instance of this class manages one single I2C port. As usual
 * with Linux, I2C ports are exposed as files thanks to the sysfs.
 * You need to know the mapping between the I2C port and the file.
 * 
 * Normally I2C (i2c-*) files should be under /dev in most boards,
 * in others might be in the IIO (Industrial I/O), /sys/iio.
 * 
 * The I2C port must be open (by calling open()) in order to read or write.
 * I2C reads and writes are done against "registers" which have a 7-bit address.
 * Obviously it's not possible to store a 7-bit word in typical computers, so
 * we have to store it in a 8-bit word (byte).
 * 
 * The padding of the address byte (if we put an extra 0 at the start or at the
 * end of the word) is completely implementation-dependant. Check the manual of
 * your board and/or sensor.
 * 
 */
class I2C {

public:

    /**
     * Constructor with file. Builds a I2C object linked to a file mapped to a I2C port.
     * @param file The filename of a I2C port (full path!)
     */
    explicit I2C(const std::string& file) : file(file), started(false), address_set(false) {
        open();
    }

    ~I2C() {
        if (is_open()) {
            try {
                close();
            }
            catch (...) {
                // Nothing to do here...
            }
        }
    }

    /**
     * Opens the I2C port.
     * @throws std::runtime_error If the port is already open
     * @throws std::runtime_error If an error occurred while opening the port
     */
    void open();

    /**
     * Opens the I2C port.
     * @throws std::runtime_error If the port is not open
     * @throws std::runtime_error If an error occurred while closing the port
     */
    void close();

    /**
     * Read a byte from a register
     * @param address A 7-bit address to the register with padding
     * @throws std::runtime_error If the port is not open
     * @throws std::runtime_error If an error occurred while reading the port
     */
    uint8_t read(uint8_t address);

    /**
     * Read size bytes from a register
     * @param address A 7-bit address to the register with padding
     * @param out The output buffer
     * @param size The number of bytes to read
     * @throws std::runtime_error If the port is not open
     * @throws std::runtime_error If an error occurred while reading the port
     */
    void read(uint8_t address, std::vector<uint8_t>& out, size_t size);

    /**
     * Write a byte to a register
     * @param address A 7-bit address to the register with padding
     * @param byte The byte to write
     * @throws std::runtime_error If the port is not open
     * @throws std::runtime_error If an error occurred while writing to the port
     */
    void write(uint8_t address, uint8_t byte);

    /**
     * Write bytes to a register
     * @param address A 7-bit address to the register with padding
     * @param buffer The buffer to write
     * @throws std::runtime_error If the port is not open
     * @throws std::runtime_error If an error occurred while writing to the port
     */
    void write(uint8_t address, const std::vector<uint8_t>& buffer);

    /**
     * Is the bus open (available for reading and writing)?
     * @returns Whether or not the bus is open
     */
    bool is_open();

    /**
     * Is the bus closed?
     * @returns Whether or not the bus is open
     */
    bool is_closed();

    static const std::string I2C_1;

    static const std::string I2C_2;

private:

    std::string file;

    bool started;

    bool address_set;

    int fd;

    uint8_t address;

    void set_address(uint8_t address);

};