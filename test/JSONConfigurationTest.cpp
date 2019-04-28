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

#include <limits>
#include <algorithm>
#include <cmath>

#include "JSONConfigurationTest.h"

void JSONConfigurationTest::getBoolTest() {
    bool test = config["bool_true"]->get<bool>();
    CPPUNIT_ASSERT(test);
}

void JSONConfigurationTest::getStringTest() {
    std::string test = config["string_test"]->get<std::string>();
    CPPUNIT_ASSERT(test == std::string("test"));
}

void JSONConfigurationTest::getFloatTest() {
    double test = config["float_three"]->get<double>();
    // https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
    bool almost_equal = std::abs(test - 3.0) <= std::numeric_limits<double>::epsilon() * std::abs(test + 3.0) * 2 || std::abs(test - 3.0) < std::numeric_limits<double>::min();
    CPPUNIT_ASSERT(almost_equal);
}

void JSONConfigurationTest::getIntTest() {
    int64_t test = config["int_minus_three"]->get<int64_t>();
    CPPUNIT_ASSERT(test == -3);
}

void JSONConfigurationTest::getUIntTest() {
    uint64_t test = config["uint_three"]->get<uint64_t>();
    CPPUNIT_ASSERT(test == 3);
}

void JSONConfigurationTest::getArrayTest() {
    std::vector<int64_t> test = config["array"]->get<std::vector<int64_t>>();
    CPPUNIT_ASSERT(test[0] == 3);
    CPPUNIT_ASSERT(test[1] == 4);
}

void JSONConfigurationTest::getNestedConfig() {
    int64_t test = config["object"]->at("int_three")->get<int64_t>();
    CPPUNIT_ASSERT(test == 3);
}

void JSONConfigurationTest::setInt() {
    config["object"]->at("int_three")->set((int64_t)5);
    int64_t test = config["object"]->at("int_three")->get<int64_t>();
    CPPUNIT_ASSERT(test == 5);
}