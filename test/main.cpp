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

#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/CompilerOutputter.h>

#include <Log.h>


int main() {

    Log::init();
    Log::log(INFO, "Test executions started");

    CppUnit::TestResultCollector result;

    std::ofstream xmlout ( "testresults.xml" );
	CppUnit::XmlOutputter xmlOutputter ( &result, xmlout );

    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cerr));
    runner.eventManager().addListener(&result);
    bool wasSuccessful = runner.run();

    xmlOutputter.write();

    Log::log(INFO, "Test executions ended");

    return !wasSuccessful;
}