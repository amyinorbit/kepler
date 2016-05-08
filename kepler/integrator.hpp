//
//  integrator.hpp
//  kepler
//
//  Created by Cesar Parent on 05/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#pragma once

struct integrator {
    
    virtual ~integrator();
    
    
    virtual void Evaluate() = 0;
};