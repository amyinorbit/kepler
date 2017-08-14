//
//  orbit.cpp
//  kepler
//
//  Created by Amy Parent on 05/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "orbit.hpp"
#include "massive_body.hpp"

orbit::orbit(const massive_body& planet, const vec3& pos, const vec3& v) {
    // Elements calculation from
    // https://downloads.rene-schwarz.com/download/M002-Cartesian_State_Vectors_to_Keplerian_Orbit_Elements.pdf
    vec3 r = pos - planet.position();
    vec3 h = vec3::cross(r, v);
    vec3 n = vec3{-h.y, h.x, 0};
    double mu = planet.gravitation_parameter();
    double v2 = std::pow(v.magnitude(), 2);
    auto e_vec = (vec3::cross(v, h)/mu)-r.normalize();
    e = e_vec.magnitude();
    if(e != 1) {
        sma = 1 / ((2/r.magnitude()) - (v2/mu));
        pe = sma * (1 - e);
        ap = sma * (1 + e);
    } else {
        pe = std::pow(h.magnitude(), 2)/mu;
        ap = INFINITY;
        sma = INFINITY;
    }
    i = degrees(std::acos(h.z/h.magnitude()));
    raan = degrees(std::acos(n.x/n.magnitude()));
    arg_pea = degrees(std::acos(dot(n, e_vec)/(n.magnitude()*e_vec.magnitude())));
    anomaly = degrees(std::acos(dot(e_vec, r)/(e_vec.magnitude()*r.magnitude())));
    
    if(n.y < 0) { raan = 360.0 - raan; }
    if(e_vec.z < 0) { arg_pea = 360.0 - arg_pea; }
    if(dot(r, v) < 0) { anomaly = 360.0 - anomaly; }
}

orbit::orbit(const massive_body& planet,
             double a,
             double e,
             double i,
             double arg_p,
             double raan,
             double v) :
    sma(a),
    e(e),
    i(i),
    arg_pea(arg_p),
    raan(raan),
    anomaly(v)
{
    pe = sma * (1 - e);
    ap = sma * (1 + e);
}
