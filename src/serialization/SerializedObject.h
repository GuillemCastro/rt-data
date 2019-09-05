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

    virtual void put(const std::string& key, uint64_t value) = 0;

    /**
     * 'Get' methods to deserialize objects
     * @param key The key of the value to be deserialized. Could be ignored by the implementation.
     * @returns The deserialized value.
     */

    virtual int get_int(const std::string& key) = 0;

    virtual unsigned int get_uint(const std::string& key) = 0;

    virtual float get_float(const std::string& key) = 0;

    virtual double get_double(const std::string& key) = 0;

    virtual bool get_bool(const std::string& key) = 0;

    virtual std::string get_string(const std::string& key) = 0;

    virtual uint64_t get_long_int(const std::string& key) = 0;

    /**
     * Obtain the bytes of the serialized object
     * @returns A vector of bytes representing the serialized object
     */
    virtual std::vector<uint8_t> get_bytes() = 0;

};