///////////////////////////////////////////////////
//
//  Hamish Carr
//  January, 2018
//
//  ------------------------
//  Cartesian3.h
//  ------------------------
//  
//  A minimal class for a point in Cartesian space
//  
///////////////////////////////////////////////////

#include "Cartesian3.h"
#include "math.h"
#include "my_code/utility.h"
#include <iomanip>
#include <cmath>

// constructors
Cartesian3::Cartesian3() 
    : x(0.0), y(0.0), z(0.0) 
    {}

Cartesian3::Cartesian3(float X, float Y, float Z)
    : x(X), y(Y), z(Z) 
    {}

Cartesian3::Cartesian3(const Cartesian3 &other)
    : x(other.x), y(other.y), z(other.z) 
    {}
    
// equality operator
bool Cartesian3::operator ==(const Cartesian3 &other) const
    { // Cartesian3::operator ==()
    return ((x == other.x) && (y == other.y) && (z == other.z));
    } // Cartesian3::operator ==()

// addition operator
Cartesian3 Cartesian3::operator +(const Cartesian3 &other) const
    { // Cartesian3::operator +()
    Cartesian3 returnVal(x + other.x, y + other.y, z + other.z);
    return returnVal;
    } // Cartesian3::operator +()

// subtraction operator
Cartesian3 Cartesian3::operator -(const Cartesian3 &other) const
    { // Cartesian3::operator -()
    Cartesian3 returnVal(x - other.x, y - other.y, z - other.z);
    return returnVal;
    } // Cartesian3::operator -()

// multiplication operator
Cartesian3 Cartesian3::operator *(float factor) const
    { // Cartesian3::operator *()
    Cartesian3 returnVal(x * factor, y * factor, z * factor);
    return returnVal;
    } // Cartesian3::operator *()

// division operator
Cartesian3 Cartesian3::operator /(float factor) const
    { // Cartesian3::operator /()
    Cartesian3 returnVal(x / factor, y / factor, z / factor);
    return returnVal;
    } // Cartesian3::operator /()


Cartesian3 &Cartesian3::operator+=(const Cartesian3 &v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Cartesian3 &Cartesian3::operator*=(const double t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
}

Cartesian3 &Cartesian3::operator/=(const double t) {
    return *this *= 1/t;
}

// dot product routine
float Cartesian3::dot(const Cartesian3 &other) const
    { // Cartesian3::dot()
    float returnVal = x * other.x + y * other.y + z * other.z;
    return returnVal;
    } // Cartesian3::dot()

// cross product routine
Cartesian3 Cartesian3::cross(const Cartesian3 &other) const
    { // Cartesian3::cross()
    Cartesian3 returnVal(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    return returnVal;
    } // Cartesian3::cross()

// routine to find the length
float Cartesian3::length() const
    { // Cartesian3::length()
    return sqrt(x*x + y*y + z*z);   
    } // Cartesian3::length()

// normalisation routine
Cartesian3 Cartesian3::unit() const
    { // Cartesian3::unit()
    float length = sqrt(x*x+y*y+z*z);
    Cartesian3 returnVal(x/length, y/length, z/length);
    return returnVal;
    } // Cartesian3::unit()

// operator that allows us to use array indexing instead of variable names
float &Cartesian3::operator [] (const int index)
    { // operator []
    // use default to catch out of range indices
    // we could throw an exception, but will just return the 0th element instead
    switch (index)
        { // switch on index
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        // actually the error case
        default:
            return x;       
        } // switch on index
    } // operator []

// operator that allows us to use array indexing instead of variable names
const float &Cartesian3::operator [] (const int index) const
    { // operator []
    // use default to catch out of range indices
    // we could throw an exception, but will just return the 0th element instead
    switch (index)
        { // switch on index
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        // actually the error case
        default:
            return x;       
        } // switch on index
    }

double Cartesian3::get_x() const {
    return x;
}

double Cartesian3::get_y() const {
    return y;
}

double Cartesian3::get_z() const {
    return z;
}

double Cartesian3::length_squared() const {
    return x*x + y*y + z*z;
}

Cartesian3 Cartesian3::random() {
    return Cartesian3(randomDouble(), randomDouble(), randomDouble());
}

Cartesian3 Cartesian3::random(double min, double max) {
    return Cartesian3(randomDoubleInRange(min, max), randomDoubleInRange(min, max), randomDoubleInRange(min, max));
}

bool Cartesian3::near_zero() const {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
}

// operator []

// multiplication operator
Cartesian3 operator *(float factor, const Cartesian3 &right)
    { // operator *
    // scalar multiplication is commutative, so flip & return
    return right * factor;
    } // operator *


Cartesian3 operator*(const Cartesian3 &u, const Cartesian3 &v) {
    return Cartesian3(u[0] * v[0], u[1] * v[1], u[2] * v[2]);
}

// stream input
std::istream & operator >> (std::istream &inStream, Cartesian3 &value)
    { // stream output
    inStream >> value.x >> value.y >> value.z;
    return inStream;
    } // stream output
        
// stream output
std::ostream & operator << (std::ostream &outStream, const Cartesian3 &value)
    { // stream output
    outStream << std::setprecision(4) << value.x << " " << std::setprecision(4) << value.y << " " << std::setprecision(4) << value.z;
    return outStream;
    } // stream output

double dot(const Cartesian3 &u, const Cartesian3 &v) {
    return u[0] * v[0]
           + u[1] * v[1]
           + u[2] * v[2];
}

Cartesian3 cross(const Cartesian3 &u, const Cartesian3 &v) {
    return Cartesian3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

Cartesian3 unit_vector(Cartesian3 v) {
    return v / v.length();
}

Cartesian3 randomInUnitSphere() {
    while (true) {
        //把圆心当做0,0,0点,那么随机取点的范围应该上,三个轴都在-1到1之间
        //然后p-0点也就是p自己,然后计算p的长度是否大于0.小于0在球体内部
        auto p = Cartesian3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Cartesian3 randomUnitVector() {
    return unit_vector(randomInUnitSphere());
}

Cartesian3 randomInHemisphere(const Cartesian3 &normal) {
    Cartesian3 in_unit_sphere = randomInUnitSphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -1*in_unit_sphere;
}

Cartesian3 reflect(const Cartesian3 &v, const Cartesian3 &n) {
    return v - 2*dot(v,n)*n;
}

Cartesian3 refract(const Cartesian3 &uv, const Cartesian3 &n, double etai_over_etat) {
    auto cos_theta = std::fmin(dot(-1*uv, n), 1.0);
    Cartesian3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Cartesian3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

Cartesian3 randomInUnitDisk() {
    while (true) {
        auto p = Cartesian3(randomDoubleInRange(-1, 1), randomDoubleInRange(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Cartesian3 randomCosineDirection() {
    auto r1 = randomDouble();
    auto r2 = randomDouble();
    auto z = sqrt(1-r2);

    auto phi = 2*pi*r1;
    auto x = cos(phi)*sqrt(r2);
    auto y = sin(phi)*sqrt(r2);

    return Cartesian3(x, y, z);
}