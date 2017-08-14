//
//  physics.hpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include "vec.hpp"

struct State {
    
    State() : p(0, 0, 0), v(0, 0, 0) {}
    State(const vec3& p, const vec3& v) : p(p), v(v) {}
    
    vec3    p;
    vec3    v;
};

struct Derivative {
    
    Derivative() : dp(0, 0, 0), dv(0, 0, 0) {}
    Derivative(const vec3& dp, const vec3& dv) : dp(dp), dv(dv) {}
    
    vec3    dp;
    vec3    dv;
};

