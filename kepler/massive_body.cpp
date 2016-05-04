//
//  planet.cpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#include "massive_body.hpp"

vec3 massive_body::gravity(const vec3& at) const {
    double r = (position_ - at).magnitude();
    return (position_ - at).normalize((mu_) / (r*r));
}


/// Local vertical relative to the planet.
vec3 massive_body::up(const vec3& at) const {
    return (at - position_).normalize();
}


double massive_body::altitude(const vec3 &at) const  {
    return (at - position_).magnitude() - radius_;
}

double massive_body::atmo_density(const vec3 &at) const  {
    auto h = altitude(at);
    if(h > atmo_.depth) return vec3{};
    return atmo_.groundDensity * std::pow(M_E, -(h/atmo_.scaleHeight));
}