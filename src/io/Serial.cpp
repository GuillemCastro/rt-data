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

#include "Serial.h"

void Serial::start() {
    tty_fd = open(file.c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY );
    if (tty_fd < 0) {
        throw std::runtime_error("Could not open serial port");
    }
    fcntl(tty_fd, F_SETFL, O_RDWR); // Set the file status flags to O_RDWR

    tcgetattr(tty_fd, &tty); // Get the options struct

    cfmakeraw(&tty); // Set to raw-like mode (input is done char by char, no echoing, processing disabled). This initializes some of the flags.
    
    cfsetospeed(&tty, baud_rate); // Set output baud rate
    cfsetispeed(&tty, baud_rate); // Set input baud rate

    // Initialize flags

    tty.c_cflag |= (CLOCAL | CREAD); // Ignore modem control lines, enable receiver
    tty.c_cflag &= ~PARENB; // Disable parity (just in case) before setting it
    tty.c_cflag |= parity; // Set parity
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= bits; // Set number of bits
    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Disable canonical mode, echo inputs, ...
    tty.c_oflag &= ~OPOST; // Disable output processing

    tty.c_cc[VMIN] = 0; // Minimum number of characters for reads -> 0
    tty.c_cc[VTIME] = 100;	// Timeout for reads -> 10 seconds (100 deciseconds)

    tcsetattr(tty_fd, TCSANOW, &tty); // Set the options

    int status;
    ioctl(tty_fd, TIOCMGET, &status);
    status |= TIOCM_DTR; // Data terminal ready
    status |= TIOCM_RTS; // Request to send
    ioctl(tty_fd, TIOCMSET, &status);

    is_open = true;
}

void Serial::stop() {
    if (!is_open) {
        throw std::runtime_error("Serial port is not open");
    }
    close(tty_fd);
    is_open = false;
}

void Serial::flush() {
    if (!is_open) {
        throw std::runtime_error("Serial port is not open");
    }
    tcflush(tty_fd, TCIOFLUSH);
}

void Serial::send(const std::vector<uint8_t>& buffer) {
    if (!is_open) {
        throw std::runtime_error("Serial port is not open");
    }
    int write_count = write(tty_fd, buffer.data(), buffer.size() * sizeof(uint8_t));
    if (write_count < 0) {
        throw std::runtime_error("Error while writting to serial port");
    }
}

uint8_t Serial::receive() {
    if (!is_open) {
        throw std::runtime_error("Serial port is not open");
    }
    uint8_t res;
    int read_count = read(tty_fd, &res, sizeof(uint8_t));
    if (read_count < 0) {
        throw std::runtime_error("Error while reading from serial port");
    }
    return res;
}

void Serial::receive(std::vector<uint8_t>& out, size_t size) {
    if (!is_open) {
        throw std::runtime_error("Serial port is not open");
    }
    out.reserve(out.size() + size);
    int read_count = read(tty_fd, out.data(), size * sizeof(uint8_t));
    if (read_count < 0) {
        throw std::runtime_error("Error while reading from serial port");
    }
}

speed_t Serial::convertBaudRate(const int baudRate) {
    speed_t res;
    switch (baudRate) {
        case 9600:
            res = B9600;
            break;
        case 19200:
            res = B19200;
            break;
        case 38400:
            res = B38400;
            break;
        case 57600:
            res = B57600;
            break;
        case 115200:
            res = B115200;
            break;
        case 230400:
            res = B230400;
            break;
        case 460800:
            res = B460800;
            break;
        case 500000:
            res = B500000;
            break;
        case 576000:
            res = B576000;
            break;
        case 921600:
            res = B921600;
            break;
        case 1000000:
            res = B1000000;
            break;
        case 1152000:
            res = B1152000;
            break;
        case 1500000:
            res = B1500000;
            break;
        case 2000000:
            res = B2000000;
            break;
        case 2500000:
            res = B2500000;
            break;
        case 3000000:
            res = B3000000;
            break;
        case 3500000:
            res = B3500000;
            break;
        case 4000000:
            res = B4000000;
            break;
        default: 
            throw std::invalid_argument("Unsuportted baud rate");
            break;
    }
    return res;
}

uint32_t Serial::convertBits(const int bits) {
    uint32_t res;
    switch (bits) {
        case 5:
            res = CS5;
            break;
        case 6:
            res = CS6;
            break;
        case 7:
            res = CS7;
            break;
        case 8:
            res = CS8;
            break;
        default:
            throw std::invalid_argument("Unsuportted number of bits");
            break;
    }
    return res;
}

uint32_t Serial::convertParity(Parity parity) {
    /**
    * The values for parity are,
    * NONE -> 0 (meaning no parity),
    * ODD -> PARENB|PARODD (enable parity and use odd),
    * EVEN -> PARENB (enable parity and use even), 
    * MARK -> PARENB|PARODD|CMSPAR (mark parity),
    * SPACE -> PARENB|CMSPAR (space parity).
    * https://stackoverflow.com/a/6947758/7293774
    */
    uint32_t res;
    switch (parity) {
        case NONE:
            res = 0;
            break;
        case ODD:
            res = PARENB | PARODD;
            break;
        case EVEN:
            res = PARENB;
            break;
        case MARK:
            res = PARENB | PARODD | CMSPAR;
            break;
        case SPACE:
            res = PARENB | CMSPAR;
            break;
        default:
            throw std::invalid_argument("Unsuportted parity");
            break;
    }
    return res;
}