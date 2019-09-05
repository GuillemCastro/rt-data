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
#include "../serialization/Serializer.h"
#include "../serialization/ByteObject.h"

#include <fstream>
#include <mutex>

template <typename SerializationClass>
class FileWriter : public Writer {

public:

    /**
     * Constructor with filename
     * @param file The name of the file to write to.
     */
    FileWriter(const std::string file) : filename(file) {

    }

    /**
     * Open the file for writing
     * @throws std::runtime_error if the file is already open
     */
    virtual void open() override {
        if (isOpen()) {
            throw std::runtime_error("Already open");
        }
        file.open(filename, std::ofstream::out | std::ofstream::binary | std::ofstream::ate);
    }

    /**
     * Closes the file. No more writes are allowed
     * @throws std::runtime_error if the file is already closed
     */
    virtual void close() override {
        if (isClosed()) {
            throw std::runtime_error("Already closed");
        }
        file.close();
    }

    /**
     * Write a data to the file with the default topic
     * @param data The data to be written
     * @throws std::runtime_error if the file is not open
     */
    virtual void write(std::shared_ptr<Data> data) override {
        write("default", data);
    }

    /**
     * Write a data to the file with a topic
     * @param topic The topic of the data
     * @param data The data to be written
     * @throws std::runtime_error if the file is not open
     */
    virtual void write(std::string topic, std::shared_ptr<Data> data) override {
        if (isClosed()) {
            throw std::runtime_error("FileWriter must be open before writing");
        }
        std::unique_lock<std::mutex> lck(mtx);
        SerializationClass serialized(topic);
        data->serialize(&serialized);
        std::vector<uint8_t> bytes = serialized.getBytes();
        file.write((char *)bytes.data(), bytes.size());
    }

    /**
     * Forces the file to be written to disk
     */
    virtual void flush() override {
        file.flush();
    }

    /**
     * Is the file open?
     * @returns Whether or not the file is open
     */
    virtual bool is_open() override {
        return file.is_open();
    }

    /**
     * Is the file closed?
     * @returns Whether or not the file is closed
     */
    virtual bool is_open() override {
        return !file.is_open();
    }

private:

    std::string filename;

    std::ofstream file;

    Serializer serializer;

    std::mutex mtx;

};