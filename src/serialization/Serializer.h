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

#include "serialization/Serializable.h"

/**
 * A helper class to serialize and deserialize objects
 */
class Serializer {

public:

    /**
     * Serialize a Serializable into an object of class Destination
     * Note: Destination must be subclass of SerializedObject
     * @params serializable The object to serialize
     * @returns The serialized object
     */
    template <class Destination>
    Destination serialize(Serializable& serializable) {
        static_assert(
            std::is_base_of<SerializedObject, Destination>::value, 
            "The destination class must be derived from 'SerializedObject'");
        Destination object;
        serializable.serialize(&object);
        return object;
    }

    /**
     * Deserialize a SerializedObject into an object of class Destination
     * Note: Destination must be subclass of Serializable
     * @params serializable The object to deserialize
     * @returns The deserialized object
     */
    template <class Destination>
    Destination deserialize(SerializedObject& object) {
        static_assert(
            std::is_base_of<Serializable, Destination>::value, 
            "The destination class must be derived from 'Serializable'");
        Destination destination;
        destination.deserialize(&object);
        return destination;
    }

};