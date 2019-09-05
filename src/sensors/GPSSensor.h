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

#include "../Sensor.h"
#include "../Log.h"

#include <libgpsmm.h> 

// Forward declaration
class GPSData;

/**
 * GPS sensor
 * Can read from a GPS sensor connected to a TTY port
 * and managed by a gpsd daemon.
 */
class GPSSensor : public Sensor {

public:

    /**
     * Default constructor
     */
    GPSSensor() : Sensor(), host("localhost"), port(DEFAULT_GPSD_PORT), gps(host.c_str(), port.c_str()) {

    }

    /**
     * Constructor with all configurable parameters
     * @param name Name of the sensor. Used to identify it.
     * @param topic The topic where this sensor will publish its data to
     * @param rate The rate in nanoseconds at which the sensor will be read
     * @param host The hostname of the host where the gpsd daemon is running. By default "localhost"
     * @param port The port that gpsd is listening to. By default DEFAULT_GPSD_PORT
     */
    GPSSensor(const std::string& name, const std::string& topic, 
        uint64_t rate, const std::string& host="localhost", const std::string& port=DEFAULT_GPSD_PORT) : Sensor(name, topic, rate), host(host), port(port), gps(host.c_str(), port.c_str()) {

    }
    
    /**
     * Constructor with a Configuration object
     * @param config The node containing the configuration for this sensor
     */
    explicit GPSSensor(Configuration& config) : Sensor(config), 
        host(config["host"].get<std::string>()), port(config["port"].get<std::string>()), gps(host.c_str(), port.c_str()) {

    }

    /**
     * Starts the sensor.
     * @throws std::runtime_error if the sensor has been already started or if it was stopped.
     * @throws std::runtime_error if the gpsd daemon is not running
     */
    virtual void start() override;

    /**
     * Stops the sensor.
     * @throws std::runtime_error if the sensor has been already stopped or if it was never started.
     */
    virtual void stop() override;

    /**
     * Get the hostname of the GPSD daemon
     * @returns The hostname of the GPSD daemon
     */
    std::string get_host() const;

    /**
     * Get the port of the GPSD daemon
     * @returns The port of the GPSD daemon
     */
    std::string get_port() const;

    /**
     * Set the hostname of the GPSD daemon
     * @param host The hostname of the GPSD daemon
     */
    void set_host(const std::string& host);

    /**
     * Set the port of the GPSD daemon
     * @param The port of the GPSD daemon
     */
    void set_port(const std::string& port);

protected:

    /**
     * Internal read method
     */
    virtual void read();

private:

    std::string host;

    std::string port;

    gpsmm gps;

};

enum GPSStatus {
    NOFIX = 0, // no fix
    FIX, // fix without DGPS
    DGPS_FIX // fix with DGPS
};

enum FixMode {
    NOT_SEEN = 0, 
    NO_FIX,
    FIX_2D,
    FIX_3D
};

class GPSData : public Data {

public:

    /**
     * Default constructor
     */
    GPSData() : Data() {

    }

    explicit GPSData(gps_data_t* gps_data) :
        gps_time(Timestamp((uint64_t)(gps_data->fix.time * 1000000000.0))),
        status((GPSStatus)gps_data->status),
        number_of_satellites_used(gps_data->satellites_used),
        number_of_satellites_visible(gps_data->satellites_visible),
        fix_mode((FixMode)gps_data->fix.mode),
        longitude(gps_data->fix.longitude),
        latitude(gps_data->fix.latitude),
        altitude(gps_data->fix.altitude),
        track(gps_data->fix.track),
        ground_speed(gps_data->fix.speed),
        vertical_speed(gps_data->fix.climb),
        latitude_uncertainty(gps_data->fix.epy),
        longitude_uncertainty(gps_data->fix.epx),
        altitude_uncertainty(gps_data->fix.epv),
        track_uncertainty(gps_data->fix.epd),
        ground_speed_uncertainty(gps_data->fix.eps),
        vertical_speed_uncertainty(gps_data->fix.epc) {
    
    }

    Timestamp get_GPS_time() const;

    GPSStatus get_GPS_status() const;

    int get_satellites_used() const;

    int get_satellites_visible() const;

    FixMode get_fix_mode() const;

    double get_longitude() const;

    double get_latitude() const;

    double get_altitude() const;

    double get_track() const;

    double get_ground_speed() const;

    double get_vertical_speed() const;

    double get_latitude_uncertainty() const;

    double get_longitude_uncertainty() const;

    double get_track_uncertainty() const;

    double get_ground_speed_uncertainty() const;

    double get_vertical_speed_uncertainty() const;

    void set_GPS_time(const Timestamp& time);

    void set_GPS_status(GPSStatus status);

    void set_satellites_used(int usedSatellites);

    void set_satellites_visible(int visibleSatellites);

    void set_fix_mode(FixMode fixMode);

    void set_longitude(double longitude);

    void set_latitude(double latitude);

    void set_altitude(double altitude);

    void set_track(double track);

    void set_ground_speed(double groundSpeed);

    void set_vertical_speed(double verticalSpeed);

    void set_latitude_uncertainty(double latitudeUncertainty);

    void set_longitude_uncertainty(double longitudeUncertainty);

    void set_altitude_uncertainty(double altitudeUncertainty);

    void set_track_uncertainty(double trackUncertainty);

    void set_ground_speed_uncertainty(double groundSpeedUncertainty);

    void set_vertical_speed_uncertainty(double verticalSpeedUncertainty);

    /**
     * Serialize the AnalogData. Do not call directly.
     * @param object The resulting SerializedObject where the data must be saved.
     */
    virtual void serialize(SerializedObject* object) override;

    /**
     * Deserialize the AnalogData. Do not call directly.
     * @param object The SerializedObject to load the data from.
     */
    virtual void deserialize(SerializedObject* object) override;

private:

    Timestamp gps_time;

    GPSStatus status;
    int number_of_satellites_used;
    int number_of_satellites_visible;

    FixMode fix_mode;

    double longitude, latitude; // degrees
    double altitude; // meters
    double track; // Course made good (relative to true north)
    double ground_speed; // Speed over ground, in m/s
    double vertical_speed; // Vertical speed (aka climb) in m/s

    /** Uncertainty values with 95% confidence **/ 

    double latitude_uncertainty; // in meters
    double longitude_uncertainty; // in meters
    double altitude_uncertainty; // in meters
    double track_uncertainty; // in degrees
    double ground_speed_uncertainty; // in m/s
    double vertical_speed_uncertainty; // in m/s

};