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
        gps_data->set_origin(name);
        queue.push(gps_data);
    }
}

std::string GPSSensor::get_host() const {
    return host;
}

std::string GPSSensor::get_port() const {
    return port;
}

void GPSSensor::set_host(const std::string& host) {
    this->host = host;
}

void GPSSensor::set_port(const std::string& port) {
    this->port = port;
}

Timestamp GPSData::get_GPS_time() const {
    return gps_time;
}

GPSStatus GPSData::get_GPS_status() const {
    return status;
}

int GPSData::get_satellites_used() const {
    return number_of_satellites_used;
}

int GPSData::get_satellites_visible() const {
    return number_of_satellites_visible;
}

FixMode GPSData::get_fix_mode() const {
    return fix_mode;
}

double GPSData::get_longitude() const {
    return longitude;
}

double GPSData::get_latitude() const {
    return latitude;
}

double GPSData::get_altitude() const {
    return altitude;
}

double GPSData::get_track() const {
    return track;
}

double GPSData::get_ground_speed() const {
    return ground_speed;
}

double GPSData::get_vertical_speed() const {
    return vertical_speed;
}

double GPSData::get_latitude_uncertainty() const {
    return latitude_uncertainty;
}

double GPSData::get_longitude_uncertainty() const {
    return longitude_uncertainty;
}

double GPSData::get_track_uncertainty() const {
    return track_uncertainty;
}

double GPSData::get_ground_speed_uncertainty() const {
    return ground_speed_uncertainty;
}

double GPSData::get_vertical_speed_uncertainty() const {
    return vertical_speed_uncertainty;
}

void GPSData::set_GPS_time(const Timestamp& time) {
    this->gps_time = time;
}

void GPSData::set_GPS_status(GPSStatus status) {
    this->status = status;
}

void GPSData::set_satellites_used(int usedSatellites) {
    this->number_of_satellites_used = usedSatellites;
}

void GPSData::set_satellites_visible(int visibleSatellites) {
    this->number_of_satellites_visible = visibleSatellites;
}

void GPSData::set_fix_mode(FixMode fixMode) {
    this->fix_mode = fixMode;
}

void GPSData::set_longitude(double longitude) {
    this->longitude = longitude;
}

void GPSData::set_latitude(double latitude) {
    this->latitude = latitude;
}

void GPSData::set_altitude(double altitude) {
    this->altitude = altitude;
}

void GPSData::set_track(double track) {
    this->track = track;
}

void GPSData::set_ground_speed(double groundSpeed) {
    this->ground_speed = groundSpeed;
}

void GPSData::set_vertical_speed(double verticalSpeed) {
    this->vertical_speed = verticalSpeed;
}

void GPSData::set_latitude_uncertainty(double latitudeUncertainty) {
    this->latitude_uncertainty = latitudeUncertainty;
}

void GPSData::set_longitude_uncertainty(double longitudeUncertainty) {
    this->longitude_uncertainty = longitudeUncertainty;
}

void GPSData::set_altitude_uncertainty(double altitudeUncertainty) {
    this->altitude_uncertainty = altitudeUncertainty;
}

void GPSData::set_track_uncertainty(double trackUncertainty) {
    this->track_uncertainty = trackUncertainty;
}

void GPSData::set_ground_speed_uncertainty(double groundSpeedUncertainty) {
    this->ground_speed_uncertainty = groundSpeedUncertainty;
}

void GPSData::set_vertical_speed_uncertainty(double verticalSpeedUncertainty) {
    this->vertical_speed_uncertainty = verticalSpeedUncertainty;
}

void GPSData::serialize(SerializedObject* object) {
    Data::serialize(object);
    object->put("gps_time", (unsigned int)gps_time.to_nanos());
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
    gps_time = Timestamp(object->get_uint("gps_time"));
    status = (GPSStatus)object->get_int("status");
    number_of_satellites_used = object->get_int("number_of_satellites_used");
    number_of_satellites_visible = object->get_int("number_of_satellites_visible");
    fix_mode = (FixMode)object->get_int("fix_mode");
    longitude = object->get_double("longitude");
    latitude = object->get_double("latitude");
    altitude = object->get_double("altitude");
    track = object->get_double("track");
    ground_speed = object->get_double("ground_speed");
    vertical_speed = object->get_double("vertical_speed");
    latitude_uncertainty = object->get_double("latitude_uncertainty");
    longitude_uncertainty = object->get_double("longitude_uncertainty");
    altitude_uncertainty = object->get_double("altitude_uncertainty");
    track_uncertainty = object->get_double("track_uncertainty");
    ground_speed_uncertainty = object->get_double("ground_speed_uncertainty");
    vertical_speed_uncertainty = object->get_double("vertical_speed_uncertainty");
}