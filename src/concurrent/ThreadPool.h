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

#include <thread>
#include <atomic>
#include <vector>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "concurrent/ConcurrentQueue.h"

/**
 * A class to manage a thread pool
 */
class ThreadPool {

public:

    /**
     * Default constructor
     * By default build the pool with 10 threads
     */
    ThreadPool() : thread_count(10), 
        threads(std::vector<std::thread>(10)), 
        stopped(false),
        jobs_in_execution(0) {
        init_threads();
    }

    /**
     * Build a pool with 'count' number of threads
     * @param count The number of threads of the pool
     */
    ThreadPool(int count) : thread_count(count), 
        threads(std::vector<std::thread>(count)), 
        stopped(false),
        jobs_in_execution(0) {
        init_threads();
    }

    /**
     * Destructor. Joins all threads. 
     */
    ~ThreadPool() {
        join();
    }

    /**
     * Queue a new job to be executed by the pool
     * @param job A function to be executed. Must have no parameters and return nothing.
     */
    void addJob(std::function<void(void)> job);

    /**
     * Wait for all the jobs in execution and join the threads
     * Note: all the queued jobs are discarded
     */
    void join();

    /**
     * Get the number of threads managed by the class
     * @returns the number of threads managed by the class
     */
    int size() {
        return thread_count;
    }

    /**
     * Get the number of jobs in execution
     * @returns the number of jobs in execution
     */
    int inExecution() {
        return jobs_in_execution;
    }

private:

    int thread_count;

    std::atomic<int> jobs_in_execution;

    std::atomic<bool> stopped;

    ConcurrentQueue<std::function<void(void)>> queue;

    std::vector<std::thread> threads;

    std::condition_variable new_job;

    std::mutex wait_mutex;

    void thread_run();

    void init_threads();

};