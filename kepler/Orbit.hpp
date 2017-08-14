//
//  Orbit.hpp
//  kepler
//
//  Created by Amy Parent on 05/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include "vec.hpp"

class MassiveBody;

struct Orbit final {
    
    Orbit(const MassiveBody& planet, const vec3& position, const vec3& velocity);
    
    Orbit(const MassiveBody& planet,
          double a,
          double e,
          double i,
          double arg_p,
          double raan,
          double v);
    
    ~Orbit() {}
    
    double semiMajorAxis() const { return sma; }
    
    double periapsis() const { return pe; }
    
    double apoapsis() const { return ap; }
    
    double eccentricity() const { return e; }
    
    double inclination() const { return i; }
    
    double argOfPeriapsis() const { return arg_pea; }
    
    double raan() const { return raan; }
    
    double trueAnomaly() const { return anomaly; }
    
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

