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

#include "SQLiteWriter.h"

void SQLiteWriter::open() {
    if (rt_optimization) {
        //This way SQLite does not check if the OS has written to disk
        //The commit time is much faster
        db.exec("PRAGMA synchronous = OFF");
        //Set the journal to volatile RAM instead of disk
        //We are saving disk space and some writes to disk
        db.exec("PRAGMA journal_mode = MEMORY");
    }
    is_open = true;
}

void SQLiteWriter::close() {
    //Nothing to do :/
    //The database is closed when the destructor of SQLite::Database is called
    is_open = false;
}

void SQLiteWriter::write(std::shared_ptr<Data> data) {
    write("default", data);
}

void SQLiteWriter::write(std::string topic, std::shared_ptr<Data> data) {
    if (!is_open) {
        throw std::runtime_error("Writer is not open");
    }
    std::unique_lock<std::mutex> lck(mtx);
    //The table name is a combination of the topic and the origin of the data
    //An origin is not expected to send different types of data to the same topic
    std::ostringstream table_stream;
    table_stream << topic << "_" << data->getOrigin();
    std::string table = table_stream.str();
    SQLiteObject object(table);
    data->serialize(&object);
    buffer.push_back(object);
    if (!db.tableExists(table)) {
        db.exec(object.getCreateTable());
    }
    if (prepared_statements.find(table) == prepared_statements.end()) {
        prepared_statements.emplace(table, SQLite::Statement(db, object.getInsert()));
    }
    if (buffer.size() > buffer_size) {
        lck.unlock(); //Avoid deadlock
        flush();
    }
}

void SQLiteWriter::flush() {
    std::unique_lock<std::mutex> lck(mtx);
    std::string table;
    SQLite::Transaction transaction(db);
    for (auto& object : buffer) {
        table = object.getTable();
        object.bindValues(prepared_statements.at(table));
        prepared_statements.at(table).exec();
        prepared_statements.at(table).reset();
    }
    transaction.commit();
    buffer.clear();
}

bool SQLiteWriter::isOpen() {
    return is_open;
}

bool SQLiteWriter::isClosed() {
    return !is_open;
}