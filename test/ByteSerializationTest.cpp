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

#include "ByteSerializationTest.h"

void ByteSerializationTest::dataSerializationTest() {
    Timestamp epoch = Timestamp::epoch;
    Data d;
    Serializer s;
    std::string origin("test");
    d.setTimestamp(epoch);
    d.setOrigin(origin);
    ByteObject byteSerialized = s.serialize<ByteObject>(d);
    Data d2;
    d2.deserialize(&byteSerialized);
    CPPUNIT_ASSERT(epoch == d2.getTimestamp());
    CPPUNIT_ASSERT(origin == d2.getOrigin());
}