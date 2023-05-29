#pragma once
#include "include/drawable.h"
#include "include/vector3d.h"

#include <iostream>
#include <vector>

class Spring;
class Constraint;

class Masse: public Drawable {
private:
    /**
     * Valeur de la masse de cette instance
    */
    double mass;

    /**
     * Valeur du coefficient de frottement pour cette masse
    */
    double lambda;

    /**
     * Vecteur position de la masse
    */
    Vector3D pos;

    /**
     * Vecteur vitesse de la masse
    */
    Vector3D vel;

    /**
     * Vecteur de la somme des forces sur la masse
    */
    Vector3D force;

    /**
     * Liste de tous les ressorts connectés à cette masse
     * Ce sont des pointeurs constants car il ne revient pas à la masse de les modifier
    */
    std::vector<const Spring*> springs;

    /**
     * Liste de toutes les contraintes qui peuvent concerner cette masse
     * (les contraintes du tissu auquel elle appartient généralement)
     * Ce sont des pointeurs constants car il ne revient pas à la masse de les modiifier
    */
    std::vector<const Constraint*> constraints;

    /**
     * Identificateur unique de la masse à partir de la variable de classe COUNT
    */
    const int id;

    /**
     * Variable de classe permettant de donner des identificateurs uniques aux masses 
     * en comptant le nombre de masses crées
    */
    static int COUNT;

public:
    /** 
     * Constructeur masse nécesssaire ensuite lambda, pos et vel peuvent etre par defaut
     * N'est pas propriétaire des springs
    */
    Masse(double mass, double lambda = 0.0, const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D());
    
    /**
     * Pas de copie de masse: à quels ressorts connecter? 
    */
    Masse(const Masse&) = delete;

    /**
     * Pas de copie de masse: à quels ressorts connecter? 
    */
    Masse& operator=(const Masse&) = delete;

    /** 
     * Possible de déplacer les masses
    */
    Masse(Masse&&) = default;

    /** 
     * Possible de déplacer les masses
    */
    Masse& operator=(Masse&&) = default;

    /**
     * Destructeur par défaut pour les masses
    */
    virtual ~Masse() = default;

    /**
     * Vecteur position de la masse
    */
    const Vector3D& getPos() const { return pos; }

    /** 
     * Vecteur vitesse de la masse
    */
    const Vector3D& getVel() const { return vel; }
    
    /** 
     * Vecteur de la force actuelle sur la masse
    */
    const Vector3D& getForce() const { return force; }
    
    /** 
     * Renvoie la valeur de la masse de cette instance 
    */
    double getMass() const { return mass; }
    
    /** 
     * Coefficient de frottement
    */
    double getLambda() const { return lambda; }

    /**
     * Identifiant unique de la masse
    */
    int getId() const { return id; }

    /**
     * Modifie la position de la masse
    */
    void setPos(const Vector3D& vec) { pos = vec; }
    
    /** 
     * Modifie la vitesse de la masse
    */
    void setVel(const Vector3D& vec) { vel = vec; }

    /** 
     * Vecteur accélération de la masse
    */
    Vector3D acceleration() const;

    /**
     * Fonction de l'accélération en fonction du temps, position et vitesse (pour les intégrateurs)
    */
    Vector3D acceleration(double time, const Vector3D& p, const Vector3D& v);

    /**
     * Energie mécanique de la masse
    */
    double energy() const;

    /**
     * Rajoute une contrainte à la masse
    */
    void addConstraint(const Constraint& constraint);
    
    /**
     * Supprime toutes les contraintes sur la masse
    */
    void clearConstraints();

    /**
     * Modifie la force en fonction de la contrainte fournie
    */
    void applyConstraint(const Constraint& constraint, double time);

    /**
     * Modifie la force en fonction des contraintes sur la masse
    */
    void applyConstraints(double time);

    /** 
     * Rajoute une force à cette masse 
    */
    void addForce(const Vector3D& df);

    /** 
     * Met à jour la force sur la masse avec
     * mg, -lambda*v et la somme des forces de rappel 
    */
    void updateForce();

    /** 
     * Connecte un nouveau ressort à la masse en 
     * vérifiant s'il n'est pas déjà connecté 
    */
    void connectSpring(Spring& spring);

    /** 
     * Déconnecte la masse du ressort donné 
    */
    void disconnectSpring(const Spring& spring);
    
    /** 
     * Déconnecte tous les ressorts 
    */
    void disconnect();

    /** 
     * Vérifie si le ressort est connecté 
    */
    bool springConnected(const Spring& spring) const;

    /**
     * Redéfinition de draw pour afficher la masse dans le renderer
    */
    virtual void draw(Renderer& dest) override;

    /** 
     * Représentation de la masse dans un flot 
    */
    void display(std::ostream& out, size_t level = 0) const;
};

/** 
 * Surcharge externe de l'opérateur << pour les masses 
*/
std::ostream& operator<<(std::ostream& out, const Masse& mass);