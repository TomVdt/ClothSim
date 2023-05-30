#pragma once

#include <iostream>
// Pour la conversion Vector3D -> glm::vec3
#include <glm/vec3.hpp>


class Vector3D {
private:
    /**
     * Composantes du vecteur selon les 3 axes
    */
    double x, y, z;

public:
    /**
     * Constructeur par défaut créant le vecteur nul
    */
    constexpr Vector3D(): x(0.0), y(0.0), z(0.0) {}

    /**
     * Constructeur prenant les trois coordonnées d'un vecteur: x,y,z
    */
    constexpr Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}


    /**
     * Coordonnée x du vecteur
    */
    double getX() const { return x; }

    /**
     * Coordonnée y du vecteur
    */
    double getY() const { return y; }

    /**
     * Coordonnée z du vecteur
    */
    double getZ() const { return z; }


    /**
     * Change la coordonnée x du vecteur
    */
    void setX(double x_) { x = x_; }

    /**
     * Change la coordonnée y du vecteur
    */
    void setY(double y_) { y = y_; }

    /**
     * Change la coordonnée z du vecteur
    */
    void setZ(double z_) { z = z_; }


    /**
     * Surcharge interne de l'opérateur += avec un vecteur à 3 dimensions
    */
    Vector3D& operator+=(const Vector3D&);

    /**
     * Surcharge interne de l'opérateur -= avec un vecteur à 3 dimensions
    */
    Vector3D& operator-=(const Vector3D&);

    /**
     * Surcharge interne de l'opérateur *= avec un double
    */
    Vector3D& operator*=(double);

    /**
     * Surcharge interne de l'opérateur /= avec un double
    */
    Vector3D& operator/=(double);


    /**
     * Surcharge d'opérateur qui retourne le produit scalaire entre ce vecteur et celui fourni
    */
    double operator*(const Vector3D&) const;

    /**
     * Surcharge d'opérateur qui retourne le produit vectoriel entre ce vecteur et celui fourni
    */
    Vector3D operator^(const Vector3D&) const;

    /**
     * Surcharge d'opérateur qui retourne une copie de ce vecteur normalisé
    */
    Vector3D operator~() const;


    /**
     * Surcharge de l'opérateur qui teste les égalités entre vecteurs
    */
    bool operator==(const Vector3D&) const;

    /**
     * Surcharge de l'opérateur testant l'inégalité entre vecteurs
    */
    bool operator!=(const Vector3D&) const;


    /**
     * Retourne la norme au carré du vecteur
    */
    double normSq() const;

    /**
     * Retourne la norme du vecteur
    */
    double norm() const;

    /**
     * Normalise le vecteur
    */
    Vector3D& normalize();

    /**
     * Renvoie une copie du vecteur normalisée
    */
    Vector3D normalized() const;

    /**
     * Renvoie le produit scalaire entre ce vecteur et celui fourni
    */
    double dot(const Vector3D&) const;

    /**
     * Renvoie le produit vectoriel entre ce vecteur et celui fourni
    */
    Vector3D cross(const Vector3D&) const;

    /**
     * Tourne le vecteur selon un angle et une normale
    */
    Vector3D& rotate(double, const Vector3D&);

    /**
     * Renvoie une copie du vecteur tournée selon un angle et une normale
    */
    Vector3D rotated(double, const Vector3D&) const;


    /**
     * La distance entre deux vecteurs
    */
    static double dist(const Vector3D&, const Vector3D&);

    /**
     * Le produit vectoriel entre deux vecteurs
    */
    static Vector3D cross(const Vector3D&, const Vector3D&);

    /**
     * Le produit scalaire entre deux vecteurs
    */
    static double dot(const Vector3D&, const Vector3D&);

    /**
     * Transforme ce vecteur en vecteur utilisé pour le graphisme de glm
    */
    glm::vec3 toGlmVec3() const;
};


/**
 * Surcharge externe de l'opérateur + entre vecteurs à 3 dimensions
*/
Vector3D operator+(Vector3D, const Vector3D&);

/**
 * Surcharge externe de l'opérateur - renvoyant l'opposé d'un vecteur
*/
Vector3D operator-(Vector3D);

/**
 * Surcharge externe de l'opérateur - entre vecteurs à 3 dimensions
*/
Vector3D operator-(Vector3D, const Vector3D&);

/**
 * Surcharge externe de l'opérateur * entre un vecteur à 3 dimensions et un double
*/
Vector3D operator*(Vector3D, double);

/**
 * Surcharge externe de l'opérateur * entre un double et un vecteur à 3 dimensions
*/
Vector3D operator*(double, const Vector3D&);

/**
 * Surcharge externe de l'opérateur / entre un vecteur à 3 dimensions et un double
*/
Vector3D operator/(Vector3D, double);


/**
 * Surcharge externe de l'opérateur << afin d'afficher un Vector3D dans un flot
*/
std::ostream& operator<<(std::ostream&, const Vector3D&);
