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

#include "SPI.h"

void SPI::open() {
    if (started) {
        throw std::runtime_error("SPI port already open");
    }
    fd = ::open(file.c_str(), O_RDWR);
    if (fd < 0) {
        throw std::runtime_error(strerror(errno)); 
    }

    uint8_t byte_mode = (uint8_t)mode;

    // Configure SPI mode
    int ret = ioctl(fd, SPI_IOC_WR_MODE, &byte_mode);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }
    ret = ioctl(fd, SPI_IOC_RD_MODE, &byte_mode);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }

    // Configure number of bits per word
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits_per_word);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits_per_word);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }

    // Configure speed
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno)); 
    }

    started = true;
}

void SPI::close() {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }
    int ret = ::close(fd);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
    started = false;
}

uint8_t SPI::read() {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }

    spi_ioc_transfer spi_transfer;
    memset(&spi_transfer, 0, sizeof(spi_transfer));

    uint8_t res = 0;

    spi_transfer.rx_buf = (unsigned long)&res;
    spi_transfer.len = sizeof(uint8_t);

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }

    return res;
}

void SPI::read(std::vector<uint8_t>& out, size_t size) {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }

    spi_ioc_transfer spi_transfer;
    memset(&spi_transfer, 0, sizeof(spi_transfer));

    if (out.size() < size) {
        out.resize(size);
    }

    spi_transfer.rx_buf = (unsigned long)out.data();
    spi_transfer.len = size * sizeof(uint8_t);

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void SPI::write(uint8_t byte) {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }

    spi_ioc_transfer spi_transfer;
    memset(&spi_transfer, 0, sizeof(spi_transfer));

    spi_transfer.tx_buf = (unsigned long)&byte;
    spi_transfer.len = sizeof(uint8_t);

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void SPI::write(const std::vector<uint8_t>& buffer) {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }

    spi_ioc_transfer spi_transfer;
    memset(&spi_transfer, 0, sizeof(spi_transfer));

    spi_transfer.tx_buf = (unsigned long)buffer.data();
    spi_transfer.len = buffer.size() * sizeof(uint8_t);

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}

void SPI::transfer(const std::vector<uint8_t>& to_send, std::vector<uint8_t>& to_receive, size_t size) {
    if (!started) {
        throw std::runtime_error("SPI port is not open");
    }

    spi_ioc_transfer spi_transfer;
    memset(&spi_transfer, 0, sizeof(spi_transfer));

    if (to_receive.size() < size) {
        to_receive.resize(size);
    }

    spi_transfer.tx_buf = (unsigned long)to_send.data();
    spi_transfer.rx_buf = (unsigned long)to_receive.data();
    spi_transfer.len = size * sizeof(uint8_t);

    int ret = ioctl(fd, SPI_IOC_MESSAGE(1), &spi_transfer);
    if (ret < 0) {
        throw std::runtime_error(strerror(errno));
    }
}