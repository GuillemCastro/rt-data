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

#include "../Listener.h"
#include "State.h"

#include <unordered_set>

/**
 * \class StateMachine
 * 
 * \brief A class to implement simple finite state machines
 * 
 * This class can be used to implement simple finite state machines.
 * You must register StateMachine instances in the event Broker.
 * 
 * Each time the Broker dispatches an event to the StateMachine,
 * it will check if any of the transitions is possible (by calling
 * the check_condition() method on the destination States). 
 * 
 * If any of them is possible, it will first call the leave() method
 * from the origin State, and then the arrive() method on the destination
 * State.
 * 
 * You can also force a state change by calling set_current_state().
 * 
 */
class StateMachine : public Listener {

public:

    /**
     * Build a StateMachine with an initial state
     * @param start_state The initial state of the state machine
     */
    StateMachine(std::shared_ptr<State> start_state) {
        states.insert(start_state);
        current_state = start_state.get();
        transitions[current_state] = std::vector<State*>();
        current_state->arrive();
    }

    /**
     * Add a new state to the state machine
     * @param state the state to be added
     * @throws std::invalid_argument If the state is already in the state machine
     */
    void add_state(std::shared_ptr<State> state);

    /**
     * Remove a state from the state machine
     * @param state The state to be removed
     * @throws std::invalid_argument If the state is the current state
     * @throws std::invalid_argument If the state is not in the state machine
     */
    void remove_state(std::shared_ptr<State> state);

    /**
     * Get the current state
     * @returns the current state
     */
    State* get_current_state();

    /**
     * Set a state as the current state. If the state was not in the state machine, it will be added to it.
     * @param state The new current state
     */
    void set_current_state(std::shared_ptr<State> state);

    /**
     * Add a transition between two states.
     * @param from The origin state of the transition
     * @param to The destination state of the transition
     * @throws std::invalid_argument If either of the states is not in the state machine.
     */
    void add_transition(std::shared_ptr<State> from, std::shared_ptr<State> to);

    /**
     * Called when the Broker dispatches an event in a subscribed topic
     * @param topic The topic that has a new event
     * @param data The associated data for the event
     */
    void handle(std::string event, std::shared_ptr<Data> data);

private:

    /**
     * Change the current state
     * @param state The new current state
     */
    void change_current_state(State* state);

    State* current_state;

    std::unordered_set<std::shared_ptr<State>> states;

    std::unordered_map<State*, std::vector<State*>> transitions;

};