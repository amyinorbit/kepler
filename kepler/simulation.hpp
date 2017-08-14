//
//  simulation.hpp
//  kepler
//
//  Created by Amy Parent on 09/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#pragma once
#include <memory>
#include <string>
#include "integrator.hpp"


class simulation {
    
    simulation(std::shared_ptr<integrator> integrator,
               const std::string& planet);
    
    
};

