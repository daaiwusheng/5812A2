//////////////////////////////////////////////////////////////////////
//
//  University of Leeds
//  COMP 5812M Foundations of Modelling & Rendering
//  User Interface for Coursework
//
//  September, 2020
//
//  ------------------------
//  Cartesian3.h
//  ------------------------
//  
//  A minimal class for a point in Cartesian space
//  
///////////////////////////////////////////////////

#ifndef CARTESIAN3_H
#define CARTESIAN3_H

#include <iostream>

// the class - we will rely on POD for sending to GPU
class Cartesian3
    { // Cartesian3
    public:
    // the coordinates
    float x, y, z;

    // constructors
    Cartesian3();
    Cartesian3(float X, float Y, float Z);
    Cartesian3(const Cartesian3 &other);
    
    // equality operator
    bool operator ==(const Cartesian3 &other) const;

    // addition operator
    Cartesian3 operator +(const Cartesian3 &other) const;

    // subtraction operator
    Cartesian3 operator -(const Cartesian3 &other) const;

    // multiplication operator
    Cartesian3 operator *(float factor) const;

    // division operator
    Cartesian3 operator /(float factor) const;

    Cartesian3& operator+=(const Cartesian3 &v);

    Cartesian3& operator*=(const double t);

    Cartesian3& operator/=(const double t);

    // dot product routine
    float dot(const Cartesian3 &other) const;

    // cross product routine
    Cartesian3 cross(const Cartesian3 &other) const;
    
    // routine to find the length
    float length() const;
    
    // normalisation routine
    Cartesian3 unit() const;
    
    // operator that allows us to use array indexing instead of variable names
    float &operator [] (const int index);
    const float &operator [] (const int index) const;
    //---VVV-----add some new functions
    double get_x() const;
    double get_y() const;
    double get_z() const;


    double length_squared() const;

    inline static Cartesian3 random();

    inline static Cartesian3 random(double min, double max);

    bool near_zero() const;

    //---^^^-----add some new functions
    }; // Cartesian3

// multiplication operator
Cartesian3 operator *(float factor, const Cartesian3 &right);


Cartesian3 operator*(const Cartesian3 &u, const Cartesian3 &v);


// stream input
std::istream & operator >> (std::istream &inStream, Cartesian3 &value);

// stream output
std::ostream & operator << (std::ostream &outStream, const Cartesian3 &value);

double dot(const Cartesian3 &u, const Cartesian3 &v);

Cartesian3 cross(const Cartesian3 &u, const Cartesian3 &v);

Cartesian3 unit_vector(Cartesian3 v);

Cartesian3 random_in_unit_sphere();

Cartesian3 random_unit_vector();

Cartesian3 random_in_hemisphere(const Cartesian3& normal);

Cartesian3 reflect(const Cartesian3& v, const Cartesian3& n);

Cartesian3 refract(const Cartesian3& uv, const Cartesian3& n, double etai_over_etat);

Cartesian3 random_in_unit_disk();

Cartesian3 random_cosine_direction();

#endif