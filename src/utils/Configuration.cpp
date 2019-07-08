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

#include "Configuration.h"

Configuration& Configuration::at(const std::string& property) {
    throw std::runtime_error("Operation not supported on a leaf node");
}

Configuration& Configuration::at(const int index) {
    throw std::runtime_error("Operation not supported on a leaf node");
}

Configuration& ConfigurationTreeNode::at(const std::string& property) {
    if (childs.find(property) == childs.end()) {
        load_from_implementation(property);
    }
    return *childs[property];
}

Configuration& ConfigurationArrayNode::at(const int index) {
    if (!loaded) {
        load_from_implementation();
        loaded = true;
    }
    return *childs[index];
}

Configuration& Configuration::operator[](const std::string &property) {
    return this->at(property);
}

Configuration& Configuration::operator[](const int index) {
    return this->at(index);
}

Configuration& ConfigurationTreeNode::at(const int index) {
    throw std::runtime_error("Operation not supported on a tree node");
}

Configuration& ConfigurationArrayNode::at(const std::string& property) {
    throw std::runtime_error("Operation not supported on an array node");
}