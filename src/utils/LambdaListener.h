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

#include <functional>

#include "Listener.h"

/**
 * A concrete implementation of Listener that uses an anonymous function
 * to handle the event
 */
class LambdaListener : public Listener {

public:

    /**
     * Constructor
     * @param listener The anonymous function that will handle the event
     * The signature of the anonymous function must be,
     * void(std::string,std::shared_ptr<Data>)> listener);
     */
    LambdaListener(std::function<void(std::string, std::shared_ptr<Data>)> listener) : listener(listener) {

    }

    /**
     * Called when the Broker dispatches an event in a subscribed topic.
     * The previously passed anonymous function will handle the event
     * @param topic The topic that has a new event
     * @param data The associated data for the event
     */
    virtual void handle(std::string topic, std::shared_ptr<Data> data) override;

private:

    std::function<void(std::string, std::shared_ptr<Data>)> listener;


};