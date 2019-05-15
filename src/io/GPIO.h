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

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <stdexcept>

enum Mode {
    INPUT = 0,
    OUTPUT
};

enum PinStatus {
    LOW = 0,
    HIGH
};

/**
 * \class GPIO
 * 
 * \brief A class to control the GPIOs (General Purpose Input Outputs) of your board
 * 
 * An instance of this class manages one single GPIO pin. After opening the GPIO remember
 * to set the mode (INPUT or OUTPUT) of the pin before reading or writing. Reading from a pin
 * not set to INPUT mode or writing to a pin not set to OUTPUT is undefined behaviour.
 * 
 * A GPIO pin is identified by a number. The number of the pin depends on the board you are using,
 * check the documentation for your board.
 */
class GPIO {

public:

    /**
     * Constructor. Build a GPIO object with a pin number.
     * @param pin The number of the pin to manage. 
     */
    GPIO(int pin) : pin(pin) {

    }

    /**
     * Open the pin. After opening remember to set the mode.
     * @throws std::runtime_error If the operation fails
     */
    void open();

    /**
     * Close the pin. No more operations are allowed.
     * @throws std::runtime_error If the operation fails
     */
    void close();

    /**
     * Read the status of the pin (HIGH or LOW).
     * @throws std::runtime_error If the operation fails
     */
    PinStatus read();

    /**
     * Set the status of the pin (HIGH or LOW).
     * @param value The new status of the pin (PinStatus::LOW or PinStatus::HIGH)
     * @throws std::runtime_error If the operation fails
     */
    void write(PinStatus value);

    /**
     * Set the mode of the pin (INPUT or OUTPUT)
     * @param mode The new mode of the pin (Mode::INPUT or Mode::OUTPUT)
     * @throws std::runtime_error If the operation fails
     */
    void setMode(Mode mode);

private:

    int pin;

    static const std::string MODE_IN;
    static const std::string MODE_OUT;

};