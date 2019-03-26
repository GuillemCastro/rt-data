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

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Broker.h"

class BrokerTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(BrokerTest);
    CPPUNIT_TEST(dispatchTest);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp() {
        broker = std::make_shared<Broker>();
    }

    void tearDown() {
        try {
            broker->stop();
        }
        catch (const std::runtime_error&) {

        }
        broker.reset();
    }

    void dispatchTest();


private:

    std::shared_ptr<Broker> broker;

};

CPPUNIT_TEST_SUITE_REGISTRATION( BrokerTest );