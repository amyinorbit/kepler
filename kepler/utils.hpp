//
//  Utilities.h
//  Meteor
//
//  Created by Cesar Parent on 13/07/2015.
//  Copyright (c) 2015 Cesar Parent. All rights reserved.
//

#pragma once

#include <cstdio>
#include <cmath>

/*!
 * @brief       Converts an angle in degrees to radians.
 * @ingroup     Geometry
 * @param       degrees An angle in degrees.
 * @return      The angle in radians.
 */
inline double
radians(double degrees) {
    return degrees * M_PI / 180.f;
}

/*!
 * @brief       Converts an angle in radians to degrees.
 * @ingroup     Geometry
 * @param       radians An angle in radians.
 * @return      The angle in degrees.
 */
inline double
degrees(double radians) {
    return radians * 180.f / M_PI;
}

/*!
 * @brief       Returns the minimum of two objects of type <code>T</code>
 * @note        Both objects must implement comparison operators.
 * @tparam      T       The type of the objects to return.
 * @ingroup     Geometry
 * @param       a       First object to compare.
 * @param       b       Second object to compare.
 * @return      The minimum of a and b.
 */
template<typename T>
inline T
min(T a, T b) {
    return (a < b) ? a : b;
}

/*!
 * @brief       Returns the maximum of two objects of type <code>T</code>
 * @note        Both objects must implement comparison operators.
 * @tparam      T       The type of the object to return.
 * @ingroup     Geometry
 * @param       a       First object to compare.
 * @param       b       Second object to compare.
 * @return      The maximum of a and b.
 */
template<typename T>
inline T
max(T a, T b) {
    return (a > b) ? a : b;
}

/*!
 * @brief       Clamps a value between two bounds.
 * @ingroup     Geometry
 * @tparam      T       The type of the object to clamp.
 * @param       value   The varable to clamp.
 * @param       min     The value's lower boundary.
 * @param       max     The value's upper boundary.
 */
template<typename T>
inline T
clamp(T value, T min, T max) {
    return value <= min ? min : value >= max ? max : value;
}

/*!
 * @brief       Caps a value to an upper bound.
 * @ingroup     Geometry
 * @tparam      T       The type of the object to cap.
 * @param       value   The varable to cap.
 * @param       cap     The value's upper boundary.
 */
template<typename T>
inline T
cap(T value, T cap) {
    return (value > cap) ? cap : value;
}

/*!
 * @brief       Linearly interpolates between two values.
 * @ingroup     Geometry
 * @param       from    First value.
 * @param       to      Second value.
 * @param       t       Interpolation proportion.
 * @return      A value equivalent to `(1-t)*from + t*to`.
 */
template<typename T> T
lerp(T from, T to, float t) {
    t = clamp(t, 0.f, 1.f);
    return (1-t)*from + t*to;
}

