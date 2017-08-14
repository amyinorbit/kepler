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
#include "Integrator.hpp"


class simulation {
    
    simulation(std::shared_ptr<Integrator> integrator,
               const std::string& planet);
    
    
};

