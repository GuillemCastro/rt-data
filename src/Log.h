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

#ifdef WITH_G3LOG
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <memory>
#include <experimental/source_location>
#include <sstream>
#endif
#include <iostream>

#ifndef WITH_G3LOG
enum Level {
    DEBUG,
    INFO,
    WARNING,
    FATAL
};
#endif

#ifdef WITH_G3LOG
class LogLine {

public:

    LogLine(std::string file, int line, std::string function, LEVELS& level) :
        stream(), file(file), line(line), function(function), level(level) {

    }

    ~LogLine() {
        g3::internal::saveMessage(stream.str().c_str(), file.c_str(), line, function.c_str(), level, "", SIGABRT, nullptr);
    }

    std::ostringstream stream;

private:

    std::string file;
    int line;
    std::string function;
    LEVELS level;

};

template<typename T>
LogLine& operator<<(LogLine& line, T& value) {
    line.stream << std::forward<T>(value);
    return line;
}

template<typename T>
LogLine& operator<<(LogLine& line, T&& value) {
    line.stream << std::forward<T>(value);
    return line;
}

template<typename T>
LogLine& operator<<(LogLine&& line, T&& value) {
    return line << std::forward<T>(value);
}
#endif //WITH_G3LOG

class Log {

public:

    Log() = delete;

    Log(const Log& another) = delete;

    Log& operator=(const Log& another) = delete;

    /**
     * Initialize the logging service
     * @param logPrefix The prefix for the log file (optional, default = "log")
     * @param logFilePath The path for the log files (optional, default = "./")'
     * @param enableConsole Whether the logs should be printed by stdout or not (optional, default = true)
     */
    static void init(const std::string& logPrefix = "log", const std::string& logFilePath = "./", bool enableConsole = true) {
        #ifdef WITH_G3LOG
        auto fileSinkHandle = Log::logWorker->addSink(std::make_unique<g3::FileSink>(logPrefix, logFilePath), &g3::FileSink::fileWrite);
        if (enableConsole) {
            auto consoleSinkHandle = Log::logWorker->addSink(std::make_unique<ConsoleSink>(), &ConsoleSink::ReceiveLogMessage);
        }
        g3::initializeLogging(Log::logWorker.get());
        #endif
    }

    /**
     * Log a message with a printf-like format
     * @param level The level of the log. Possible values = DEBUG, INFO, WARNING, FATAL
     * @param message The message to be written to the log. It can contain printf-like format specifiers that are replaced by the values specified in the additional arguments
     * @param ... (additional arguments) If message contains format specifiers, the function expects additional arguments each containing a value to be used to replace a format specifier 
     */
    #ifdef WITH_G3LOG
    static inline LogLine log(LEVELS level = INFO, std::experimental::source_location loc = std::experimental::source_location::current()) {
        return LogLine(loc.file_name(), loc.line(), loc.function_name(), level);
    }
    #else
    static inline std::ostream& log(Level level) {
        return std::cout;
    }
    #endif // WITH_G3LOG

private:

    #ifdef WITH_G3LOG

    struct ConsoleSink {

        enum FG_Color {YELLOW = 33, RED = 31, GREEN=32, WHITE = 97};

        FG_Color GetColor(const LEVELS level) const {
            if (level.value == WARNING.value) { return YELLOW; }
            if (level.value == DEBUG.value) { return GREEN; }
            if (g3::internal::wasFatal(level)) { return RED; }
            return WHITE;
        }
    
        void ReceiveLogMessage(g3::LogMessageMover logEntry) {
            auto level = logEntry.get()._level;
            auto color = GetColor(level);
            std::cout << "\033[" << color << "m" << logEntry.get().toString() << "\033[m" << std::endl;
        }

    };

    static std::unique_ptr<g3::LogWorker> logWorker;

    #endif // WITH_G3LOG

};
