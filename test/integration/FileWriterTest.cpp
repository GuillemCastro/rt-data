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

#include <io/FileWriter.h>
#include <Data.h>
#include <serialization/JSONObject.h>
#include <serialization/ByteObject.h>


#include <iostream>

int main() {
    std::string origin = "test";
    Timestamp time = Timestamp::now();
    FileWriter<JSONObject> writerJSON("test_json.txt");
    FileWriter<ByteObject> writerByte("test_byte.txt");
    std::shared_ptr<Data> d = std::make_shared<Data>(time, origin);
    writerJSON.write(d);
    writerJSON.write(d);
    writerByte.write(d);
    writerByte.write(d);
}