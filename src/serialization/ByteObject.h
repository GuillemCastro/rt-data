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

#include "serialization/SerializedObject.h"

#include <vector>
#include <stdint.h>
#include <stdexcept>

class ByteObject : public SerializedObject {

public:

    ByteObject() : SerializedObject() {

    }

    ByteObject(const std::vector<uint8_t> bytes) : bytes(bytes) {

    }

    /**
     * 'Put' methods to serialize objects
     * @param key The preferred key for the value to be serialized. This parameter is ignored.
     * @param value The value to be serialized.
     */

    virtual void put(const std::string& key, int value) {
        _put<int>(key, value);
    }

    virtual void put(const std::string& key, unsigned int value) {
        _put<unsigned int>(key, value);
    }

    virtual void put(const std::string& key, float value) {
        _put<float>(key, value);
    }

    virtual void put(const std::string& key, double value) {
        _put<double>(key, value);
    }

    virtual void put(const std::string& key, bool value) {
        _put<bool>(key, value);
    }

    virtual void put(const std::string& key, std::string value) {
        _put_string(key, value);
    }

    /**
     * 'Get' methods to deserialize objects
     * @param key The key of the value to be deserialized. This parameter is ignored.
     * @returns The deserialized value.
     */

    virtual int getInt(const std::string& key) {
        return _get<int>(key);
    }

    virtual unsigned int getUInt(const std::string& key) {
        return _get<int>(key);
    }

    virtual float getFloat(const std::string& key) {
        return _get<float>(key);
    }

    virtual double getDouble(const std::string& key) {
        return _get<double>(key);
    }

    virtual bool getBool(const std::string& key) {
        return _get<bool>(key);
    }

    virtual std::string getString(const std::string& key) {
        return _get_string(key);
    }

    /**
     * Get the resulting bytes.
     * @returns A vector of bytes that representing the serialization
     *      of all passed values.
     * Every value has prepended its size (or lenght)
     * |size of object1|object1 bytes|size of object2|object2 bytes|
     */
    std::vector<uint8_t> getBytes() {
        return bytes;
    }

private:

    template <typename T>
    void _put(std::string key, const T& value) {
        const uint8_t* serialized = reinterpret_cast<const uint8_t*>(&value);
        bytes.push_back((uint8_t) sizeof(T));
        for (int i = 0; i < sizeof(value); ++i) {
            bytes.push_back(serialized[i]);
        }
    }

    void _put_string(std::string key, const std::string& value) {
        bytes.push_back((uint8_t) value.size());
        for (char character : value) {
            bytes.push_back((uint8_t) character);
        }
    }

    template <typename T>
    T _get(std::string key) {
        if (sizeof(T) > bytes.size()) {
            throw std::out_of_range("Not enough remaining bytes to be deserialized");
        }
        if (bytes[0] != sizeof(T)) {
            throw std::length_error("The asked type size does not match the stored value size");
        }
        T result;
        uint8_t* deserialized = reinterpret_cast<uint8_t*>(&result);
        for (int i = 1; i <= sizeof(T) && i < bytes.size(); ++i) {
            deserialized[i-1] = bytes[i];
        }
        bytes.erase(bytes.begin(), bytes.begin() + sizeof(T) + 1);
        return result;
    }

    std::string _get_string(std::string key) {
        if (bytes.size() <= 1) {
            throw std::out_of_range("Not enough remaining bytes to be deserialized");
        }
        uint8_t size = bytes[0];
        std::string result;
        for (int i = 1; i <= size; ++i) {
            result.push_back(bytes[i]);
        }
        bytes.erase(bytes.begin(), bytes.begin() + size + 1);
        return result;
    }

    std::vector<uint8_t> bytes;

};