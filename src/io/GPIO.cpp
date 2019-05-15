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

#include "GPIO.h"

const std::string GPIO::MODE_IN = "in";
const std::string GPIO::MODE_OUT = "out";

void GPIO::open() {
	int fd = ::open("/sys/class/gpio/export", O_WRONLY);
	if (fd < 0) {
		throw std::runtime_error("Failed to open GPIO");
	}
    char buffer[10];
	ssize_t size = snprintf(buffer, 10, "%d", pin);
	int ret = ::write(fd, buffer, size);
	if (ret < 0) {
		throw std::runtime_error("Failed to open GPIO");
	}
	::close(fd);
}

void GPIO::close() {
	int fd = ::open("/sys/class/gpio/unexport", O_WRONLY);
	if (fd < 0) {
		throw std::runtime_error("Failed to open unexport for closing");
	}
	char buffer[10];
	ssize_t size = snprintf(buffer, 10, "%d", pin);
	int ret = ::write(fd, buffer, size);
	if (ret < 0) {
		throw std::runtime_error("Failed to close GPIO");
	}
	::close(fd);
}

PinStatus GPIO::read() {
	char path[50];
	snprintf(path, 50, "/sys/class/gpio/gpio%d/value", pin);
	int fd = ::open(path, O_RDONLY);
	if (fd < 0) {
		throw std::runtime_error("Failed to open GPIO for reading");
	}
	char value_str[3];
	int ret = ::read(fd, value_str, 3);
	if (ret < 0) {
		throw std::runtime_error("Failed to read from GPIO");
	}
	::close(fd);
	return (PinStatus) atoi(value_str);
}

void GPIO::write(PinStatus value) {
	char path[50];
	snprintf(path, 50, "/sys/class/gpio/gpio%d/value", pin);
	char write_value[3];
	snprintf(write_value, 3, "%d", (int)value);
	int fd = ::open(path, O_WRONLY);
	if (fd < 0) {
		throw std::runtime_error("Failed to open GPIO for writing");
	}
	int ret = ::write(fd, write_value, 1);
	if (ret < 0) {
		throw std::runtime_error("Failed write to GPIO");
	}
	::close(fd);
}

void GPIO::setMode(Mode mode) {
	char path[50];
	snprintf(path, 50, "/sys/class/gpio/gpio%d/direction", pin);
	int fd = ::open(path, O_WRONLY);
	if (fd < 0) {
		throw std::runtime_error("Failed to open GPIO for changing mode");
	}
	std::string gpio_mode = (mode == Mode::INPUT)? MODE_IN : MODE_OUT;
	int ret = ::write(fd, gpio_mode.data(), gpio_mode.size());
	if (ret < 0) {
		throw std::runtime_error("Failed to set GPIO mode");
	}
	::close(fd);
}