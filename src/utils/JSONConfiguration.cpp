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

#include "JSONConfiguration.h"
#include "Log.h"

void JSONConfiguration::load_from_implementation(const std::string& property) {
    if (file.find(property) != file.end()) {
        if (not file[property].is_object() and not file[property].is_array()) {
            std::shared_ptr<Any> new_content;
            if (file[property].is_boolean()) {
                new_content = Any::create_any<bool>(file[property].get<bool>());
            }
            else if (file[property].is_string()) {
                new_content = Any::create_any<std::string>(file[property].get<std::string>());
            }
            else if (file[property].is_number_float()) {
                new_content = Any::create_any<double>(file[property].get<double>());
            }
            else if (file[property].is_number_unsigned()) {
                new_content = Any::create_any<uint64_t>(file[property].get<uint64_t>());
            }
            else if (file[property].is_number_integer()) {
                new_content = Any::create_any<int64_t>(file[property].get<int64_t>());
            }
            childs[property] = std::make_shared<JSONConfiguration>(new_content);
        }
        else {
            childs[property] = std::make_shared<JSONConfiguration>(file[property]);
        }
    }
    else {
        childs[property] = std::make_shared<JSONConfiguration>();
    }
}