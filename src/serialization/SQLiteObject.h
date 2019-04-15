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

#pragma once

#include "SerializedObject.h"
#include "../utils/Any.h"

#include <SQLiteCpp/Statement.h>

#include <vector>
#include <stdint.h>
#include <stdexcept>
#include <sstream>
#include <map>
#include <unordered_map>

class SQLiteObject : public SerializedObject {

public:

    SQLiteObject() : SerializedObject(), table("default") {

    }

    explicit SQLiteObject(std::string table) : SerializedObject(), table(table) {

    }

    /**
     * 'Put' methods to serialize objects
     * @param key The preferred key for the value to be serialized.
     * @param value The value to be serialized.
     */

    virtual void put(const std::string& key, int value) {
        _put(key, value, Type::INT);
    }

    virtual void put(const std::string& key, unsigned int value) {
        _put(key, value, Type::UINT);
    }

    virtual void put(const std::string& key, float value) {
        _put(key, value, Type::FLOAT);
    }

    virtual void put(const std::string& key, double value) {
        _put(key, value, Type::DOUBLE);
    }

    virtual void put(const std::string& key, bool value) {
        _put(key, value, Type::BOOL);
    }

    virtual void put(const std::string& key, std::string value) {
        std::string escaped_value = "\"" + value + "\"";
        _put(key, escaped_value, Type::STRING);
    }

    /**
     * 'Get' methods to deserialize objects
     * @param key The key of the value to be deserialized. This parameter is ignored.
     * @returns The deserialized value.
     */

    virtual int getInt(const std::string& key) {
        return contents[key]->get<int>();
    }

    virtual unsigned int getUInt(const std::string& key) {
        return contents[key]->get<unsigned int>();
    }

    virtual float getFloat(const std::string& key) {
        return contents[key]->get<float>();
    }

    virtual double getDouble(const std::string& key) {
        return contents[key]->get<double>();
    }

    virtual bool getBool(const std::string& key) {
        return contents[key]->get<bool>();
    }

    virtual std::string getString(const std::string& key) {
        std::string content = contents[key]->get<std::string>();
        if (content[0] == '\"' && content[ content.size() -1 ] == '\"') {
            content.erase( content.begin() );
            content.erase( content.end() - 1 );
        }
        return content;
    }

    /**
     * Get the prepared statement for inserting data
     * @returns A SQL prepared statement that can be used to insert data from the serialized class 
     */
    std::string getInsert() {
        std::ostringstream insert;
        bool first = true;
        insert << "INSERT INTO " << table << " (";
        for (auto& column : contents) {
            if (!first) {
                insert << ", ";
            }
            else {
                first = false;
            }
            insert << column.first;
        }
        insert << ") VALUES (";
        first = true;
        for (auto& column : contents) {
            if (!first) {
                insert << ", ";
            }
            else {
                first = false;
            }
            insert << ':' << column.first;
        }
        insert << ");";
        return insert.str();
    }

    /**
     * Get the statement that can be used to create a table for the serialized class
     * @returns The create statement for the table representing the original serialized class
     */
    std::string getCreateTable() {
        std::ostringstream create_table;
        bool first = true;
        create_table << "CREATE TABLE " << table << " (";
        for (auto& column : contents) {
            if (!first) {
                create_table << ", ";
            }
            else {
                first = false;
            }
            create_table << column.first;
        }
        create_table << ");";
        return create_table.str();
    }

    /**
     * Get the table name
     * @returns The table name
     */
    std::string getTable() {
        return table;
    }

    /**
     * Bind the values of this serialized object to a prepared statement
     * @params insert The statement where the values have to be bind to.
     */
    void bindValues(SQLite::Statement& insert) {
        for (auto& column : contents) {
            bind_column(insert, column.first);
        }
    }

private:

    enum Type {
        INT, UINT, FLOAT, DOUBLE, BOOL, STRING
    };

    template <typename T>
    void _put(std::string key, const T& value, Type type) {
        contents[key] = Any::create_any(value);
        types[key] = type;
    }

    void bind_column(SQLite::Statement& insert, std::string column) {
        std::string bind_column_name = ":" + column;
        switch (types[column]) {
            case INT:
                insert.bind(bind_column_name, contents[column]->get<int>());
                break;
            case UINT:
                insert.bind(bind_column_name, contents[column]->get<unsigned int>());
                break;
            case FLOAT:
                insert.bind(bind_column_name, contents[column]->get<float>());
                break;
            case DOUBLE:
                insert.bind(bind_column_name, contents[column]->get<double>());
                break;
            case BOOL:
                insert.bind(bind_column_name, contents[column]->get<bool>());
                break;
            case STRING:
                insert.bind(bind_column_name, contents[column]->get<std::string>());
                break;
        }
    }

    std::string table;

    std::map<std::string, std::shared_ptr<Any>> contents;

    std::unordered_map<std::string, Type> types;

};