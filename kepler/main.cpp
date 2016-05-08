//
//  main.cpp
//  kepler
//
//  Created by Cesar Parent on 04/05/2016.
//  Copyright © 2016 cesarparent. All rights reserved.
//

#include <iostream>
#include "vec.hpp"
#include "matrix.hpp"
#include "massive_body.hpp"

int main(int argc, const char * argv[]) {
    
    auto earth = massive_body("Earth", 3600*24, 6371e3, 3.986004418e14, 1.221, 8.5e3, 400e3);
    
    auto kerbin = massive_body("Kerbin", 3600*9, 1200e3, 14126.4e9, 1.221, 5.6e3, 70e3);
    
    auto coord = massive_body::coordinates{0, 0, 0};
//    auto test = kerbin.cartesian(coord);
//    auto up = kerbin.up(test);
//    auto north = kerbin.north(test);
//    auto east = kerbin.east(test);
//    
//    // insert code here...
//    std::cout << "pos: " << test << std::endl;
//    std::cout << "up:  " << up << std::endl;
//    std::cout << "n:   " << north << std::endl;
//    std::cout << "e:   " << east << std::endl;
//    std::cout << "n-e: " << north.rotate(up, -M_PI_2) << std::endl;
//    std::cout << "n45: " << kerbin.heading(test, 0, 45) << std::endl;
    
    auto test = earth.cartesian(coord);
    std::cout << earth.inertial_velocity(test) << std::endl;
    auto halfday = earth.polar(test, 24 * 3600);
    std::cout << "Longitude: " << halfday.longitude << std::endl;
    
    return 0;
}
