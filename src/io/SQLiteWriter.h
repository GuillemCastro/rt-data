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

#include "Writer.h"
#include "../serialization/SQLiteObject.h"

#include <SQLiteCpp/SQLiteCpp.h>

#include <vector>
#include <mutex>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <memory>

/**
 * A concrete implementation of Writer for SQLite databases
 */
class SQLiteWriter : public Writer {

public:

    /**
     * Default constructor.
     * @param file The database file
     */
    explicit SQLiteWriter(const std::string& file) : is_open(false), rt_optimization(false), file(file), buffer_size(500), db(file, SQLite::OPEN_READWRITE) {

    }

    /**
     * Constructor
     * @param file The database file
     * @param bufferSize The maximum size for the buffer. If this size is exceeded, flush() will be called.
     */
    SQLiteWriter(const std::string& file, int bufferSize) : is_open(false), rt_optimization(false), file(file), buffer_size(bufferSize), db(file, SQLite::OPEN_READWRITE) {

    }

    /**
     * Constructor
     * @param file The database file
     * @param optimization Applies some optimizations. MIGHT CAUSE DATA LOSS. The journal is set to memory and SQLite does not
     *          verify if the data has been written to disk by the OS
     */
    SQLiteWriter(const std::string& file, bool optimization) : is_open(false), rt_optimization(optimization), file(file), buffer_size(500), db(file, SQLite::OPEN_READWRITE) {

    }

    /**
     * Constructor
     * @param file The database file
     * @param bufferSize The maximum size for the buffer. If this size is exceeded, flush() will be called.
     * @param optimization Applies some optimizations. MIGHT CAUSE DATA LOSS. The journal is set to memory and SQLite does not
     *          verify if the data has been written to disk by the OS
     */
    SQLiteWriter(const std::string& file, int bufferSize, bool optimization) : is_open(false), rt_optimization(optimization), file(file), buffer_size(bufferSize), db(file, SQLite::OPEN_READWRITE) {

    }

    /**
     * Destructor. Flush remaining inserts and closes the database.
     */
    ~SQLiteWriter() {
        flush();
        close();
    }

    /**
     * Open the writter and allocate all the necessary resources.
     */
    virtual void open();

    /**
     * Does nothing
     */
    virtual void close();

    /**
     * Write an object. Will be buffered. Returning from this function does
     * not guarantee that the object was written (depends on the implementation).
     * flush() will be called if the size of the buffer exceeds buffer_size.
     */
    virtual void write(std::shared_ptr<Data> data);

   /**
     * Write an object. Will be buffered. Returning from this function does
     * not guarantee that the object was written (depends on the implementation).
     * flush() will be called if the size of the buffer exceeds buffer_size.
     */
    virtual void write(std::string topic, std::shared_ptr<Data> data);

    /**
     * Force any buffered object to be written. Returning from this function
     * guarantees that all buffered object have been written.
     */
    virtual void flush();

    /**
     * Is the writer open?
     * @returns Whether the Writer is open or not
     */
    virtual bool isOpen();

    /**
     * Is the writer closed?
     * @returns Whether the Writer is closed or not
     */
    virtual bool isClosed();

private:

    std::vector<SQLiteObject> buffer;

    bool is_open;

    bool rt_optimization;

    std::string file;

    std::size_t buffer_size;

    SQLite::Database db;

    std::mutex mtx;

    std::unordered_map<std::string, SQLite::Statement> prepared_statements;

};