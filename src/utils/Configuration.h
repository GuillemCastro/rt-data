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
#include <vector>

#include "Any.h"

/**
 * A class with the interface that allows to build a configuration data structure with a tree-like structure.
 * The idea is to load the configuration tree from a configuration file.
 * Each node of the tree represents either a property (leaf), an array or another tree.
 * This class contains the implementation for the leaf nodes. The actual tree is implemented at the subclass level (see ConfigurationTreeNode).
 */
class Configuration {

public:

    Configuration() : content(Any::create_any(nullptr)) {

    }

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
     * @param index The position of the node in an array
     * @returns The node in the `index` position
     */
    virtual Configuration& at(const int index);

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param property The name of the node that will be returned
     * @returns A node named `property`
     */
    virtual Configuration& operator[](const std::string &property);

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param index The position of the node in an array
     * @returns The node in the `index` position
     */
    virtual Configuration& operator[](const int index);

    /**
     * Set the content of the current node
     * Note: the underlying configuration file will not be updated
     * @param content The new content for the node
     */
    template <typename T>
    void set(T content) {
        this->content->set<T>(content);
    }

    /**
     * Set the content of the current node
     * Note: the underlying configuration file will not be updated
     * @param content The new content for the node
     */
    template <typename T>
    void operator=(T content) {
        this->set(content);
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
     * The content of the current node.
     * Can contain any type.
     */
    std::shared_ptr<Any> content;

};

/**
 * A class that represents a node with a subtree. Each child is an instance of Configuration.
 * The configuration childs are not loaded until they are acessed for the first time (lazy initialization).
 */
class ConfigurationTreeNode : public Configuration {

public:

    // Use the constructors defined by Configuration
    using Configuration::Configuration;

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param property The name of the node that will be returned
     * @returns A node named `property`
     */
    virtual Configuration& at(const std::string& property);

    /**
     * Get a child of the current node. This operation is not supported on this type of node.
     * @throws std::runtime_error When called
     */
    virtual Configuration& at(const int index);

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

};

class ConfigurationArrayNode : public Configuration {

public:

    // Use the constructors defined by Configuration
    using Configuration::Configuration;

    /**
     * Get a child of the current node. This operation is not supported on this type of node.
     * @throws std::runtime_error When called
     */
    virtual Configuration& at(const std::string& property);

    /**
     * Get a child of the current node
     * Note: if the child does not exist, it will be created
     * @param index The position of the node in an array
     * @returns The node in the `index` position
     */
    virtual Configuration& at(const int index);

protected:

    /**
     * Loads an array from the underlying configuration file into the childs array.
     * Must be implemented by subclasses.
     */
    virtual void load_from_implementation() = 0;

    /**
     * The array of child nodes
     */
    std::vector<std::shared_ptr<Configuration>> childs;

private:

    bool loaded = false;

};
