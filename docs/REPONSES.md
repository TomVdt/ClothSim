# Réponses

## P1

> Comment représentez-vous ces vecteurs ? Comment sont-ils organisés : quels attributs ? quelles méthodes ? quels droits d'accès ?

Les vecteurs sont représentés avec 3 `double` privés `x`, `y` et `z`. Ce sont les seuls attributs de la classe.
Nous aurions bien sur aussi pu utiliser un array de taille 3 (`std::array` ou array à la C), mais notre choix semble plus naturel et plus ergonomique à utiliser.
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

Nous n'avons pas rajouté de constructeur de copie car la copie par défaut (copie de surface) suffit, nous n'avons pas d'allocation dynamique.

> Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur)
> 1. que cela impliquerait-il au niveau des attributs de la classe ?
> 2. quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ? (C'est d'ailleurs pour cela qu'on ne vous demande pas de faire un tel constructeur !)

On pourrait envisager de convertir les coordonnées sphériques en coordonnées cartésiennes dans un nouveau constructeur (ou à travers une méthode statique, pour différencier du constructeur `x`, `y`, `z`), et continuer à utiliser le vecteur comme un vecteur en coordonnées cartésiennes.

On pourrait aussi rajouter des attributs (privés) `rho`, `theta` et `r` que nous devrons mettre à jour à chaque changement dans le vecteur, ce qui peut être très coûteux en calculs. Alternativement, nous pourrions rajouter uniquement des getters qui calculent `rho`, `theta` et `r` quand on en a besoin, à l'aide des fonctions trigonométriques (coûteux en calcul!).

Cependant, si nous voulions majoritairement utiliser les vecteurs avec la représentation en coordonnées sphériques, il serait préférable de créer une classe `Vector3D` qui manipule des coordonnées sphériques, au coût de temps de calcul pour convertir en coordonnées cartésiennes si nécessaire.

Pour notre utilisation des vecteurs, les `Vector3D` en coordonnées cartésiennes sont préférables, car on a surtout des mouvements de translation et non de rotation.

> Quels opérateurs avez vous introduits ?

Nous avons introduit les opérateurs `<<` et `==` pour faire le role de `affiche` et `compare`, ainsi que d'autre opérateurs, qui sont documentés dans `CONCEPTION.md` (en résumé: opérateurs arithmétiques, normalisation `~`, produit scalaire et vectoriel).

## P5

> Comment avez-vous implémenté l'ensemble de ressorts ?

L'ensemble de ressorts est un `vector<const Spring*>`. On utilise des `Spring*`, pointeurs "a la C" vers des `Spring` et non des `unique_ptr` car un ressort connecte 2 masses ensemble, qui doivent chacune garder une référence vers leurs ressorts. On ne peut pas utiliser de références par limitation de la classe `vector`. Une autre option serait d'utiliser des `shared_ptr` mais ils pourraient poser des problèmes de référence circulaire entre `Spring` et `Masse`, même s'ils simplifiraient la gestion de mémoire.
On utilise des `const` pointeurs car il ne revient pas à la masse de modifier les ressorts, cela sera fait au niveau du tissu.

## P7

> Comment avez vous conçu votre classe `Integrateur` ?

La classe `Integrator` est une classe abstraite. Elle contient seulement une méthode virtuelle pure publique `integrate` qui prend une référence à une `Masse` et un `dt` comme pas de temps afin de mettre à jour la position de la masse (avec cette méthode redéfinie dans les sous-classe).

> Quelle est la relation entre les classes `Integrateur` et `IntegrateurEulerCromer` ?

`EulerCromerIntegrator` "est un" `Integrator`, c'est à dire qu'il hérite des méthodes d'`Integrator`. Cette relation d'héritage avec `Integrator` comme super-classe permettra du polymorphisme entre les différents intégrateurs qui pourront être implémentés plus tard.

Nous définissons la méthode `integrate` pour `EulerCromerIntegrator` afin que ça ne soit plus une classe abstraite mais bien un intégrateur fonctionnel.

## P8

> Lesquelles des méthodes précédentes avez-vous implémentées ? Les avez-vous mises en public ou private ? Précisez pour chacune et expliquez pourquoi.

Nous avons choisi de ne pas implémenter un constructeur recevant une liste de masses car dans notre conception les masses appartiennent au tissu et il ne revient pas à l'utilisateur de s'en occuper. Il n'y a donc pour les tissus simples qu'un constructeur par défaut initialisant les listes de masses et ressorts à des listes vides et il faut y rajouter des masses à l'aide de la méthode `addMass()`. Pour les tissus plus complexes, les constructeurs se chargeront de créer les masses nécessaires selon les caractéristiques du tissu.

La méthode `connect()` alloue un nouvel emplacement mémoire pour un ressort connecté aux deux masses dont l'indice est passé en argument. C'est une méthode publique pour permettre à l'utilisateur de créer des liens dans le tissu (après avoir fourni les masses).

Notre implémentation garanti que les deux masses correspondantes sont connectées à chaque ressort quand il est crée au sein du tissu donc une méthode connecteMasse() ne nous serait pas utile.

La méthode publique `check()` permet de vérifier la cohérence du ressort, elle doit donc être disponible à l'utilisateur.

## P9

> En termes de POO, quelle est donc la nature de la méthode `dessine_sur()` ? 

Notre méthode `draw()` est une méthode virtuelle pure, rendant la classe `Drawable` abstraite

> Comment représentez vous la classe `Systeme` ?

La classe `System` contient 3 attributs privés:
- Un tableau dynamique de `unique_ptr<Cloth>` pour permettre une collection hétérogène de différents tissus plus tard dans le projet. Les tissus appartiennent au système qui est seul à s'occuper de leur évolution ce qui explique l'utilisation de `unique_ptr`.
- Un tableau dynamique de `unique_ptr<Constraint>` pour les même raisons
- Un `time` nécessaire à la bonne application des contraintes

Le système est donc l'ensemble des éléments physiques de la simulation.

Pour les méthodes nous avons implémenté:
- `getTime()` et `energy()` qui servent pour l'affichage des caractéristiques du système
- `addCloth()`, `addConstraint()` et `clear()` qui servent à gérer le contenu du système
- La méthode `draw`, nécessaire à implémenter avec `Drawable` ainsi que la méthode `drawContents()` qui fait appel aux méthodes `draw()` des différents éléments du système
- `display` pour la représentation en format texte (utilisé dans la surcharge de `<<` pour `ostream`)
- Une méthode `step()` qui fait évoluer le système en recevant un intégrateur et un pas de temps. Cela permet de faire évoluer numériquement tout le système physique.

Ainsi un `System` contient tous les éléments physiques et reçoit les informations nécessaires pour le faire évoluer selon ce que l'utilisateur souhaite.

## P14

> Où cela s'intègre-t-il dans votre projet/conception ? Quels changements cela engendre-t-il (ou pas) ?

Nous allons créer deux nouvelles sous-classe de `Integrator` pour lesquelles il faudra redéfinir la méthode virtuelle `integrate` avec les formules correspondantes. 

Le polymorphisme permet une compatibilités entre ces nouveaux intégrateurs et notre conception jusqu'ici. Cependant comme ces nouveaux intégrateurs nécessitent de pouvoir calculer des accélérations intermédiaires nous avons dû modifier légèrement notre implémentation:
- Surcharger la méthode `acceleration` des masses afin qu'elle puisse prendre un temps, une position et une vitesse. Elle calcule l'accélération correspondante à ces paramètres sans modifier la masse elle-même (hors de la méthode).
- Rajouter une variable `time` à la méthode `integrate` dans la classe abstraite `Integrator` et toutes ses sous-classes (cette variable n'est pas utilisée par Euler-Cromer) afin de pouvoir la fournir à la nouvelle méthode `acceleration`.

Ainsi nous pouvons à l'aide du polymorphisme changer dynamiquement l'intégrateur utilisé pour faire évoluer le système.
