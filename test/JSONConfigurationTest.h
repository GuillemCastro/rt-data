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

#include "utils/JSONConfiguration.h"

class JSONConfigurationTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(JSONConfigurationTest);
    CPPUNIT_TEST(getBoolTest);
    CPPUNIT_TEST(getStringTest);
    CPPUNIT_TEST(getFloatTest);
    CPPUNIT_TEST(getIntTest);
    CPPUNIT_TEST(getUIntTest);
    CPPUNIT_TEST(getArrayTest);
    CPPUNIT_TEST(getNestedConfig);
    CPPUNIT_TEST(setInt);
    CPPUNIT_TEST_SUITE_END();

public:

    void setUp() {
        uint64_t three = 3;
        file = {
            {"bool_true", true},
            {"string_test", "test"},
            {"float_three", 3.0},
            {"int_minus_three", -3},
            {"uint_three", (uint64_t)three},
            {"array", {3,4,5,6}},
            {"object", {
                {"int_three", 3}
            }}
        };
        config = JSONConfiguration(file);
    }

    void tearDown() {
        
    }

    void getBoolTest();

    void getStringTest();

    void getFloatTest();

    void getIntTest();

    void getUIntTest();

    void getArrayTest();

    void getNestedConfig();

    void setInt();

private:

    nlohmann::json file;
    JSONConfiguration config;

};

CPPUNIT_TEST_SUITE_REGISTRATION( JSONConfigurationTest );