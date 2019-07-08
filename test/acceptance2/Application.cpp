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

#include <rtdata/Application.h>
#include <rtdata/sensors/GPSSensor.h>
#include <rtdata/io/SQLiteWriter.h>
#include <rtdata/io/HTTPWriter.h>
#include <rtdata/io/TCPWriter.h>
#include <rtdata/utils/JSONConfiguration.h>
#include <rtdata/utils/LambdaListener.h>
#include <rtdata/Log.h>

HTTPWriter httpWriter("http://localhost:5000");
TCPWriter tcpWriter("127.0.0.1", 5005);

void Application::setup() {
    Log::init();
    Log::logMessage(INFO, "Acceptance test config started");
    httpWriter.open();
    tcpWriter.open();
    JSONConfiguration config(std::string("config.json"));
    std::shared_ptr<Sensor> sensor = std::make_shared<GPSSensor>(config["sensors"]["gps"]);
    manager.addSensor(sensor);
    broker.subscribe("test", std::make_shared<LambdaListener>([](std::string topic, std::shared_ptr<Data> data) {
        std::shared_ptr<GPSData> analog_data = std::static_pointer_cast<GPSData>(data);
        Log::logMessage(DEBUG, "Received data with latitude %f", analog_data->getLatitude());
        Log::logMessage(DEBUG, "Received data with longitude %f", analog_data->getLongitude());
        Log::logMessage(DEBUG, "Received data with altitude %f", analog_data->getAltitude());
        Log::logMessage(DEBUG, "Received data with origin %s", data->getOrigin().c_str());
        httpWriter.write(topic, data);
        tcpWriter.write(topic, data);
    }));
    broker.start();
    manager.start();
    Log::logMessage(INFO, "Acceptance test config ended");
}

void Application::loop() {

}