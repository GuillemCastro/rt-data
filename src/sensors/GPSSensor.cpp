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

#include "GPSSensor.h"

void GPSSensor::start() {
    if (gps.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
        throw std::runtime_error("No GPSD running");
    }
    Sensor::start();
    Log::log(INFO) << "[" << name << "] GPS sensor started";
}

void GPSSensor::stop() {
    Sensor::stop();
}

void GPSSensor::read() {
    if (gps.waiting(10)) { // wait for input, timeout = 10 seconds
        gps_data_t* gpsd_data = gps.read();
        if (gpsd_data == NULL) {
            Log::log(WARNING) << "[" << name << "] Received invalid (null) GPS data";
            return; // invalid gps data
        }
        std::shared_ptr<GPSData> gps_data = std::make_shared<GPSData>(gpsd_data);
        gps_data->setOrigin(name);
        queue.push(gps_data);
    }
}

std::string GPSSensor::getHost() const {
    return host;
}

std::string GPSSensor::getPort() const {
    return port;
}

void GPSSensor::setHost(const std::string& host) {
    this->host = host;
}

void GPSSensor::setPort(const std::string& port) {
    this->port = port;
}

Timestamp GPSData::getGPSTime() const {
    return gps_time;
}

GPSStatus GPSData::getGPSStatus() const {
    return status;
}

int GPSData::getSatellitesUsed() const {
    return number_of_satellites_used;
}

int GPSData::getSatellitesVisible() const {
    return number_of_satellites_visible;
}

FixMode GPSData::getFixMode() const {
    return fix_mode;
}

double GPSData::getLongitude() const {
    return longitude;
}

double GPSData::getLatitude() const {
    return latitude;
}

double GPSData::getAltitude() const {
    return altitude;
}

double GPSData::getTrack() const {
    return track;
}

double GPSData::getGroundSpeed() const {
    return ground_speed;
}

double GPSData::getVerticalSpeed() const {
    return vertical_speed;
}

double GPSData::getLatitudeUncertainty() const {
    return latitude_uncertainty;
}

double GPSData::getLongitudeUncertainty() const {
    return longitude_uncertainty;
}

double GPSData::getTrackUncertainty() const {
    return track_uncertainty;
}

double GPSData::getGroundSpeedUncertainty() const {
    return ground_speed_uncertainty;
}

double GPSData::getVerticalSpeedUncertainty() const {
    return vertical_speed_uncertainty;
}

void GPSData::setGPSTime(const Timestamp& time) {
    this->gps_time = time;
}

void GPSData::setStatus(GPSStatus status) {
    this->status = status;
}

void GPSData::setSatellitesUsed(int usedSatellites) {
    this->number_of_satellites_used = usedSatellites;
}

void GPSData::setSatellitesVisible(int visibleSatellites) {
    this->number_of_satellites_visible = visibleSatellites;
}

void GPSData::setFixMode(FixMode fixMode) {
    this->fix_mode = fixMode;
}

void GPSData::setLongitude(double longitude) {
    this->longitude = longitude;
}

void GPSData::setLatitude(double latitude) {
    this->latitude = latitude;
}

void GPSData::setAltitude(double altitude) {
    this->altitude = altitude;
}

void GPSData::setTrack(double track) {
    this->track = track;
}

void GPSData::setGroundSpeed(double groundSpeed) {
    this->ground_speed = groundSpeed;
}

void GPSData::setVerticalSpeed(double verticalSpeed) {
    this->vertical_speed = verticalSpeed;
}

void GPSData::setLatitudeUncertainty(double latitudeUncertainty) {
    this->latitude_uncertainty = latitudeUncertainty;
}

void GPSData::setLongitudeUncertainty(double longitudeUncertainty) {
    this->longitude_uncertainty = longitudeUncertainty;
}

void GPSData::setAltitudeUncertainty(double altitudeUncertainty) {
    this->altitude_uncertainty = altitudeUncertainty;
}

void GPSData::setTrackUncertainty(double trackUncertainty) {
    this->track_uncertainty = trackUncertainty;
}

void GPSData::setGroundSpeedUncertainty(double groundSpeedUncertainty) {
    this->ground_speed_uncertainty = groundSpeedUncertainty;
}

void GPSData::setVerticalSpeedUncertainty(double verticalSpeedUncertainty) {
    this->vertical_speed_uncertainty = verticalSpeedUncertainty;
}

void GPSData::serialize(SerializedObject* object) {
    Data::serialize(object);
    object->put("gps_time", (unsigned int)gps_time.toNanos());
    object->put("status", (int)status);
    object->put("number_of_satellites_used", number_of_satellites_used);
    object->put("number_of_satellites_visible", number_of_satellites_visible);
    object->put("fix_mode", (int)fix_mode);
    object->put("longitude", longitude);
    object->put("latitude", latitude);
    object->put("altitude", altitude);
    object->put("track", track);
    object->put("ground_speed", ground_speed);
    object->put("vertical_speed", vertical_speed);
    object->put("latitude_uncertainty", latitude_uncertainty);
    object->put("longitude_uncertainty", longitude_uncertainty);
    object->put("altitude_uncertainty", altitude_uncertainty);
    object->put("track_uncertainty", track_uncertainty);
    object->put("ground_speed_uncertainty", ground_speed_uncertainty);
    object->put("vertical_speed_uncertainty", vertical_speed_uncertainty);
}

void GPSData::deserialize(SerializedObject* object) {
    Data::deserialize(object);
    gps_time = Timestamp(object->getUInt("gps_time"));
    status = (GPSStatus)object->getInt("status");
    number_of_satellites_used = object->getInt("number_of_satellites_used");
    number_of_satellites_visible = object->getInt("number_of_satellites_visible");
    fix_mode = (FixMode)object->getInt("fix_mode");
    longitude = object->getDouble("longitude");
    latitude = object->getDouble("latitude");
    altitude = object->getDouble("altitude");
    track = object->getDouble("track");
    ground_speed = object->getDouble("ground_speed");
    vertical_speed = object->getDouble("vertical_speed");
    latitude_uncertainty = object->getDouble("latitude_uncertainty");
    longitude_uncertainty = object->getDouble("longitude_uncertainty");
    altitude_uncertainty = object->getDouble("altitude_uncertainty");
    track_uncertainty = object->getDouble("track_uncertainty");
    ground_speed_uncertainty = object->getDouble("ground_speed_uncertainty");
    vertical_speed_uncertainty = object->getDouble("vertical_speed_uncertainty");
}