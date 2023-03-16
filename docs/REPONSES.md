# Réponses

## Exercice 1

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

Pour l'instant, aucune méthode privée n'est nécessaire.
