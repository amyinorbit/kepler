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
    
    double semiMajorAxis() const { return _sma; }
    
    double periapsis() const { return _periapsis; }
    
    double apoapsis() const { return _apoapsis; }
    
    double eccentricity() const { return _eccentricity; }
    
    double inclination() const { return _inclination; }
    
    double argOfPeriapsis() const { return _argOfPeriapsis; }
    
    double raan() const { return _raan; }
    
    double trueAnomaly() const { return _anomaly; }
    
private:
    
    double _sma;
    double _periapsis;
    double _apoapsis;
    double _eccentricity;
    double _inclination;
    double _argOfPeriapsis;
    double _raan;
    double _anomaly;
    
};

