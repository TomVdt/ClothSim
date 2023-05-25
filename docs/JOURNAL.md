# Journal

## Semaine 1

- Prise de connaissance du projet

## Semaine 2

- Prototypage classe `Vector3D`
- Implémentation classe `Vector3D`
- Tests pour `Vector3D`
- Écriture d'un macro pour faciliter les tests pour l'instant
- Écriture d'un `Makefile`

## Semaine 3

- Refactoring de `Vector3D`
- Rajout de l'opérateur `~` (unitaire)
- `Vector3D::normalize()` retourne une réference sur l'instance
- Rajout de tests pour `Vector3D`
- Tentative ratée de refaire la méthode de tests (enlever macros)
- Documentation de `Vector3D`
- Refonte du `Makefile`: nouvelles cibles `run_tests`, `build`, réécriture des autres cibles
- Fichier pour les constantes `constants.cpp`, déplacement de `EPSILON` du `vector3d.h`

## Semaine 4

- Début de création de `Masse`
- Début de création de `Spring`
- Correction de bugs dans `Vector3D`
- Beaucoup, beaucoup de lecture de documentation de Qt5
- Début de travail sur la partie graphique (fenetre, 3d, caméra)

## Semaine 5

- Documentation `Masse`
- Documentation `Spring`
- Tests `Masse`
- Tests `Spring`
- Début des `Integrator`

## Semaine 6

- Création de `EulerCromerIntegrator`
- Tests intégrateurs
- Visualisation et vérification de cohérence des tests avec `python` + `matplotlib`
- Classe `Cloth` simple
- Petits ajustements aux `Spring` et `Masse`

## Semaine 7

- Fin des tests intégrateurs
- Finir classe `Cloth`
- Création des exceptions dans `exceptions.h`
- Refactoring
- Nouveau `Makefile`
- Exercice P9

## Semaine 7.5

- Tests tissus
- Changement de `constants.h`
- Plus de refactoring
- Réglage des segfault
- Finir QT
- Détruire QT
- Amitié finie avec QT maintenant imgui c'est mon meilleur copain

## Semaine 8

- Classes `System`, `Drawable`, `Renderer`
- Nouveau `Makefile`
- Exam yolo

## Semaine 9

- R E F A C T O R I N G  <sub>trois</sub> : `Cloth`, `Masse`, `Spring`...
- Test du graphisme sur les VMs: ultramegastonks
- Exercice P10

## Semaine 10

- Dessin des `Spring`
- Cleanup du code
- Exercice P13
- Première tentative d'implémentation de RK4: très instable

## Semaine 11

- Ajout dynamique des tissus et des contraintes dans la simulation
- Petites améliorations dans la conception
- Un peu d'optimisation

## Semaine 12

- Modification de l'implémentation des intégrateurs, RK4 toujours instable
- Amélioration du graphisme et de l'interface d'utilisation (flag de compilation AZERTY)
- Le `main.cpp` créé le `System` désormais et le donne à `window.cpp`
- Corrections diverses
- Noms de variables plus cohérents

## Semaine 13

- Troisième implémentation des intégrateurs: RK4 et Newmark stables et fonctionnels
- Modification dynamique du paramètre de convergence `epsilon` de l'intégrateur de Newmark
- Nouvelle conception des contraintes
- Début du nettoyage du code