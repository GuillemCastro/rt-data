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

#include "StateMachineTest.h"

void StateMachineTest::addStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    StateMachine sm(s);
    CPPUNIT_ASSERT(s->arrive_called);
}

void StateMachineTest::addStateTwiceTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    StateMachine sm(s);
    bool exception_thrown = false;
    try {
        sm.add_state(s);
    }
    catch(std::invalid_argument& e) {
        exception_thrown = true;
    }
    if (!exception_thrown) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void StateMachineTest::removeStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    sm.add_state(s2);
    sm.remove_state(s2);
}

void StateMachineTest::removeInexistingStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    bool exception_thrown = false;
    try {
        sm.remove_state(s2);
    }
    catch(std::invalid_argument& e) {
        exception_thrown = true;
    }
    if (!exception_thrown) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void StateMachineTest::removeCurrentStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    StateMachine sm(s);
    bool exception_thrown = false;
    try {
        sm.remove_state(s);
    }
    catch(std::invalid_argument& e) {
        exception_thrown = true;
    }
    if (!exception_thrown) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void StateMachineTest::getCurrentStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    StateMachine sm(s);
    CPPUNIT_ASSERT(s.get() == sm.get_current_state());
}

void StateMachineTest::setCurrentStateTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    sm.set_current_state(s2);
    CPPUNIT_ASSERT(s2.get() == sm.get_current_state());
    CPPUNIT_ASSERT(s->leave_called && s->arrive_called);
    CPPUNIT_ASSERT(s2->arrive_called);
}

void StateMachineTest::addTransitionTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    sm.add_state(s2);
    sm.add_transition(s, s2);
}

void StateMachineTest::addTransitionNonExistingTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    bool exception_thrown = false;
    try {
        sm.add_transition(s, s2);
    }
    catch(std::invalid_argument& e) {
        exception_thrown = true;
    }
    if (!exception_thrown) {
        CPPUNIT_FAIL("Exception expected");
    }
}

void StateMachineTest::handleTest() {
    std::shared_ptr<StateStub> s = std::make_shared<StateStub>("test");
    std::shared_ptr<StateStub> s2 = std::make_shared<StateStub>("test2");
    StateMachine sm(s);
    sm.add_state(s2);
    sm.add_transition(s, s2);
    sm.handle("test", std::make_shared<Data>());
    CPPUNIT_ASSERT(s->leave_called && s->arrive_called);
    CPPUNIT_ASSERT(s2->arrive_called);
}