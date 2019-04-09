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

#include "Data.h"

/**
 * Interface to implement writters of Data objects.
 */
class Writer {

public:

    /**
     * Open the writter and allocate all the necessary resources.
     */
    virtual void open() = 0;

    /**
     * Closes the writter. All resources are freed.
     * The writter might not be able to reopen (depends on the implementation)
     */
    virtual void close() = 0;

    /**
     * Write an object. Might be buffered. Returning from this function does
     * not guarantee that the object was written (depends on the implementation).
     */
    virtual void write(Data& data) = 0;

    /**
     * Write an object. Might be buffered. Returning from this function does
     * not guarantee that the object was written (depends on the implementation).
     */
    virtual void write(std::string topic, Data& data) = 0;

    /**
     * Force any buffered object to be written. Returning from this function
     * guarantees that all buffered object have been written.
     */
    virtual void flush() = 0;

    /**
     * Is the writer open?
     * @returns Whether the Writer is open or not
     */
    virtual bool isOpen() = 0;

    /**
     * Is the writer closed?
     * @returns Whether the Writer is closed or not
     */
    virtual bool isClosed() = 0;

};