//
//  Vec.hpp
//  Meteor
//
//  Created by Cesar Parent on 22/08/2015.
//  Copyright © 2015 Cesar Parent. All rights reserved.
//
#pragma once
#include "utils.hpp"
#include "matrix.hpp"
#include <cmath>
#include <iostream>


/*!
 * @class       vec
 * @ingroup     Geometry
 * @brief       An object that can represents vectors of different types (int, float, double) and
 *              dimensions (2+).
 * @details     Vectors can be added and subtracted to one another, multiplied
 *              and divided by scalars or other vectors, and multiplied by matrices of compatible
 *              dimensions
 * @tparam      T               The type of the vector's components.
 * @tparam      size            The number of components in the vector.
 */
template <typename T, int size>
struct vec {
    
    /**
     * @name        Creating Vectors
     * @{
     */
    
    /*!
     * @brief       Creates a vector from a list of values.
     * @param       values      List ofVector's components.
     */
    vec(T values[size]) {
        for(int i = 0; i < size; ++i) {
            data[i] = values[i];
        }
    }
    
    /*!
     * @brief       Creates a vector with a single value for each of its components
     * @param       value       Value of every component of the vector.
     */
    vec(T value = 0) {
        for(int i = 0; i < size; ++i) {
            data[i] = value;
        }
    }
    
    
    /*!
     * @brief       Creates a vector from a vector of one dimension smaller, filling the remaining
     *              component with a constant value.
     * @param       vec         Vector to create the new vector with.
     * @param       rem         Value to fill the remaining member with. Defaults to `0`
     */
    vec(const vec<T, size-1>& vec, T rem = 0) {
        for(int i = 0; i < size-1; ++i) {
            data[i] = vec.data[i];
        }
        data[size-1] = rem;
    }
    
    /**
     * @}
     */
    
    /*!
     * @internal
     * @brief       Copies a vector into another.
     * @param       rhs         Copied vector
     */
    vec(const vec<T, size>& rhs) {
        for(int i = 0; i < size; ++i) {
            data[i] = rhs.data[i];
        }
    }
    
    /*!
     * @internal
     * @brief       Assigment operator (Copy semantics).
     * @param       rhs         Copied vector.
     */
    vec&
    operator=(const vec<T, size>& rhs) {
        if(this != &rhs) {
            for(int i = 0; i < size; ++i) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }
    
    /*!
     * @internal
     * @brief       Conversion operations between vectors of different types.
     *              The origin type T must be cast-able to the destination type P.
     */
    template<typename P>
    operator vec<P, size>() const {
        vec<P, size> v;
        for(int i = 0; i < size; ++i) {
            v.data[i] = (P)data[i];
        }
        return v;
    }
    
    /**
     * @name        Inspecting a Vector's properties
     * @{
     */
    
    /*!
     * @brief       Returns a vector with the same direction as the receiver, with a given
     *              magnitude.
     * @param       magnitude   Magnitude of the normalized vector. Defaults to `1`.
     */
    vec<T, size>
    normalize(float length = 1) const {
        float _length = magnitude();
        if(_length != 0) {
            return vec<T, size>(*this) * (length / magnitude());
        }
        return vec<T, size>{0};
    }
    
    /*!
     * @brief       Returns the vector's length.
     * @return      The vector's length.
     */
    float
    magnitude() const {
        
        float l = 0;
        for(int i = 0; i < size; ++i) {
            l += data[i] * data[i];
        }
        return sqrtf(l);
    }
    
    /**
     * @}
     */
    
    /*!
     * @internal
     * @brief       Vector members accessor.
     */
    T&
    operator[](int i) { return data[i]; }
    
    /*!
     * @brief       Array storing the vector's components
     */
    T       data[size];
    
};


// MARK: -
// MARK: Compound Operators

// vec += vec
template<typename T, int S> vec<T, S>&
operator+=(vec<T, S>& lhs, const vec<T, S>& rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] += (T)rhs.data[i];
    }
    return lhs;
}

// vec -= vec
template<typename T, int S> vec<T, S>&
operator-=(vec<T, S>& lhs, const vec<T, S>& rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] -= (T)rhs.data[i];
    }
    return lhs;
}

