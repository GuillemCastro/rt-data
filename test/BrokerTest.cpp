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

#include "BrokerTest.h"
#include "SensorStub.h"

#include <chrono>
#include <iostream>

void BrokerTest::dispatchTest() {
    std::mutex mutex;
    std::condition_variable cond_var;
    std::atomic<bool> dispatched(false);
    broker->start();
    broker->subscribe("test", [this, &dispatched, &cond_var](std::string topic, std::shared_ptr<Data> data) {
        std::shared_ptr<IntData> int_data = std::static_pointer_cast<IntData>(data);
        CPPUNIT_ASSERT(5 == int_data->getValue());
        dispatched = true;
        cond_var.notify_one();
    });
    std::unique_lock<std::mutex> lck(mutex);
    std::shared_ptr<Data> data = std::make_shared<IntData>(5);
    broker->dispatch("test", data);
    cond_var.wait_for(lck, std::chrono::seconds(1));
    CPPUNIT_ASSERT(dispatched);
}