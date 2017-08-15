//
//  rk4.cpp
//  kepler
//
//  Created by Amy Parent on 08/05/2016.
//  Copyright © 2016 Amy Parent. All rights reserved.
//

#include "RK4.hpp"

State RK4::advanceState(const SolidBody &body, const MassiveBody &planet, double dt) {
    
    auto previousState = body.stateVectors();
    
    auto a = evaluate(body, planet, dt, Derivative{});
    auto b = evaluate(body, planet, dt*0.5, a);
    auto c = evaluate(body, planet, dt*0.5, b);
    auto d = evaluate(body, planet, dt, c);
    
    auto dpdt = (a.dp + 2.f*(b.dp + c.dp) + d.dp)/6.f;
    auto dvdt = (a.dv + 2.f*(b.dv + c.dv) + d.dv)/6.f;
    
    return State(previousState.p + (dpdt * dt), previousState.v + (dvdt * dt));
}

Derivative RK4::evaluate(const SolidBody &body, const MassiveBody &planet, double dt,const Derivative &d) {
    auto previousState = body.stateVectors();
    auto s = State(previousState.p + (d.dp * dt), previousState.v + (d.dv * dt));
    return Derivative(s.v, acceleration(body, s, planet));
}

vec3 RK4::acceleration(const SolidBody &body, const State& state, const MassiveBody &planet) {
    auto airspeed = state.v - planet.inertialVelocity(state.p);
    auto drag = 0.5 * planet.atmosphericDensity(state.p)
              * std::pow(airspeed.magnitude(), 2)
              *body.surfaceArea() * body.dragCoefficient();
    return ((body.forces() - airspeed.normalize(drag)) / body.mass()) + planet.gravity(state.p);
}
