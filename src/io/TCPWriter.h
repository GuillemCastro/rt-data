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

#include "Writer.h"
#include "../Log.h"
#include "../serialization/Serializer.h"
#include "../serialization/ByteObject.h"

#include <atomic>
#include <mutex>

#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
 * Class to send Data objects through a TCP socket
 */
class TCPWriter : public Writer {

public:

    /**
     * Default constructor
     */
    TCPWriter(const std::string& host, int port) : host(host), port(port), is_open(false) {

    }

    /**
     * Destructor. By default closes the socket.
     */
    ~TCPWriter() {
        if (is_open) {
            try {
                close();
            }
            catch(...) {}
        }
    }

    /**
     * Open the socket, call it before writing data
     * @throws std::runtime_error When the socket is already open
     */
    virtual void open();

    /**
     * Close the socket
     * @throws std::runtime_error When the socket has been already closed
     */
    virtual void close();

    /**
     * Write the Data object to the socket with the default topic
     * @param data The Data object to write to the socket
     * @throws std::runtime_error If the TCPWriter has not been opened
     */
    virtual void write(std::shared_ptr<Data> data);

    /**
     * Write the Data object to the socket with a topic
     * @param topic The topic of the associated data
     * @param data The Data object to write to the socket
     * @throws std::runtime_error If the TCPWriter has not been opened
     */
    virtual void write(std::string topic, std::shared_ptr<Data> data);

    /**
     * Does nothing
     */
    virtual void flush();

    /**
     * Is the TCPWriter open?
     * @returns Whether or not the TCPWriter is open
     */
    virtual bool isOpen();

    /**
     * Is the TCPWriter closed?
     * @returns Whether or not the TCPWriter is closed
     */
    virtual bool isClosed();

private:

    std::string host;

    int port;

    std::atomic<bool> is_open;

    int socket_fd;

    std::mutex mtx;

    Serializer serializer;

};