// vec *= vec
template<typename T, int S> vec<T, S>&
operator*=(vec<T, S>& lhs, const vec<T, S>& rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] *= (T)rhs.data[i];
    }
    return lhs;
}

// vec *= scalar
template<typename T, int S> vec<T, S>&
operator*=(vec<T, S>& lhs, double rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] *= rhs;
    }
    return lhs;
}

// vec /= vec
template<typename T, int S> vec<T, S>&
operator/=(vec<T, S>& lhs, const vec<T, S>& rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] /= (T)rhs.data[i];
    }
    return lhs;
}

// vec /= scalar
template<typename T, int S> vec<T, S>&
operator/=(vec<T, S>& lhs, double rhs) {
    for(int i = 0; i < S; ++i) {
        lhs.data[i] /= rhs;
    }
    return lhs;
}

// MARK: -
// MARK: binary operators

// vec + vec
template<typename T, int S> const vec<T, S>
operator+(const vec<T, S>& lhs, const vec<T, S>& rhs) {
    vec<T, S> v(lhs);
    return v += rhs;
}

// vec - vec
template<typename T, int S> const vec<T, S>
operator-(const vec<T, S>& lhs, const vec<T, S>& rhs) {
    vec<T, S> v(lhs);
    return v -= rhs;
}

// vec * vec
template<typename T, int S> const vec<T, S>
operator*(const vec<T, S>& lhs, const vec<T, S>& rhs) {
    vec<T, S> v(lhs);
    return v *= rhs;
}

// vec * scalar
template<typename T, int S> const vec<T, S>
operator*(const vec<T, S>& lhs, double rhs) {
    vec<T, S> v(lhs);
    return v *= rhs;
}

// scalar * vec
template<typename T, int S> const vec<T, S>
operator*(double lhs, const vec<T, S>& rhs) {
    vec<T, S> v(rhs);
    return v *= lhs;
}

// vec / vec
template<typename T, int S> const vec<T, S>
operator/(const vec<T, S>& lhs, const vec<T, S>& rhs) {
    vec<T, S> v(lhs);
    return v /= rhs;
}

// vec / scalar
template<typename T, int S> const vec<T, S>
operator/(const vec<T, S>& lhs, double rhs) {
    vec<T, S> v(lhs);
    return v /= rhs;
}

template<typename T, int S> const vec<T, S>
operator/(double lhs, const vec<T, S>& rhs) {
    vec<T, S> v{0};
    for(int i = 0; i < S; ++i) {
        v.data[i] = lhs/rhs.data[i];
    }
    return v;
}

/*!
 * @internal
 * @brief       Multiply a vector by a matrix.
 */
template<typename T, int r, int c> const vec<T, c>
operator*(const matrix<r,c>& lhs, const vec<T,c>& rhs) {
    vec<T,c> v = 0;
    T temp;
    for(int i = 0; i < c; ++i) {
        temp = 0;
        for(int k = 0; k < c; ++k) {
            temp += (T)lhs[i][k] * rhs.data[k];
        }
        v.data[i] = temp;
    }
    return v;
}

// MARK: -
// MARK: Vector printer

template<typename T, int S> std::ostream&
operator<<(std::ostream& s, const vec<T, S>& v) {
    s<<"{";
    for(int i = 0; i < S; ++i) {
        s << v.data[i];
        if(i != S-1) {
            s<<", ";
        }
    }
    s<<"}";
    return s;
}

// MARK: -
// MARK: Unary minus operator

template<typename T, int S> vec<T, S>
operator-(const vec<T, S>& rhs) {
    return -1*vec<T, S>(rhs);
}

// MARK: -
// MARK: Other vector-specific operations

/*!
 * @brief       Returns the dot product of two vectors of the same dimension.
 * @param       a       First vector.
 * @param       b       Second vector.
 * @return      Result of the dot product of a and b.
 */
template<typename T, int S> T
dot(const vec<T, S>& a, const vec<T, S>& b) {
    T prod;
    for(int i = 0; i < S; ++i) {
        prod += a.data[i] * b.data[i];
    }
    return prod;
}

