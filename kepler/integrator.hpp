//
//  integrator.hpp
//  kepler
//
//  Created by Amy Parent on 05/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once

#include "solid_body.hpp"
#include "massive_body.hpp"

class integrator {
public:
    
    virtual ~integrator() {}
    
    virtual void advance_state(solid_body& body, const massive_body& planet, double dt) = 0;
};

