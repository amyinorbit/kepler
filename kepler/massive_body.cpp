//
//  planet.cpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#include "massive_body.hpp"
#include "json.hpp"
#include <fstream>
#include <stdexcept>

using json_t = nlohmann::json;

massive_body::massive_body(const std::string& name,
                           double period,
                           double radius,
                           double mu,
                           double rho_0,
                           double atmo_scale_h,
                           double atmo_h) :
name(name),
rotation_period_(period),
position_(0, 0),
radius_(radius),
μ(mu),
atmo_(rho_0, atmo_scale_h, atmo_h)
{
    
}

massive_body::massive_body(const std::string& json_file) {
    std::fstream raw{json_file};
    if(raw.is_open()) { throw std::runtime_error{""}; }
    json_t json;
    raw >> json;
    std::cout << json;
}


vec3 massive_body::gravity(const vec3& at) const {
    double r = (position_ - at).magnitude();
    return (position_ - at).normalize((μ) / (r*r));
}

vec3 massive_body::up(const vec3& at) const {
    return (at - position_).normalize();
}

vec3 massive_body::north(const vec3 &at) const {
    return vec3::cross(up(at), east(at)).normalize();
}

vec3 massive_body::east(const vec3 &at) const {
    return vec3::cross(vec3{0, 0, 1}, up(at)).normalize();
}

vec3 massive_body::heading(const vec3& at, double heading, double pitch) const {
    return north(at).rotate(east(at), radians(pitch)).rotate(up(at), -radians(heading));
}

vec3 massive_body::inertial_velocity(const vec3& at) const {
    double from_axis = (at - position_).xy.magnitude();
    double angular_velocity = (2.0*M_PI)/rotation_period_;
    return east(at) * from_axis * angular_velocity;
}

massive_body::coordinates massive_body::polar(const vec3 &at, double epoch) const {
    auto ray = at - position_;
    
    double longitude = degrees(std::atan2(ray.y, ray.x));
    double latitude = degrees(std::asin(at.z / ray.magnitude()));
    
    if(epoch != 0) {
        double when = epoch / rotation_period_;
        double days = 0;
        double fract = std::modf(when, &days) * 360.0;
        longitude -= fract;
        longitude = (longitude < 0) ? 360.0 + longitude : longitude;
    }
    return coordinates {
        latitude,
        longitude,
        ray.magnitude() - radius_
    };
}

vec3 massive_body::cartesian(const massive_body::coordinates &at) const {
    double lat = radians(at.latitude);
    double lon = radians(at.longitude);
    double radius = (radius_ + at.altitude);
    return vec3 {
        radius * std::cos(lat) * std::cos(lon),
        radius * std::cos(lat) * std::sin(lon),
        radius * std::sin(lat)
    } + position_;
}


double massive_body::altitude(const vec3 &at) const  {
    return (at - position_).magnitude() - radius_;
}

double massive_body::atmo_density(const vec3 &at) const  {
    auto h = altitude(at);
    if(h > atmo_.depth) return 0;
    return atmo_.groundDensity * std::pow(M_E, -(h/atmo_.scaleHeight));
}