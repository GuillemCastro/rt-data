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
#include <unordered_map>
#include <memory>
#include <vector>

/**
 * Interface for serialized containers.
 */
class SerializedObject {

public:

    SerializedObject() = default;

    /**
     * 'Put' methods to serialize objects
     * @param key The preferred key for the value to be serialized. Could be ignored by the implementation.
     * @param value The value to be serialized.
     */

    virtual void put(const std::string& key, int value) = 0;

    virtual void put(const std::string& key, unsigned int value) = 0;

    virtual void put(const std::string& key, float value) = 0;

    virtual void put(const std::string& key, double value) = 0;

    virtual void put(const std::string& key, bool value) = 0;

    virtual void put(const std::string& key, std::string value) = 0;

    /**
     * 'Get' methods to deserialize objects
     * @param key The key of the value to be deserialized. Could be ignored by the implementation.
     * @returns The deserialized value.
     */

    virtual int getInt(const std::string& key) = 0;

    virtual unsigned int getUInt(const std::string& key) = 0;

    virtual float getFloat(const std::string& key) = 0;

    virtual double getDouble(const std::string& key) = 0;

    virtual bool getBool(const std::string& key) = 0;

    virtual std::string getString(const std::string& key) = 0;

    /**
     * Obtain the bytes of the serialized object
     * @returns A vector of bytes representing the serialized object
     */
    virtual std::vector<uint8_t> getBytes() = 0;

};