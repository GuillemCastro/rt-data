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
#include "../serialization/JSONObject.h"

#include <nlohmann/json.hpp>
#include <curl/curl.h>

#include <mutex>
#include <atomic>

/**
 * Class to send Data objects to HTTP endpoints using POST requests formatted in JSON
 */
class HTTPWriter : public Writer {

public:

    /**
     * Default constructor
     * @param url The URL of the HTTP endpoint
     */
    explicit HTTPWriter(const std::string& url) : url(url) {

    }

    /**
     * Initializes the HTTPWriter and the cURL backend
     */
    virtual void open();

    /**
     * Cleans up all the memory used for the connection
     */
    virtual void close();

    /**
     * Send a data to the HTTP endpoint with the default topic
     * @param data The Data to be sent
     */
    virtual void write(std::shared_ptr<Data> data);

    /**
     * Send a data to the HTTP endpoint with a topic
     * @param topic The topic of the associated data
     * @param data The Data to be sent
     */
    virtual void write(std::string topic, std::shared_ptr<Data> data);

    /**
     * Is the HTTPWriter open?
     * @returns Whether or not this object has been initialized
     */
    virtual bool isOpen();

    /**
     * Is the HTTPWriter closed?
     * @returns Whether or not this object has been cleaned up
     */
    virtual bool isClosed();

    /**
     * Does nothing
     */
    virtual void flush();

private:

    static std::atomic<bool> curl_init;

    std::string url;

    Serializer serializer;

    std::mutex mtx;

};