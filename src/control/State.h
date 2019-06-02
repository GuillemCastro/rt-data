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

#include "../Data.h"


/**
 * \class State
 * 
 * \brief Abstract class that represent one StateMachine state
 * 
 * This class can be derived to implement custom states or you
 * can use the derived LambdaState.
 * 
 * When the StateMachine receives a new event, it will call
 * check_condition() to check if it's possible to change to
 * this state.
 * 
 * If check_condition() returns true, this state will become
 * the current state of the StateMachine.
 * 
 * When a State becomes the current state, the StateMachine
 * call its arrive() method. When a State stops being the
 * current state, the StateMachine will call its leave()
 * method.
 * 
 * A State is uniquely identified by its name.
 * 
 */
class State {

public:

    /**
     * A method that is called by a StateMachine when this state becomes the current state.
     */
    virtual void arrive() = 0;

    /**
     * A method that is called by a StateMachine when this state stops being the current state.
     */
    virtual void leave() = 0;

    /**
     * A method that is called by a StateMachine to check if it should become the current state.
     */
    virtual bool check_condition(State* current_state, std::string event, std::shared_ptr<Data> data) = 0;

    /**
     * Get the name of the State
     */
    const std::string& get_name() const;

    /**
     * Set the name of the state
     * @param name The new name of the state
     */
    void set_name(const std::string& name);

private:

    std::string name;

};