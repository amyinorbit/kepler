//
//  rk4.hpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include "integrator.hpp"

class rk4 final : public integrator {
public:
    
    virtual void advanceState(SolidBody& body, const MassiveBody& planet, double dt);
    
private:
    
    derivative_t evaluate(SolidBody& body,
                          const MassiveBody& planet,
                          double dt,
                          const derivative_t& d);
    
    vec3 acceleration(const SolidBody& body, const state_t& state, const MassiveBody& planet);
    
};

