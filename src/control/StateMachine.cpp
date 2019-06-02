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

#include "StateMachine.h"

void StateMachine::add_state(std::shared_ptr<State> state) {
    if (states.find(state->get_name()) != states.end()) {
        throw std::invalid_argument("State already in state machine");
    }
    states[state->get_name()] = state;
    transitions[state->get_name()] = std::vector<std::string>(1);
}

void StateMachine::remove_state(std::shared_ptr<State> state) {
    if (state->get_name() == current_state->get_name()) {
        throw std::invalid_argument("Cannot remove current state");
    }
    else if (states.find(state->get_name()) == states.end()) {
        throw std::invalid_argument("State not in state machine");
    }
    states.erase(state->get_name());
}

State* StateMachine::get_current_state() {
    return current_state;
}

void StateMachine::set_current_state(std::shared_ptr<State> state) {
    if (states.find(state->get_name()) == states.end()) {
        this->add_state(state);
    }
    change_current_state(state->get_name());
}

void StateMachine::change_current_state(const std::string& state_name) {
    current_state->leave();
    current_state = states[state_name].get();
    current_state->arrive();
}

void StateMachine::add_transition(std::shared_ptr<State> from, std::shared_ptr<State> to) {
    if (states.find(from->get_name()) == states.end()) {
        throw std::invalid_argument("From state not in state machine");
    }
    else if (states.find(to->get_name()) == states.end()) {
        throw std::invalid_argument("To state not in state machine");
    }
    transitions[from->get_name()].push_back(to->get_name());
}

void StateMachine::handle(std::string event, std::shared_ptr<Data> data) {
    for (std::string state : transitions[current_state->get_name()]) {
        if (states[state]->check_condition(current_state, event, data)) {
            this->change_current_state(state);
            break;
        }
    }
}