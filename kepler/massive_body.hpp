//
//  planet.hpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once
#include <string>
#include "vec.hpp"


/// Defines the way planets are represented in the integrator/universe
/// Atmospheres are, so far, modeled using the basic
struct massive_body final {
    
    massive_body(const std::string& name,
                 double radius,
                 double mu,
                 double rho_0,
                 double atmo_scale_h,
                 double atmo_h);
    
    massive_body(const std::string& json_file);
    
    ~massive_body();
    
    
    // Local gravity force exerted by the body.
    vec3 gravity(const vec3& at) const;
    
    /// Local vertical relative to the body.
    vec3 up(const vec3& at) const;
    
    /// Altitude relative to the body.
    double altitude(const vec3& at) const;
    
    /// Atmospheric density at the current position.
    double atmo_density(const vec3& at) const;
    
private:
    
    std::string name;
    
    double rotation_period_;
    
    vec3 position_;
    
    double radius_;
    
    double mu_;
    
    struct {
        double groundDensity;
        double scaleHeight;
        double depth;
    } atmo_;
    
};