#pragma once
#include <iostream>  // for std::ostream
#include <glm/vec3.hpp>

class Vector3D {
private:
    double x, y, z;

public:
    // Constructors
    constexpr Vector3D(): x(0.0), y(0.0), z(0.0) {}
    constexpr Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setters
    void setX(double x_) { x = x_; }
    void setY(double y_) { y = y_; }
    void setZ(double z_) { z = z_; }

    // Internal operator overloading
    Vector3D& operator+=(const Vector3D&);
    Vector3D& operator-=(const Vector3D&);
    Vector3D& operator*=(double);
    Vector3D& operator/=(double);


    // Alternatives to .dot() and .cross() and .normalized()
    double operator*(const Vector3D&) const;
    Vector3D operator^(const Vector3D&) const;
    Vector3D operator~() const;

    bool operator==(const Vector3D&) const;
    bool operator!=(const Vector3D&) const;

    // Methods
    double normSq() const;
    double norm() const;
    Vector3D& normalize();
    Vector3D normalized() const;
    double dot(const Vector3D&) const;
    Vector3D cross(const Vector3D&) const;

    Vector3D& rotate(double, const Vector3D&);
    Vector3D rotated(double, const Vector3D&) const;

    static double dist(const Vector3D&, const Vector3D&);
    static Vector3D cross(const Vector3D&, const Vector3D&);
    static double dot(const Vector3D&, const Vector3D&);

    glm::vec3 toGlmVec3() const;
};


// External operator overloads
Vector3D operator+(Vector3D, const Vector3D&);
Vector3D operator-(Vector3D);
Vector3D operator-(Vector3D, const Vector3D&);
Vector3D operator*(Vector3D, double);
Vector3D operator*(double, const Vector3D&);
Vector3D operator/(Vector3D, double);

// "Print"
std::ostream& operator<<(std::ostream&, const Vector3D&);
