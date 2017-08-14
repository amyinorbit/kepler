//
//  main.cpp
//  kepler
//
//  Created by Amy Parent on 04/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdint>
#include "RK4.hpp"
#include "MassiveBody.hpp"
#include "Orbit.hpp"

void debug_orbit(const Orbit& o, const MassiveBody& p) {
    std::cout << "==== keplerian orbital elements ====" << std::endl;
    std::cout << "ApA: " << (o.apoapsis() - p.radius())/1000.0 << "km" << std::endl;
    std::cout << "PeA: " << (o.periapsis() - p.radius())/1000.0 << "km" << std::endl;
    std::cout << "SmA: " << (o.semiMajorAxis()  - p.radius())/1000.0 << "km" << std::endl;
    std::cout << "Inc: " << o.inclination() << "°" << std::endl;
    std::cout << "Ecc: " << o.eccentricity() << std::endl;
    std::cout << std::endl;
}

const MassiveBody::coordinates boca_chica{25.996, -97.154, 160.0e3};
const MassiveBody::coordinates ccafs{28.562106, -80.577180, 10000.0e3};
const MassiveBody::coordinates gto{0.0, 0.0, 80.0e3};
const MassiveBody::coordinates sso{25.996, -97.154, 200.0e3};

int main(int argc, const char * argv[]) {
    
    auto earth = MassiveBody("Earth", 3600*24, 6371e3, 3.986004418e14, 1.221, 8.5e3, 2000e3);
    auto kerbin = MassiveBody("Kerbin", 3600*9, 1200e3, 14126.4e9, 1.221, 5.6e3, 70e3);
    
    vec3 r = earth.cartesian(ccafs);
    
    //vec3 r = vec3{4059608.89, -1528891.74, 5202483.96};
    double speed = 3713;
    double azimuth = 45;
    double vx = std::cos(radians(azimuth)) * speed;
    double vy = std::sin(radians(azimuth)) * speed;
    vec3 v = earth.east(r) * vx + earth.north(r) * vy;
    //vec3 v = vec3{1472.907943, 7457.907896, 1039.523951};
    
    Orbit o = Orbit(earth, r, v);
    debug_orbit(o, earth);
    
    std::cout << "Density: " << earth.atmosphericDensity(r) << std::endl;
    
    
    SolidBody body = SolidBody(419455, {10, 10, 10}, 1640.6, 2.0);
    body.state.p = r;
    body.state.v = v;
    
    RK4 integrator{};
    
    std::ofstream out{argv[1]};
    out << "time,x,y,z,ix,iy,iz,lat,lon,alt" << std::endl;
    
    double time = 0;
    double inc = .10;
    double simu_time = 6;
    
    for(uint64_t i = 0; i < (simu_time/inc)*3600; ++i) {
        time += i*inc;
        integrator.advanceState(body, earth, inc);
        
        if(body.state.p.magnitude() < earth.radius()+50e3) break;
        
        if(i % 40 != 0) continue;
        
        auto coord = earth.polar(body.state.p, i*inc);
        //coord.altitude = 0;
        auto inertial = earth.cartesian(coord);
        
        out << time << ",";
        out << body.state.p.x << "," << body.state.p.y << "," << body.state.p.z << ",";
        out << inertial.x << "," << inertial.y << ","  << inertial.z << ",";
        out << coord.latitude << "," << coord.longitude << "," << coord.altitude << std::endl;
        
    }
    
    std::cout << "simulation ended after " << std::floor(time) << "seconds (" << std::floor(time/3600.0) << " h, " << std::floor(time/(24 * 3600.0)) << "d)" << std::endl;
    
    debug_orbit(Orbit(earth, body.state.p, body.state.v), earth);
    
    out.close();
    
    return 0;
}
