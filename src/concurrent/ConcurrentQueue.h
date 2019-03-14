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

#include <queue>
#include <mutex>

template <typename T>
class ConcurrentQueue {

public:

    ConcurrentQueue() = default;

    T& pop() {
        std::unique_lock<std::mutex> lck(mtx);
        T& item = q.front();
        q.pop();
        return item;
    }

    void push(T& item) {
        std::unique_lock<std::mutex> lck(mtx);
        q.push(item);
    }

    bool empty() {
        std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

    ConcurrentQueue(const ConcurrentQueue&) = delete;
    
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

private:

    std::queue<T> q;
    std::mutex mtx;

};