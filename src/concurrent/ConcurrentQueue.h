/*
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

/**
 * \class ConcurrentQueue
 * \brief A thread-safe (blocking) queue.
 */
template <typename T>
class ConcurrentQueue {

public:

    /**
     * Default constructor.
     */
    ConcurrentQueue() = default;

    /**
     * Delete and return the first element from the queue.
     * @returns the first element of the queue.
     */
    T pop() {
        std::unique_lock<std::mutex> lck(mtx);
        T item = q.front();
        q.pop();
        return item;
    }

    /**
     * Add a new item to the back of the queue.
     * @params item An item to be stored in the queue.
     */
    void push(T item) {
        std::unique_lock<std::mutex> lck(mtx);
        q.push(item);
    }

    /**
     * Is the queue empty?
     * @returns Whether the queue is empty or not.
     */
    bool empty() {
        std::unique_lock<std::mutex> lck(mtx);
        return q.empty();
    }

    //Do not allow copy or assignment.

    ConcurrentQueue(const ConcurrentQueue&) = delete;
    
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete;

private:

    std::queue<T> q;
    std::mutex mtx;

};