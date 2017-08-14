//
//  planet.cpp
//  kepler
//
//  Created by Amy Parent on 04/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "MassiveBody.hpp"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

using json_t = nlohmann::json;

MassiveBody::MassiveBody(const std::string& name,
                           double period,
                           double radius,
                           double mu,
                           double rho_0,
                           double atmo_scale_h,
                           double atmo_h) :
name(name),
_rotationPeriod(period),
_position(0, 0),
_radius(radius),
_gravitationalParameter(mu),
_atomsphere(rho_0, atmo_scale_h, atmo_h)
{
    
}

MassiveBody::MassiveBody(const std::string& json_file) {
    std::fstream raw{json_file};
    if(raw.is_open()) { throw std::runtime_error{""}; }
    json_t json;
    raw >> json;
    std::cout << json;
}


vec3 MassiveBody::gravity(const vec3& at) const {
    double radius = (_position - at).magnitude();
    return (_position - at).normalize((_gravitationalParameter) / (radius*radius));
}

vec3 MassiveBody::up(const vec3& at) const {
    return (at - _position).normalize();
}

vec3 MassiveBody::north(const vec3 &at) const {
    return vec3::cross(up(at), east(at)).normalize();
}

vec3 MassiveBody::east(const vec3 &at) const {
    return vec3::cross(vec3{0, 0, 1}, up(at)).normalize();
}

vec3 MassiveBody::heading(const vec3& at, double heading, double pitch) const {
    return north(at).rotate(east(at), radians(pitch)).rotate(up(at), -radians(heading));
}

vec3 MassiveBody::inertialVelocity(const vec3& at) const {
    double from_axis = (at - _position).xy.magnitude();
    double angular_velocity = (2.0*M_PI)/_rotationPeriod;
    return east(at) * from_axis * angular_velocity;
}

MassiveBody::coordinates MassiveBody::polar(const vec3 &at, double epoch) const {
    auto ray = at - _position;
    
    double longitude = degrees(std::atan2(ray.y, ray.x));
    double latitude = degrees(std::asin(at.z / ray.magnitude()));
    
    if(epoch != 0) {
        double when = epoch / _rotationPeriod;
        double days = 0;
        double fract = std::modf(when, &days) * 360.0;
        longitude -= fract;
        longitude = (longitude < -180.0) ? 360.0 + longitude : longitude;
        longitude = (longitude > 180.0) ? longitude - 360.0 : longitude;
    }
    return coordinates {
        latitude,
        longitude,
        ray.magnitude() - _radius
    };
}

vec3 MassiveBody::cartesian(const MassiveBody::coordinates &at) const {
    double lat = radians(at.latitude);
    double lon = radians(at.longitude);
    double rho = (_radius + at.altitude);
    return vec3 {
        rho * std::cos(lat) * std::cos(lon),
        rho * std::cos(lat) * std::sin(lon),
        rho * std::sin(lat)
    } + _position;
}


double MassiveBody::altitude(const vec3 &at) const  {
    return (at - _position).magnitude() - _radius;
}

double MassiveBody::atmo_density(const vec3 &at) const  {
    auto h = altitude(at);
    //if(h > atmo.depth) return 0;
    return _atomsphere.groundDensity * std::pow(M_E, -(h/_atomsphere.scaleHeight));
}
