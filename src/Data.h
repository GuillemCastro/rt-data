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

#pragma once

#include <string>

#include "time/Timestamp.h"
#include "serialization/Serializable.h"

/**
 * Class that represents data
 */
class Data : public Serializable {

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
    Data(Data& other) : time(other.time), origin(other.origin) {

    }

    /**
     * Assignment operator
     */
    Data& operator=(const Data& other) {
        if (this != &other) {
            this->time = other.time;
            this->origin = other.origin;
        }
        return *this;
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

    /**
     * Serialize the Data. Do not call directly.
     * @param object The resulting SerializedObject where the data must be saved.
     */
    virtual void serialize(SerializedObject* object) override {
        object->put("timestamp", (unsigned int) time.toNanos());
        object->put("origin", origin);
    }

    /**
     * Deserialize the Data. Do not call directly.
     * @param object The SerializedObject to load the data from.
     */
    virtual void deserialize(SerializedObject* object) override {
        time = Timestamp(object->getUInt("timestamp"));
        origin = object->getString("origin");
    }

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