//
//  solid_body.hpp
//  kepler
//
//  Created by Cesar Parent on 08/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once

#include "physics.hpp"

struct solid_body final {
    
    solid_body(double mass, const vec3& moment_of_inertia, double area, double cd);
    
    ~solid_body() {}
    
    void apply_force(const vec3& force, const vec3& com_offset);
    
    double      mass;
    vec3        moment_of_inertia;
    state_t     state;
    vec3        forces;
    vec3        torques;
    
    double      area;
    double      cd;
};

