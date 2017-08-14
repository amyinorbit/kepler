//
//  planet.hpp
//  kepler
//
//  Created by Amy Parent on 04/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include <string>
#include "vec.hpp"

/// Defines the way planets are represented in the integrator/universe
/// Atmospheres are, so far, modeled using the basic
struct MassiveBody final {
    
    struct coordinates {
        double latitude;
        double longitude;
        double altitude;
    };
    
    MassiveBody(const std::string& name,
                 double period,
                 double radius,
                 double mu,
                 double rho_0,
                 double atmo_scale_h,
                 double atmo_h);
    
    
    MassiveBody(const std::string& json_file);
    
    ~MassiveBody() {}
    
    // Get Lat/Lon/Alt from cartesian coordinates.
    coordinates polar(const vec3& at, double epoch = 0) const;
    
    // Get cartesian coordinates based on Lat/Lon/Alt
    vec3 cartesian(const coordinates& at) const;
    
    // Returns the surface velocity
    vec3 inertialVelocity(const vec3& at) const;
    
    // Local gravity force exerted by the body.
    vec3 gravity(const vec3& at) const;
    
    /// Local vertical relative to the body.
    vec3 up(const vec3& at) const;
    
    vec3 north(const vec3& at) const;
    
    vec3 east(const vec3& at) const;
    
    vec3 heading(const vec3& at, double heading, double pitch) const;
    
    /// Altitude relative to the body.
    double altitude(const vec3& at) const;
    
    /// Atmospheric density at the current position.
    double atmo_density(const vec3& at) const;
    
    double gravitationalParameter() const { return _gravitationalParameter; }
    
    double radius() const { return _radius; }
    
    vec3 position() const { return _position; }
    
private:
    
    std::string name;
    double      _rotationPeriod;
    vec3        _position;
    double      _radius;
    double      _gravitationalParameter;
    struct      Atmosphere {
        Atmosphere(double d0 = 0, double sh = 0, double d = 0) :
            groundDensity(d0),
            scaleHeight(sh),
            depth(d){}
        double groundDensity;
        double scaleHeight;
        double depth;
    }           _atomsphere;
    
};

