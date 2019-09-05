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
 * This class can also represent a JSON object in a JSON document.
 * Each node of the tree represents either a property (leaf), an array or another tree.
 * The configuration properties are not loaded until they are acessed for the first time (lazy initialization).
 */
class JSONObjectConfiguration : public ConfigurationTreeNode {

public:

    /**
     * Constructor with filename
     * Loads and parses the passed filename as a JSON file.
     * @param file The filename of a JSON file.
     */
    explicit JSONObjectConfiguration(std::string file) : ConfigurationTreeNode() {
        std::ifstream i(file);
        this->file = nlohmann::json::parse(i);
    }

    /**
     * Constructor with a JSON object
     * @param file A JSON object
     */
    explicit JSONObjectConfiguration(const nlohmann::json& file) : ConfigurationTreeNode(), file(file) {

    }

    /**
     * Default constructor
     */
    JSONObjectConfiguration() : ConfigurationTreeNode() {

    }

    /**
     * Constructor to build a leaf
     * @param content The content of the leaf
     */
    explicit JSONObjectConfiguration(std::shared_ptr<Any> content) : ConfigurationTreeNode(content) {

    }

protected:

    /**
     * Loads from the JSON file the passed property into the child nodes map.
     * @param property The property to be loaded.
     */
    virtual void load_from_implementation(const std::string& property);

private:

    nlohmann::json file;

};

/**
 * A class that represents a configuration array, loaded from a JSON file.
 * All the array is loaded at once.
 */
class JSONArrayConfiguration : public ConfigurationArrayNode {

public:

    /**
     * Constructor with filename
     * Loads and parses the passed filename as a JSON file.
     * @param file The filename of a JSON file.
     */
    explicit JSONArrayConfiguration(std::string file) : ConfigurationArrayNode() {
        std::ifstream i(file);
        this->file = nlohmann::json::parse(i);
    }

    /**
     * Constructor with a JSON object
     * @param file A JSON object
     */
    explicit JSONArrayConfiguration(const nlohmann::json& file) : ConfigurationArrayNode(), file(file) {

    }

    /**
     * Default constructor
     */
    JSONArrayConfiguration() : ConfigurationArrayNode() {

    }

    /**
     * Constructor to build a leaf
     * @param content The content of the leaf
     */
    explicit JSONArrayConfiguration(std::shared_ptr<Any> content) : ConfigurationArrayNode(content) {

    }

protected:

    /**
     * Load the array from the JSON file
     */
    virtual void load_from_implementation();

private:

    inline void load_child(const int index);

    nlohmann::json file;

};

using JSONConfiguration = JSONObjectConfiguration;
