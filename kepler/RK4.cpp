//
//  rk4.cpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "RK4.hpp"

void RK4::advanceState(SolidBody &body, const MassiveBody &planet, double dt) {
    auto a = evaluate(body, planet, dt, Derivative{});
    auto b = evaluate(body, planet, dt*0.5, a);
    auto c = evaluate(body, planet, dt*0.5, b);
    auto d = evaluate(body, planet, dt, c);
    
    auto dpdt = (a.dp + 2.f*(b.dp + c.dp) + d.dp)/6.f;
    auto dvdt = (a.dv + 2.f*(b.dv + c.dv) + d.dv)/6.f;
    
    body.state.p += dpdt * dt;
    body.state.v += dvdt * dt;
}

Derivative RK4::evaluate(SolidBody &body,
                           const MassiveBody &planet,
                           double dt,
                           const Derivative &d) {
    State s;
    
    s.p = body.state.p + dt * d.dp;
    s.v = body.state.v + dt * d.dv;
    
    Derivative out;
    
    out.dp = s.v;
    out.dv = acceleration(body, s, planet);
    
    return out;
}

vec3 RK4::acceleration(const SolidBody &body, const State& state, const MassiveBody &planet) {
    auto airspeed = state.v - planet.inertialVelocity(state.p);
    auto drag = 0.5 * planet.atmosphericDensity(state.p) * std::pow(airspeed.magnitude(), 2)*body.area*body.cd;
    return ((body.forces - airspeed.normalize(drag)) / body.mass) + planet.gravity(state.p);
}
