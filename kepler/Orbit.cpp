//
//  Orbit.cpp
//  kepler
//
//  Created by Amy Parent on 05/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "Orbit.hpp"
#include "MassiveBody.hpp"

Orbit::Orbit(const MassiveBody& planet, const vec3& pos, const vec3& v) {
    // Elements calculation from
    // https://downloads.rene-schwarz.com/download/M002-Cartesian_State_Vectors_to_Keplerian_Orbit_Elements.pdf
    vec3 r = pos - planet.position();
    vec3 h = vec3::cross(r, v);
    vec3 n = vec3{-h.y, h.x, 0};
    double mu = planet.gravitationalParameter();
    double v2 = std::pow(v.magnitude(), 2);
    auto e_vec = (vec3::cross(v, h)/mu)-r.normalize();
    _eccentricity = e_vec.magnitude();
    if(_eccentricity != 1) {
        _sma = 1 / ((2/r.magnitude()) - (v2/mu));
        _periapsis = _sma * (1 - _eccentricity);
        _apoapsis = _sma * (1 + _eccentricity);
    } else {
        _periapsis = std::pow(h.magnitude(), 2)/mu;
        _apoapsis = INFINITY;
        _sma = INFINITY;
    }
    _inclination = degrees(std::acos(h.z/h.magnitude()));
    _raan = degrees(std::acos(n.x/n.magnitude()));
    _argOfPeriapsis = degrees(std::acos(dot(n, e_vec)/(n.magnitude()*e_vec.magnitude())));
    _anomaly = degrees(std::acos(dot(e_vec, r)/(e_vec.magnitude()*r.magnitude())));
    
    if(n.y < 0) { _raan = 360.0 - _raan; }
    if(e_vec.z < 0) { _argOfPeriapsis = 360.0 - _argOfPeriapsis; }
    if(dot(r, v) < 0) { _anomaly = 360.0 - _anomaly; }
}

Orbit::Orbit(const MassiveBody& planet,
             double a,
             double e,
             double i,
             double arg_p,
             double raan,
             double v) :
    _sma(a),
    _eccentricity(e),
    _inclination(i),
    _argOfPeriapsis(arg_p),
    _raan(raan),
    _anomaly(v)
{
    _periapsis = _sma * (1 - e);
    _apoapsis = _sma * (1 + e);
}
