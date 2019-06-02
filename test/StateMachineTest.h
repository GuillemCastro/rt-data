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

#include "control/StateMachine.h"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class StateMachineTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(StateMachineTest);
    CPPUNIT_TEST(addStateTest);
    CPPUNIT_TEST(addStateTwiceTest);
    CPPUNIT_TEST(removeStateTest);
    CPPUNIT_TEST(removeInexistingStateTest);
    CPPUNIT_TEST(removeCurrentStateTest);
    CPPUNIT_TEST(getCurrentStateTest);
    CPPUNIT_TEST(setCurrentStateTest);
    CPPUNIT_TEST(addTransitionTest);
    CPPUNIT_TEST(addTransitionNonExistingTest);
    CPPUNIT_TEST(handleTest);
    CPPUNIT_TEST_SUITE_END();

public:

    void addStateTest();

    void addStateTwiceTest();

    void removeStateTest();

    void removeInexistingStateTest();

    void removeCurrentStateTest();

    void getCurrentStateTest();

    void setCurrentStateTest();

    void addTransitionTest();

    void addTransitionNonExistingTest();

    void handleTest();

private:



};

CPPUNIT_TEST_SUITE_REGISTRATION( StateMachineTest );

class StateStub : public State {

public:

    StateStub(const std::string& name) {
        set_name(name);
    }

    virtual void arrive() {
        arrive_called = true;
    }

    virtual void leave() {
        leave_called = true;
    }

    virtual bool check_condition(State* current_state, std::string event, std::shared_ptr<Data> data) {
        check_called = true;
        return true;
    }

    bool arrive_called = false;

    bool leave_called = false;

    bool check_called = false;

};