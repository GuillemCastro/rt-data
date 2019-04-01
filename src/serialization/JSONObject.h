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

#include <nlohmann/json.hpp>

#include <vector>
#include <stdint.h>
#include <stdexcept>

class JSONObject : public SerializedObject {

public:

    JSONObject() : SerializedObject() {

    }

    JSONObject(const nlohmann::json& json) : serialized(json) {

    }

    /**
     * 'Put' methods to serialize objects
     * @param key The preferred key for the value to be serialized.
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
        _put<std::string>(key, value);
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
        return _get<std::string>(key);
    }

    /**
     * Get the resulting JSON
     * @returns The serialized JSON
     */
    nlohmann::json getJSON() {
        return serialized;
    }

    /**
     * Get the resulting JSON as a std::string
     * @returns The serialized JSON
     */
    std::string getJSONString() {
        return serialized.dump();
    }

private:

    template <typename T>
    void _put(std::string key, const T& value) {
        serialized[key] = value;
    }

    template <typename T>
    T _get(std::string key) {
        return serialized[key].get<T>();
    }

    nlohmann::json serialized;

};