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

#include "TCPWriter.h"
#include "../Log.h"

void TCPWriter::open() {
    if (isopen) {
        throw std::runtime_error("TCPWriter already open");
    }
    std::unique_lock<std::mutex> lck(mtx);
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        throw std::runtime_error(strerror(errno));
    }
    sockaddr_in addr;
    int status = inet_aton(host.c_str(), (in_addr*)&addr.sin_addr.s_addr);
    if (status < 0) {
        throw std::runtime_error(strerror(errno));
    }
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    status = connect(socket_fd, (sockaddr *)&addr, sizeof(addr));
    if (status < 0) {
        throw std::runtime_error(strerror(errno));
    }
    isopen = true;
}

void TCPWriter::close() {
    if (!isopen) {
        throw std::runtime_error("TCPWriter already closed");
    }
    std::unique_lock<std::mutex> lck(mtx);
    int status = ::close(socket_fd);
    if (status < 0) {
        throw std::runtime_error(strerror(errno));
    }
    isopen = false;
}

void TCPWriter::write(std::shared_ptr<Data> data) {
    write("default", data);
}

void TCPWriter::write(std::string topic, std::shared_ptr<Data> data) {
    if (!isopen) {
        throw std::runtime_error("TCPWriter must be open before writing");
    }
    std::unique_lock<std::mutex> lck(mtx);
    ByteObject serialized(topic);
    data->serialize(&serialized);
    std::vector<uint8_t> bytes = serialized.get_bytes();
    ssize_t data_written = 0;
    ssize_t message_size = bytes.size();
    while (data_written < message_size) {
        ssize_t put = ::write(socket_fd, bytes.data() + data_written, message_size - data_written);
        if (put < 0) {
            throw std::runtime_error(strerror(errno));
        }
        data_written += put;
    }
}

bool TCPWriter::is_open() {
    return isopen;
}

bool TCPWriter::is_closed() {
    return !isopen;
}

void TCPWriter::flush() {

}