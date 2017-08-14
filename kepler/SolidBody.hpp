//
//  solid_body.hpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once

#include "physics.hpp"

struct SolidBody final {
    
    SolidBody(double mass, const vec3& moment_of_inertia, double area, double cd);
    
    ~SolidBody() {}
    
    void apply_force(const vec3& force, const vec3& com_offset);
    
    double      mass;
    vec3        moment_of_inertia;
    State     state;
    vec3        forces;
    vec3        torques;
    
    double      area;
    double      cd;
};