// MARK: -
// MARK: Common use specialisations

/*!
 * @internal
 * @brief       Defines a 2D vector and allows x/y access
 *
 */
template <typename T>
struct vec<T, 2> {
    
    /*!
     * @brief       Create a vector from its x and y components.
     */
    vec(T x, T y) : x(x), y(y) { }
    
    /*!
     * @brief       Create a vector from another vector.
     */
    vec(const vec<T, 2>& rhs) {
        x = rhs.x;
        y = rhs.y;
    }
    
    /*!
     * @brief       Create a vector with a fied value for its components
     */
    vec(T value = 0) {
        x = value;
        y = value;
    }
    
    /*!
     * @brief       Vector cast operator
     */
    template<typename P>
    operator vec<P, 2>() const {
        return vec<P, 2>(P(x), P(y));
    }
    
    /*!
     * @brief       Get the vector's magnitude.
     */
    T
    magnitude() const {
        return std::sqrt(x*x + y*y);
    }
    
    /*!
     * @brief       Returns a vector with the same direction and a given magnitude
     */
    vec<T, 2>
    normalize(float len = 1) const {
        T _length = magnitude();
        if(_length == 0 || _length == 1) { return *this; }
        return vec<T, 2>(*this) * (len / _length);
    }
    
    union {
        T data[2];
        struct { T x,y; };
        struct { T width, height; };
    };
};

/*!
 * @internal
 * @brief       Defines a 3D vector and allows x/y/z/xy access
 *
 */
template <typename T>
struct vec<T, 3> {
    
    /*!
     * @brief       Create a vector from its x, y and z components.
     */
    vec(T x, T y, T z) : x(x), y(y), z(z) { }
    
    /*!
     * @brief       Create a vector from another vector.
     */
    vec(const vec<T, 3>& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
    
    /*!
     * @bief        Create a 3D vector from a 2D vector, filling Z with rem.
     */
    vec(const vec<T, 2>& rhs, float rem = 0) {
        x = rhs.x;
        y = rhs.y;
        z = rem;
    }
    
    /*!
     * @brief       Create a vector with a fied value for its components
     */
    vec(T value = 0) {
        x = value;
        y = value;
        z = value;
    }
    
    /*!
     * @brief       Vector cast operator
     */
    template<typename P>
    operator vec<P, 3>() const {
        return vec<P, 3>((P)x, (P)y, (P)z);
    }
    
    /*!
     * @brief       Get the vector's magnitude.
     */
    T
    magnitude() const {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    static vec
    cross(const vec& a, const vec& b) {
        return vec {
             (a.y*b.z - a.z*b.y),
            -(a.x*b.z - a.z*b.x),
             (a.x*b.y - a.y*b.x)
        };
    }
    
    /*!
     * Rodriges rotation formula
     */
    vec
    rotate(const vec& axis, double angle) const {
        auto p = this->normalize();
        auto a = axis.normalize();
        auto s = std::sin(angle);
        auto c = std::cos(angle);
        
        auto t = mat33{
            a.x*a.x*(1-c) + c,      a.x*a.y*(1-c) - a.z*s,  a.x*a.z*(1-c) + a.y*s,
            a.y*a.x*(1-c) + a.z*s,  a.y*a.y*(1-c) + c,      a.y*a.z*(1-c) - a.x*s,
            a.z*a.x*(1-c) - a.y*s,  a.z*a.y*(1-c) + a.x*s,  a.z*a.z*(1-c) + c,
        };
        
        return t * p;
    }
    
    /*!
     * @brief       Returns a vector with the same direction and a given magnitude
     */
    vec<T, 3>
    normalize(T len = 1) const {
        T _length = magnitude();
        if(_length == 0 || _length == 1) { return *this; }
        
        return vec<T, 3>(*this) * (len / _length);
    }
    
    union {
        T data[3];
        struct { T x,y,z; };
        vec<T, 2> xy;
    };
};


/// @brief      2D float-precision vector
typedef vec<double, 2> vec2;
/// @brief      3D float-precision vector
typedef vec<double, 3> vec3;

