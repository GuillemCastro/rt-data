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

#include "ThreadPool.h"

void ThreadPool::init_threads() {
    for (std::size_t i = 0; i < threads.size(); ++i) {
        threads[i] = Thread(&ThreadPool::thread_run, this);
    }
}

void ThreadPool::add_job(std::function<void(void)> job) {
    queue.push(job);
    new_job.notify_one();
}

void ThreadPool::thread_run() {
    while (!stopped) {
        std::unique_lock<std::mutex> lck(wait_mutex);
        new_job.wait(lck, [this]() -> bool {return !queue.empty() || stopped;});
        if (!stopped) {
            while (queue.empty()) {
                ;
            }
            std::function<void(void)> job = queue.pop();
            ++jobs_in_execution;
            job();
            --jobs_in_execution;
        }
    }
}

void ThreadPool::join() {
    if (stopped) {
        return;
    }
    stopped = true;
    new_job.notify_all();
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::set_scheduling_policy(SchedulingPolicy policy, int priority) {
    for (std::size_t i = 0; i < threads.size(); ++i) {
        try {
           threads[i].set_scheduling_policy(policy, priority);
        }
        catch (const std::runtime_error& ex) {
            Log::log(WARNING) << "While setting a ThreadPool's thread scheduling policy an exception was thrown: " << ex.what();
            Log::log(WARNING) << "Are you running as sudo?";
        }
    }
}