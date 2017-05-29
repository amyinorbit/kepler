//
//  physics.hpp
//  kepler
//
//  Created by Cesar Parent on 08/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once
#include "vec.hpp"

struct state_t {
    
    state_t() : p(0, 0, 0), v(0, 0, 0) {}
    
    state_t(const vec3& p, const vec3& v) : p(p), v(v) {}
    
    vec3    p;
    vec3    v;
};

struct derivative_t {
    
    derivative_t() : dp(0, 0, 0), dv(0, 0, 0) {}
    
    derivative_t(const vec3& dp, const vec3& dv) : dp(dp), dv(dv) {}
    
    vec3    dp;
    vec3    dv;
};

