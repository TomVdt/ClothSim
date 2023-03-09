#pragma once
#include <iostream>  // for std::ostream
#include "constants.h"

class Vector3D {
private:
    double x, y, z;

public:
    // Constructors
    Vector3D();
    Vector3D(double, double, double);
    // TODO: Copie par défaut suffisante?
    // Vector3D(const Vector3D&);

    // Getters
    double getX() const {return x;};
    double getY() const {return y;};
    double getZ() const {return z;};

    // Setters
    void setX(double x_) {x = x_;};
    void setY(double y_) {y = y_;};
    void setZ(double z_) {z = z_;};

    // Internal operator overloading
    Vector3D& operator+=(const Vector3D&);
    Vector3D& operator-=(const Vector3D&);
    Vector3D& operator*=(double);
    Vector3D& operator/=(double);

    const Vector3D operator-() const;
    const Vector3D operator*(double) const;
    const Vector3D operator/(double) const;

    // Alternatives to .dot() and .cross() and .normalized()
    const double operator*(const Vector3D&) const;
    const Vector3D operator^(const Vector3D&) const;
    const Vector3D operator~() const;

    bool operator==(const Vector3D&) const;
    bool operator!=(const Vector3D&) const;

    // Methods
    double normSq() const;
    double norm() const;
    Vector3D& normalize();
    Vector3D normalized() const;
    double dot(const Vector3D&) const;
    Vector3D cross(const Vector3D&) const;
};


// External operator overloads
const Vector3D operator+(Vector3D, const Vector3D&);
const Vector3D operator-(Vector3D, const Vector3D&);
const Vector3D operator*(double, const Vector3D&);

// "Print"
std::ostream& operator<<(std::ostream&, const Vector3D&);
