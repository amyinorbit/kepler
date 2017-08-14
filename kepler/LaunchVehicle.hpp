//
//  LaunchVehicle.hpp
//  kepler
//
//  Created by Amy Parent on 14/08/2017.
//  Copyright © 2017 cesarparent. All rights reserved.
//

#pragma once
#include <vector>
#include <functional>
#include "physics.hpp"
#include "utils.hpp"

struct Engine {
    Engine(double maxThrust, double slIsp, double vacIsp) {
        this->mDot = maxThrust / (vacIsp * 9.81);
        this->thrustCurve[1] = slIsp;
        this->thrustCurve[0] = vacIsp;
    }
    
    double Isp(double atmospheres) const {
        atmospheres = clamp(atmospheres, 0.0, 1.0);
        return lerp(this->thrustCurve[0], this->thrustCurve[1], atmospheres);
    }
    
    double thrust(double atmospheres) const {
        return this->Isp(atmospheres) * 9.81 * this->mDot;
    }
    
    double mDot;
    double thrustCurve[2];
};

struct Target {
    vec3 attitude;
    float throttle;
};

using GNC = std::function<Target(const State&, double, double)>;

struct Stage {
    double dryMass;
    double propellantMass;
    Engine engine;
    GNC guidance;
    
    double burnTime() const {
        return this->propellantMass / engine.mDot;
    }
};

class Vehicle {
    std::vector<Stage> stages;
};

