//
//  orbit.hpp
//  kepler
//
//  Created by Cesar Parent on 05/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once
#include "vec.hpp"

class massive_body;

struct orbit final {
    
    orbit(const massive_body& planet, const vec3& position, const vec3& velocity);
    
    orbit(const massive_body& planet,
          double a,
          double e,
          double i,
          double arg_p,
          double raan,
          double v);
    
    ~orbit() {}
    
    double semi_major_axis() const { return sma; }
    
    double periapsis() const { return pe; }
    
    double apoapsis() const { return ap; }
    
    double eccentricity() const { return e; }
    
    double inclination() const { return i; }
    
    double perigee_argument() const { return arg_pea; }
    
    double RAAN() const { return raan; }
    
    double true_anomaly() const { return anomaly; }
    
private:
    
    double sma;
    double pe;
    double ap;
    double e;
    double i;
    double arg_pea;
    double raan;
    double anomaly;
    
};

