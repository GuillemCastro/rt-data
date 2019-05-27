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

#include "I2C.h"

const std::string I2C::I2C_1 = "/dev/i2c-1";
const std::string I2C::I2C_2 = "/dev/i2c-2";

void I2C::open() {
    if (started) {
        throw std::runtime_error("I2C port already open");
    }
    fd = ::open(file.c_str(), O_RDWR);
    if (fd < 0) {
        throw std::runtime_error(strerror(errno));
    }
    started = true;
}

void I2C::close() {
    if (!started) {
        throw std::runtime_error("I2C port is not open");
    }
    int ret = ::close(fd);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
    started = false;
}

uint8_t I2C::read(uint8_t address) {
    if (!started) {
        throw std::runtime_error("I2C port is not open");   
    }
    this->set_address(address);
    uint8_t res;
    int ret = ::read(fd, &res, sizeof(uint8_t));
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
    return res;
}

void I2C::read(uint8_t address, std::vector<uint8_t>& out, size_t size) {
    if (!started) {
        throw std::runtime_error("I2C port is not open");   
    }
    this->set_address(address);
    if (out.size() < size) {
        out.resize(size);
    }
    int ret = ::read(fd, out.data(), size);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void I2C::write(uint8_t address, uint8_t byte) {
    if (!started) {
        throw std::runtime_error("I2C port is not open");   
    }
    this->set_address(address);
    int ret = ::write(fd, &byte, sizeof(uint8_t));
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void I2C::write(uint8_t address, const std::vector<uint8_t>& buffer) {
    if (!started) {
        throw std::runtime_error("I2C port is not open");   
    }
    this->set_address(address);
    int ret = ::write(fd, buffer.data(), buffer.size() * sizeof(uint8_t));
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void I2C::set_address(uint8_t address) {
    if (this->address != address || !address_set) {
        int ret = ioctl(fd, I2C_SLAVE, address);
        if (ret < 0) {
            throw std::runtime_error(strerror(errno));
        }
        this->address = address;
        address_set = true;
    }
}