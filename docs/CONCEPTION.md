# Conception

La hierarchie de classes peut être vue dans la documentation générée par doxygen, sous "Classes > Class Hierarchy"

## Vector3D

Voici comment utiliser nos `Vector3D`

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

## Tissus simples

Contrairement à ce qui avait été conseillé, nous avons choisi de rajouter les masses après avoir construit le tissu.
Cela ne pose pas de problème avec notre moyen de stocker les masses, et nous trouvons que cela rend les tissus plus agréable à construire à la main, plutot que de passer un vecteur d'arguments permettant de tout contruire au départ, ce qui ne montre pas clairement ce que fait le constructeur et permet beaucoup d'erreurs.
Les masses sont construites à l'interieur du tissu, implémenté à l'aide de `std::forward` (https://en.cppreference.com/w/cpp/utility/forward).
Les connections se font par la méthode `Cloth::connect()`.
La validité du tissu peut être vérifiée avec `Cloth::check()`.
Les tissus possèdent les masses et ressorts qu'ils contiennent.

## Tissus composés

Pour implémenter nos `CompositeCloth` sans briser l'encapsulation, nous avons utilisé une méthode de transfert de possession des masses et ressorts.
Les tissus peuvent par la méthode `Cloth::giveGutsTo(Cloth&)` donner toutes leurs masses et ressorts (avec un std::move()) au tissu donné, en appelant la méthode (virtuelle) protected `Cloth::lootCorpse()` sur le tissu donné, qui combine alors les deux listes.
Pour les tissus composés, il suffit donc de, pour connecter un tissu, d'appeler la méthode `Cloth::giveGutsTo()` sur le tissu donné et d'override la méthode `Cloth::lootCorpse()` pour effectuer les nouvelles connections

## Contraintes

Pour toutes nos `Constraint`, nous avons opté d'utiliser un double-dispatch sur le tissu donné à la méthode `Constraint::apply(Cloth&)`.
La méthode appelle une méthode sur le tissu `Cloth::applyConstraint()`, qui va elle va appliquer les contraintes sur toutes les masses avec `Constraint::apply(Mass&, )`. La méthode `Cloth::applyConstraint()` d'appliquer une contrainte non enregistrée dans la liste des contraintes des masse.
Cela permet de maintenir une bonne encapsulation en évitant un getter sur les masses.
Lors de l'ajout d'une contrainte au système, la contrainte va être rajoutée à toutes les masses concernées par son champ d'action. Elles sont appliquées par la méthode `Mass::applyConstraints()`.

Nos `ImpulsionConstraint` utilisent pour mémoriser à quelles masses elles doivent s'appliquer une liste d'identifiant unique pour toutes les masses concernées, sans enregistrer leur addresse, ce qui briserait l'encapsulation.
Pour ce faire, nous attribuons automatiquement à chaque masse un entier unique, accessible en lecture seule depuis l'exterieur. Les tissus possèdent une méthode `Cloth::getMassIdsInRange()` qui, comme le nom l'indique, permet d'obtenir tous les identifiants des masses dans un certain rayon. Les contraintes enregistrent donc cette liste, pour chacun des tissus donnés.

Nous avons aussi rendu nos contraintes dessinables, pour mieux voir sur quelles masses elles agissent, et parce que nous pouvions le faire ¯\\\_(ツ)\_/¯.

## Util et exceptions

Pour des fonctions utilisées de partout dans le projet, le fichier `util.h` définit une classe `indent` qui permet tout simplement d'indenter une sortie dans un flot, pour rendre l'affichage plus agréable et mieux séparer les objets.
Un macro `UNUSED` y est aussi définit et permet d'enlever les warnings "unused argument"

Nous avons aussi implémenté un système d'exceptions avec différents types et messages possibles.
Les noms des types d'erreurs sont fortement inspirés du python.
Un macro `ERROR` permet de spécifier le type d'erreur à envoyer et les message, et complète automatiquement les contructeurs des erreurs avec le fichier et la ligne où l'erreur s'est produite.
