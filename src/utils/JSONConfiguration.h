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

#include <fstream>

#include "Configuration.h"
#include <nlohmann/json.hpp>

/**
 * A class that represents a configuration file with a tree-like structure, loaded from a JSON file.
 * Each node of the tree represents either a property (leaf) or another tree.
 * The configuration properties are not loaded until they are acessed for the first time (lazy initialization).
 */
class JSONConfiguration : public Configuration {

public:

    /**
     * Constructor with filename
     * Loads and parses the passed filename as a JSON file.
     * @param file The filename of a JSON file.
     */
    JSONConfiguration(std::string file) : Configuration() {
        std::ifstream i(file);
        this->file = nlohmann::json::parse(i);
    }

    /**
     * Constructor with a JSON object
     * @param file A JSON object
     */
    JSONConfiguration(const nlohmann::json& file) : file(file) {

    }

    // Use the constructors defined for Configuration
    using Configuration::Configuration;

protected:

    /**
     * Loads from the JSON file the passed property into the child nodes map.
     * @param property The property to be loaded.
     */
    virtual void load_from_implementation(const std::string& property);

private:

    nlohmann::json file;

};