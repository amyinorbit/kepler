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
rotation_period(period),
p(0, 0),
r(radius),
mu(mu),
atmo(rho_0, atmo_scale_h, atmo_h)
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
    double radius = (p - at).magnitude();
    return (p - at).normalize((mu) / (radius*radius));
}

vec3 massive_body::up(const vec3& at) const {
    return (at - p).normalize();
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
    double from_axis = (at - p).xy.magnitude();
    double angular_velocity = (2.0*M_PI)/rotation_period;
    return east(at) * from_axis * angular_velocity;
}

massive_body::coordinates massive_body::polar(const vec3 &at, double epoch) const {
    auto ray = at - p;
    
    double longitude = degrees(std::atan2(ray.y, ray.x));
    double latitude = degrees(std::asin(at.z / ray.magnitude()));
    
    if(epoch != 0) {
        double when = epoch / rotation_period;
        double days = 0;
        double fract = std::modf(when, &days) * 360.0;
        longitude -= fract;
        longitude = (longitude < -180.0) ? 360.0 + longitude : longitude;
        longitude = (longitude > 180.0) ? longitude - 360.0 : longitude;
    }
    return coordinates {
        latitude,
        longitude,
        ray.magnitude() - r
    };
}

vec3 massive_body::cartesian(const massive_body::coordinates &at) const {
    double lat = radians(at.latitude);
    double lon = radians(at.longitude);
    double rho = (r + at.altitude);
    return vec3 {
        rho * std::cos(lat) * std::cos(lon),
        rho * std::cos(lat) * std::sin(lon),
        rho * std::sin(lat)
    } + p;
}


double massive_body::altitude(const vec3 &at) const  {
    return (at - p).magnitude() - r;
}

double massive_body::atmo_density(const vec3 &at) const  {
    auto h = altitude(at);
    //if(h > atmo.depth) return 0;
    return atmo.ground_density * std::pow(M_E, -(h/atmo.scale_height));
}