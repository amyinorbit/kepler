//
//  solid_body.hpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once

#include "physics.hpp"

class SolidBody {
public:
    virtual ~SolidBody() {}
    
    /// The body's position and velocity vectors in the simulation's reference frame.
    virtual State stateVectors() const = 0;
    
    /// The body's current mass.
    virtual double mass() const = 0;
    
    /// The forces currently applied to the body.
    virtual vec3 forces() const = 0;
    
    /// The body's plane-equivalent body's drag coefficient.
    virtual double dragCoefficient() const = 0;
    
    /// The body's frontal surface area, used to compute aerodyamic drag.
    virtual double surfaceArea() const = 0;
};
