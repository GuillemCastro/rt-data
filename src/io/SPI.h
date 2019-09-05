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

#include <vector>
#include <string>
#include <stdexcept>

#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

/*
 * The mode of operation of the SPI port 
 * c.f. https://en.wikipedia.org/wiki/Serial_Peripheral_Interface#Mode_numbers
 * By default Mode 0
 */
enum SPIMode {
    MODE_0 = SPI_MODE_0,
    MODE_1 = SPI_MODE_1,
    MODE_2 = SPI_MODE_2,
    MODE_3 = SPI_MODE_3
};

/**
 * \class SPI
 * 
 * \brief A class to manage the SPI ports of your board
 * 
 * An instance of this class manages a single SPI port. As usual in Linux,
 * SPI ports are exposed as files, thanks to the sysfs. You need to know
 * the mapping between the SPI ports and the files. Check the docs of your
 * board.
 * 
 * Normally SPI (spidev*) files should be under /dev in most boards,
 * in others might be in the IIO (Industrial I/O subsystem), /sys/iio.
 * 
 * The I2C port must be open (by calling open()) in order to read or write.
 * Unlike I2C, SPI is a full-duplex protocol. Note that SPI are conceptually
 * two shift registers. This means that when you send a byte to a slave host,
 * you are also receiving a byte from the slave.
 * 
 * You can perform regular half-duplex reads and writes, and also a full-duplex
 * transaction using the transfer() method.
 * 
 * SPI has 4 modes of operation (from 0 to 3), each mode regulates how the chip-select,
 * clock, ... work. By default it's mode 0. Unless you need to change it, don't change it.
 * 
 * It's also important to set the communication speed correctly. By default it's set to
 * 1MHz (which will work with most devices) but you should change it to the recommended
 * speed for your device.
 * 
 * You can also configure the size of a word, by default it's 8 bits. Only change it if you
 * need it, otherwise leave it at 8. A value of 0 also sets the size of the word to 8 bits.
 * 
 * more info: https://www.kernel.org/doc/Documentation/spi/spidev
 */
class SPI {

public:

    /**
     * Build a SPI object with its filename.
     * @param file The file (full path) of a SPI port
     */
    explicit SPI(const std::string& file) :
        file(file), started(false), mode(SPIMode::MODE_0), bits_per_word(0), speed(1000000) {

    }

    /**
     * Build a SPI object with its filename and a given speed. Preferred constructor.
     * @param file The file (full path) of a SPI port
     * @param speed The speed that will be used to communicate with the slave device
     */
    SPI(const std::string& file, uint32_t speed) :
        file(file), started(false), mode(SPIMode::MODE_0), bits_per_word(0), speed(speed) {

    }    

    /**
     * Build a SPI object with its filename, speed, SPI mode and  bits per word. Preferred constructor.
     * @param file The file (full path) of a SPI port
     * @param mode The mode of operation of the SPI port (see https://en.wikipedia.org/wiki/Serial_Peripheral_Interface#Mode_numbers)
     * @param bits_per_word The size in bits of a word
     * @param speed The speed that will be used to communicate with the slave device
     */
    SPI(const std::string& file, SPIMode mode, uint8_t bits_per_word, uint32_t speed) : 
        file(file), started(false), mode(mode), bits_per_word(bits_per_word), speed(speed) {

    }

    /**
     * Open the SPI port
     * @throws std::runtime_error If the port cannot be opened
     * @throws std::runtime_error If the port is already open
     */
    void open();

    /**
     * Close the SPI port
     * @throws std::runtime_error If the close fails
     * @throws std::runtime_error If the port is not open
     */
    void close();

    /**
     * Read a sinlge byte from the slave device (half-duplex)
     * @returns The read byte
     * @throws std::runtime_error If the read fails
     * @throws std::runtime_error If the port is not open
     */
    uint8_t read();

    /**
     * Read bytes from the slave device (half-duplex)
     * @param out The buffer that will hold the received bytes
     * @param size The number of bytes to read
     * @throws std::runtime_error If the read fails
     * @throws std::runtime_error If the port is not open
     */
    void read(std::vector<uint8_t>& out, size_t size);

    /**
     * Write a single byte to the slave device (half-duplex)
     * @param byte The byte to write to the slave
     * @throws std::runtime_error If the write fails
     * @throws std::runtime_error If the port is not open
     */
    void write(uint8_t byte);

    /**
     * Write a buffer of bytes to the slave device (half-duplex)
     * @param buffer The buffer to be sent to the slave
     * @throws std::runtime_error If the write fails
     * @throws std::runtime_error If the port is not open
     */
    void write(const std::vector<uint8_t>& buffer);

    /**
     * Make a full-duplex communication with the slave device (i.e. read and write simultaneously)
     * @param to_send The buffer to be sent to the slave
     * @param to_receive The buffer that will hold the received bytes.
     * @param size The number of bytes to be received
     * @throws std::runtime_error If the transfer fails
     * @throws std::runtime_error If the port is not open
     */
    void transfer(const std::vector<uint8_t>& to_send, std::vector<uint8_t>& to_receive, size_t size);

private:

    std::string file;

    bool started;

    SPIMode mode;

    uint8_t bits_per_word;

    uint32_t speed;

    int fd;

};