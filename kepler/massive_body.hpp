//
//  planet.hpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once
#include "vec.hpp"


/// Defines the way planets are represented in the integrator/universe
/// Atmospheres are, so far, modeled using the basic
struct massive_body final {
    
    massive_body(double radius, double mass, double rho0, double scaleH);
    
    massive_body();
    
    
    vec3 gravity(const vec3& at) const {
        double r = (position_ - at).magnitude();
        return (position_ - at).normalize((mu_) / (r*r));
    }
    
    
    /// Local vertical relative to the planet.
    vec3 up(const vec3& at) const {
        return (at - position_).normalize();
    }
    
    /// Altitude relative to the body.
    double altitude(const vec3& at) const {
        return (at - position_).magnitude() - radius_;
    }
    
    /// Atmospheric density at the current position.
    double atmo_density(const vec3& at) const {
        auto h = altitude(at);
        return atmo_.groundDensity * std::pow(M_E, -(h/atmo_.scaleHeight));
    }
    
private:
    
    vec3 position_;
    
    double radius_;
    
    double mu_;
    
    struct {
        double groundDensity;
        double scaleHeight;
    } atmo_;
    
};