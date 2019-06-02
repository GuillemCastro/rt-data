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

#include "State.h"

#include <functional>

/**
 * \class LambdaState
 * 
 * \brief A concrete State with lambdas
 * 
 * Instead of subclassing State, you can also use this class to implement a State. 
 * 
 * arrive(), leave() and check_condition() are just wrappers for the lambdas.
 * 
 */
class LambdaState : public State {

public:

    /**
     * Build a new state with lambdas for arrive, leave and check_condition
     * @param name The name of the state
     * @param arrive A lambda that will be called when arrive() is invoked
     * @param leave A lambda that will be called when leave() is invoked
     * @param check A lambda that will be called when check_condition() is invoked
     */
    LambdaState(const std::string& name, std::function<void()> arrive, std::function<void()> leave, 
        std::function<bool(State* current_state, std::string event, std::shared_ptr<Data> data)> check) : 
        arrive_lambda(arrive), leave_lambda(leave), check_lambda(check) {
            set_name(name);    
    }    

    /**
     * A method that is called by a StateMachine when this state becomes the current state.
     * It will just call the arrive lambda.
     */
    virtual void arrive();

    /**
     * A method that is called by a StateMachine when this state stops being the current state.
     * It will just call the leave lambda.
     */
    virtual void leave();

    /**
     * A method that is called by a StateMachine to check if it should become the current state.
     * It will just call the check lambda.
     */
    virtual bool check_condition(State* current_state, std::string event, std::shared_ptr<Data> data);

private:

    std::function<void()> arrive_lambda;

    std::function<void()> leave_lambda;

    std::function<bool(State* current_state, std::string event, std::shared_ptr<Data> data)> check_lambda;

};