# Réponses

## P1

> Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?

Les vecteurs sont représentés avec 3 `double` privés `x`, `y` et `z`. Ce sont les seuls attributs de la classe.
Nous aurions bien sur aussi pu utiliser un array de taille 3 (`std::array` ou array à la C), mais notre choix semble plus naturel, plus performant et plus ergonomique à utiliser.
Utiliser un array serait probablement mieux si nous voulions pouvoir étendre la classe à N-dimensions.

Nous avons des méthodes publiques:
- Getters / setters pour les attributs `x`, `y` et `z`
- Produit scalaire et vectoriel, méthodes généralement utiles pour les vecteurs (surtout pour la 3D)
- Norme et norme²
- `normalize` pour normaliser le vecteur _en place_, `normalized` pour _créer un nouveau vecteur_ normalisé
- Surcharge d'opérateurs entre vecteurs `+=`, `-=`, `==`, `!=` et entre vecteur et double (changer la norme du vecteur) `/=`, `*=`, `*`, `/` ainsi que l'opposé d'un vecteur `-`.
- Deux constructeurs: le constructeur par défaut qui fixe les coordonnées à 0 et un constructeur prenant les 3 coordonnées du vecteur

  Cela facilitera l'utilisation de ces vecteurs

Aucune méthode privée n'est nécessaire pour nous.

## P4

> 	Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?

Nous n'avons pasa rajouté de constructeur de copie car la copie par défaut (copie de surface) suffit, nous n'avons pas d'allocation dynamique.

> Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur)
> 1. que cela impliquerait-il au niveau des attributs de la classe ?
> 2. quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ? (C'est d'ailleurs pour cela qu'on ne vous demande pas de faire un tel constructeur !)

On pourrait envisager de convertir les coordonnées sphériques en coordonnées cartésiennes dans un nouveau constructeur (ou à travers une méthode statique, pour différencier du constructeur `x`, `y`, `z`), et continuer à utiliser le vecteur comme un vecteur en coordonnées cartésiennes.

On pourrait aussi rajouter des attributs (privés) `rho`, `theta` et `r` que nous devrons mettre à jour à chaque changement dans le vecteur, ce qui peut être très couteux en calculs. Alternativement, nous pourrions rajouter uniquement des getters qui calculent `rho`, `theta` et `r` quand on en a besoin, à l'aide des fonctions trigonométriques (couteux en calcul!).

Cependant, si nous voulions majoritairement utiliser les vecteurs avec la représentation en coordonnées sphériques, il serait préférable de créer une classe `Vector3D` qui manipule des coordonnées sphériques, au cout de temps de calcul pour convertir en coordonnées cartésiennes, si nécessaire.

Pour notre utilisation des vecteurs, les `Vector3D` en coordonnées cartésiennes sont préférables, car on a surtout des mouvements de translation et non de rotation.

> Quels opérateurs avez vous introduits ?

Nous avons introduit les opérateurs `<<` et `==` pour faire le role de `affiche` et `compare`, ainsi que d'autre opérateurs, qui sont documentés dans `CONCEPTION.md` (en résumé: opérateurs arithmétiques, normalisation `~`, produit scalaire et vectoriel).

## P5

> Comment avez-vous implémenté l'ensemble de ressorts ?

L'ensemble de ressorts est un `vector<Spring*>`. On utilise des `Spring*`, pointeurs "a la C" vers des `Spring`s et non des `unique_ptr` car un ressort connecte 2 masses ensemble, qui doivent chacun garder une référence vers leurs ressorts. On ne peut pas utiliser de références par limitation de la classe `vector`. Une autre option serait d'utiliser des `shared_ptr` mais ils pourraient poser des problèmes de référence circulaire entre `Spring` et `Masse`, même s'ils simplifiraient la gestion de mémoire.

## P7

> Comment avez vous conçu votre classe `Integrateur` ?

La classe `Integrator` est une classe abstraite. Elle contient juste une méthode virtuelle pure publique `integrate` qui prend un pointeur sur une `Masse` et un `dt`.

> Quelle est la relation entre les classes `Integrateur` et `IntegrateurEulerCromer` ?

`EulerCromerIntegrator` "est-un" `Integrator`, c'est à dire qu'il hérite en public les méthodes d'`Integrator`.

## P8

> Lesquelles des méthodes précédentes avez-vous implémentées ? Les avez-vous mises en public ou private ? Précisez pour chacune et expliquez pourquoi.

Nous avons suivi les conseils pour le constructeur qui reçoit une liste de pointeurs vers des masses.

La méthode `connect()` alloue un nouvel emplacement mémoire pour un ressort connecté aux deux masses passées en argument. C'est une méthode publique pour permettre à l'utilisateur de créer les liens dans le tissu (après avoir fourni dans le constructeur les masses du tissu).

Notre implémentation garanti que les deux masses correspondantes sont connectées à chque ressort quand il est crée donc une méthode connecteMasse() ne nous serait pas utile.

La méthode publique `check()` permet de vérifier la cohérence du ressort, elle doit donc être disponible à l'utilisateur.

## P9

> En termes de POO, quelle est donc la nature de la méthode `dessine_sur()` ? 

Notre méthode `draw()` est une méthode virtuelle pure, rendant la classe `Drawable` abstraite

> Comment représentez vous la classe `Systeme` ?

La classe `System` contient 2 attributs privés:
- Un tableau dynamique de `Cloth*` pour permettre une collection hétérogène de différents tissus plus tard dans le projet
- Un `Integrator*`, pour permettre du polymorphisme (plusieurs types d'intégrateurs, changeable au temps de l'execution)

Pour les méthodes nous avons implémenté:
- La méthode `draw`, nécessaire à implémenter avec `Drawable`
- `display` pour la représentation en format texte (utilisé dans la surcharge de `<<` pour `ostream`)

Nous avons aussi un destructeur (virtuel) pour libérer les ressources allouées (`Cloth` et `Integrator`)
