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

#include <string>

#include "time/Timestamp.h"

/**
 * Class that represents data
 */
class Data {

public:

    /**
     * Default constructor
     * Sets the data time to the current time
     */
    Data() : time(Timestamp::now()), origin("unknown") {

    }

    /**
     * Copy constructor
     */
    Data(Data& other) {
        this->time = other.time;
        this->origin = other.origin;
    }

    /**
     * Returns the timestamp when this data was created.
     */
    Timestamp& getTimestamp();

    /**
     * Returns who generated this data.
     */
    std::string& getOrigin();

    /**
     * Set the timestamp when this data was created.
     */
    void setTimestamp(Timestamp& time);

    /**
     * Sets who generated this data.
     */
    void setOrigin(std::string& origin);

protected:

    /**
     * The time when this data was generated.
     */
    Timestamp time;

    /**
     * Who generated this data.
     */
    std::string origin;

};