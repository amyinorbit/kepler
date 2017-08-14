//
//  integrator.hpp
//  kepler
//
//  Created by Amy Parent on 05/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once

#include "SolidBody.hpp"
#include "MassiveBody.hpp"

class integrator {
public:
    
    virtual ~integrator() {}
    
    virtual void advanceState(SolidBody& body, const MassiveBody& planet, double dt) = 0;
};

