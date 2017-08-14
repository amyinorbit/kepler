//
//  rk4.hpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include "Integrator.hpp"

class RK4 final : public Integrator {
public:
    
    virtual void advanceState(SolidBody& body, const MassiveBody& planet, double dt);
    
private:
    
    Derivative evaluate(SolidBody& body,
                          const MassiveBody& planet,
                          double dt,
                          const Derivative& d);
    
    vec3 acceleration(const SolidBody& body, const State& state, const MassiveBody& planet);
    
};


