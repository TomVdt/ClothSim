# Conception

## Vector3D

Nous avons crée une classe Vector3D avec les 3 coordonnées comme attributs et des méthodes publiques:

- les constructeurs

- des getters sur les attributs
- `norm()` et `normSq()` pour avoir la norme et son carré

- pour modifier cette instance du vecteur:
    - des setters sur les 3 attributs
    - `normalize()`
    - les surcharges d'opérateurs: `+=` et `-=` avec des vecteurs
    - les surcharges d'opérateurs: `*=` et `/=` avec des double

- `normalized()` renvoie ce vecteur normalisé sans le modifier

- les opérations classiques sur des vecteurs: 
    - `dot()` ou `*` et `cross()` ou `^`
    - `*` et `/` avec des double
    - `-` pour renvoyer l'opposé du vecteur


- la surcharge d'opérateurs `==` et `!=` pour tester les égalités

Exemples:
```c++
// Constructeurs
Vector3D vec1;                  // initialise au vecteur (0, 0, 0)
Vector3D vec2(2.0, 3.0, 4.0);   // donne (2.0, 3.0, 4.0)

// Informations sur le vecteur
vec2.getX();                    // renvoie 2.0
vec2.normSq();                  // renvoie ||vec2||² = 29.0
vec2.norm();                    // renvoie la norme donc ici sqrt(29.0)

// Modifications du vecteur
vec1.setX(2.0);                  // le vec1 devient (2.0, 0, 0)
vec.normalize();                 // normalise le vecteur vec
vec1 += vec2;                    // addition vectorielle donc vec1 = (4.0, 3.0, 4.0)
vec1 *= 2.0;                     // multiplication par un scalaire donc vec1 = (8.0, 6.0, 8.0)


Vector3D vec3(vec1.normalized()) // le vec3 est le vec1 normalisé, ne modifie pas vec1


// Opérations sur les vecteurs
double x(vec1 * vec2);           // produit scalaire de vec1 et vec2
Vector3D vec4(vec1 ^ vec2);      // produit vectoriel de vec1 et vec2
Vector3D vec5(5.0 * vec1);       // 5 fois le vec1
Vector3D vec6(-vec1);            // vec6 est l'opposé de vec1
```

L'addition et la soustraction de deux vecteurs sont aussi possibles par surcharge d'opérateurs.

```c++
Vector3D addition(vec1 + vec2);
Vector3D soustraction(vec1 - vec2);
```

Finalement il est possible d'envoyer les coordonnées dans un flot de sortie.

```c++
Vector3D vec(1.0, 4.2, 2.0);

cout << vec;                    // affiche (1.0 4.2 2.0)
```