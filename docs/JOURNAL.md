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

# Semaine 6

- Création de `EulerCromerIntegrator`
- Tests intégrateurs
- Visualisation et vérification de cohérence des tests avec `python` + `matplotlib`
- Classe `Tissu` simple
- Petits ajustements aux `Spring` et `Masse`
