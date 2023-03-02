#pragma once
#include <iostream>  // for std::ostream

class Vector3D {
private:
    double x, y, z;

public:
    // Constructors
    Vector3D();
    Vector3D(double, double, double);
    Vector3D(const Vector3D&);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(double);
    void setY(double);
    void setZ(double);

    // Internal operator overloading
    Vector3D& operator+=(const Vector3D&);
    Vector3D& operator-=(const Vector3D&);
    Vector3D& operator*=(double);
    Vector3D& operator/=(double);

    const Vector3D operator*(double);
    const Vector3D operator/(double);
    const Vector3D operator-();

    bool operator==(const Vector3D&) const;
    bool operator!=(const Vector3D&) const;

    // Methods
    double norm() const;
    double normSq() const;
    Vector3D normalize();
    double dot(const Vector3D&) const;
    Vector3D cross(const Vector3D&) const;
};


// External operator overloads
const Vector3D operator+(Vector3D, const Vector3D&);
const Vector3D operator-(Vector3D, const Vector3D&);
const Vector3D operator*(double, const Vector3D&);
const Vector3D operator/(double, const Vector3D&);

// "Print"
std::ostream& operator<<(std::ostream, const Vector3D&);
