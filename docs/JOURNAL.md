# Journal

## Semaine 1

- Prise de connaissance du projet

## Semaine 2

- Prototypage classe `Vector3D`
- Implémentation classe `Vector3D`
- Mise en place d'un système de test général
- Tests pour `Vector3D`
- Écriture d'un premier `Makefile`

## Semaine 3

- Refactoring de `Vector3D`
- Nouvelles méthodes et opérateurs pour le calcul de `Vector3D`
- Rajout de tests supplémentaires pour `Vector3D`
- Documentation de `Vector3D`
- Refonte du `Makefile`: meilleure gestion des cibles
- Gestion des constantes nécessaires au projet

## Semaine 4

- Début de l'implémentation de la classe `Mass`
- Début de l'implémentation de la classe `Spring`
- Correction de bugs dans `Vector3D`
- Lecture de documentations de Qt5
- Début de travail sur la partie graphique (fenetre, 3d, caméra)

## Semaine 5

- Documentation de `Mass`
- Documentation de `Spring`
- Tests de `Mass`
- Tests de `Spring`
- Début des `Integrator`

## Semaine 6

- Création de `EulerCromerIntegrator`
- Tests intégrateurs
- Visualisation et vérification de cohérence des tests avec `python` + `matplotlib`
- Classe `Cloth` simple
- Petits ajustements aux `Spring` et `Mass`

## Semaine 7

- Fin des tests intégrateurs
- Finition de la classe `Cloth`
- Gestion des erreurs à l'aide d'un `exceptions.h`
- Refactoring divers
- Nouveau `Makefile`
- Exercice P9

## Semaine 7.5 - vacances

- Tests tissus
- Changement dans la gestion des constantes
- Plus de refactoring
- Réglage des segfault
- Faire fonctionner QT
- Détruire QT
- Amitié finie avec QT maintenant imgui est mon meilleur ami

## Semaine 8

- Classes `System`, `Drawable`, `Renderer`
- Nouveau `Makefile`
- Examen du milieu de semestre

## Semaine 9

- REFACTORING  <sub>trois</sub> : `Cloth`, `Mass`, `Spring`...
- Test du graphisme sur les VMs: ça fonctionne
- Exercice P10
- Exercice P11
- Début des tissus complexes

## Semaine 10

- Dessin des `Spring`
- Cleanup du code
- Finition des tissus complexes
- Exercice P13
- Première tentative d'implémentation de RK4: très instable

## Semaine 11

- Ajout dynamique des tissus et des contraintes dans la simulation
- Petites améliorations dans la conception: meilleure encapsulation
- Correction d'une petite faute dans les abstractions OpenGL

## Semaine 12

- Modification de l'implémentation des intégrateurs, RK4 toujours instable
- Amélioration du graphisme et de l'interface d'utilisation (flag de compilation AZERTY)
- Changement dans la gestion des `System` dans la conception
- Corrections diverses
- Noms de variables plus cohérents
- Amélioration du système d'erreur

## Semaine 13

- Troisième implémentation des intégrateurs: RK4 et Newmark stables et fonctionnels
- Rectification d'erreurs d'intégration
- Modification dynamique du paramètre de convergence `epsilon` de l'intégrateur de Newmark
- Nouvelle conception des contraintes et rajout de la contrainte `AttractionConstraint`
- Création d'une TODOList pour la fin du projet (nettoyage, finalisation de la conception, readme ...)
- Début du nettoyage final du code
- Amélioration du système de tests et rajouts de tests manquants
- Gestion des warnings
- Documentation extensive, exhaustive et exténuante

## Semaine 14

- Réorganisation de la structure du projet pour le rendu
- Fin de la documentation du code
- Fin du nettoyage du code
- Ecriture finale de la conception
- Correction de tests
- Tests finis
- Dernières petites révisions aux tissus
- Vérification de la compilation sur les VMs (ca compile!)
- Écriture du README