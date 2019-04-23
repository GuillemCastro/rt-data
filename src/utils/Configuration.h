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

#include "Any.h"

/**
 * An interface that represents a configuration file with a tree-like structure
 * Each node of the tree represents either a property (leaf) or another tree.
 * The configuration properties are not loaded until they are acessed for the first time (lazy initialization).
 */
class Configuration {

public:

    /**
     * Default constructor
     */
    Configuration() : content(nullptr) {

    }

    /**
     * Constructor to build a leaf
     * @param content The content of the leaf
     */
    Configuration(std::shared_ptr<Any> content) : content(content) {

    }

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param property The name of the node that will be returned
     * @returns A node named `property`
     */
    virtual Configuration& at(const std::string& property);

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param property The name of the node that will be returned
     * @returns A node named `property`
     */
    virtual Configuration& operator[](const std::string &property);

    /**
     * Set the content of the current node
     * Note: the underlying configuration file will not be updated
     * @param content The new content for the node
     */
    template <typename T>
    void set(const T& content) {
        if (this->content == nullptr) {
            this->content = Any::create_any<T>(content);
        }
        else {
            this->content->set<T>(content);
        }
    }

    /**
     * Set the content of the current node
     * Note: the underlying configuration file will not be updated
     * @param content The new content for the node
     */
    template <typename T>
    void operator=(const T& s)  {
        this->set<T>(content);
    }

    /**
     * Get the content of the current node
     * @returns The content of the current node
     */
    template <typename T>
    T get() {
        return content->get<T>();
    }

protected:

    /**
     * Loads the passed child property into the childs map.
     * Must be implemented by subclasses.
     * @param property The property that has to be loaded
     */
    virtual void load_from_implementation(const std::string& property) = 0;

    /**
     * The map of child nodes. Child nodes are identified by a string (property).
     */
    std::unordered_map<std::string, std::shared_ptr<Configuration>> childs;

    /**
     * The content of the current node.
     * Can contain any type.
     */
    std::shared_ptr<Any> content;

};