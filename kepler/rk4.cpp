//
//  rk4.cpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "rk4.hpp"

void rk4::advance_state(solid_body &body, const massive_body &planet, double dt) {
    auto a = evaluate(body, planet, dt, derivative_t{});
    auto b = evaluate(body, planet, dt*0.5, a);
    auto c = evaluate(body, planet, dt*0.5, b);
    auto d = evaluate(body, planet, dt, c);
    
    auto dpdt = (a.dp + 2.f*(b.dp + c.dp) + d.dp)/6.f;
    auto dvdt = (a.dv + 2.f*(b.dv + c.dv) + d.dv)/6.f;
    
    body.state.p += dpdt * dt;
    body.state.v += dvdt * dt;
}

derivative_t rk4::evaluate(solid_body &body,
                           const massive_body &planet,
                           double dt,
                           const derivative_t &d) {
    state_t s;
    
    s.p = body.state.p + dt * d.dp;
    s.v = body.state.v + dt * d.dv;
    
    derivative_t out;
    
    out.dp = s.v;
    out.dv = acceleration(body, s, planet);
    
    return out;
}

vec3 rk4::acceleration(const solid_body &body, const state_t& state, const massive_body &planet) {
    auto airspeed = state.v - planet.inertial_velocity(state.p);
    auto drag = 0.5 * planet.atmo_density(state.p) * std::pow(airspeed.magnitude(), 2)*body.area*body.cd;
    return ((body.forces - airspeed.normalize(drag)) / body.mass) + planet.gravity(state.p);
}