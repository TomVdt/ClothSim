# Graphisme

## Pourquoi ne pas avoir utilisé Qt5?

Nous avons choisi très vite après le début du graphisme de ne pas utiliser Qt5, pour plusieurs raisons.

- Les entrées clavier et souris n'étaient vraiment pas pratiques à utiliser
- Le temps de compilation était très, très long
- C'est une vielle librairie (surtout sur les VMs...), et nous voulions tester quelque chose de nouveau, plus configurable
- La difficulté de contrôler les paramêtre de la simulation: quel est l'interet de faire une simulation si on ne peut pas bidouiller avec tous les petits paramètres :p ?

À la place, nous utilisons GLFW pour la fenêtre, glew pour OpenGL et Dear ImGui (la raison principale du changement) pour l'interface.

Ce changement nous a permis d'implémenter avec une grande facilité

- Un menu pour controler les paramêtres de la simulation
- Une interaction clavier-souris fluide
- L'ajout dynamique de tissus et contraintes
- L'affichage de l'énergie en environ 10 lignes de code
- Le changement dynamique d'intégrateurs
- Des informations relatives à la simulation et la fenetre
- Un temps de compilation TOTAL (application + tests + exercices + documentation) d'environ 25s avec clang, contrairement à la minute que prenait Qt

Nous avons aussi pu garder notre Makefile au lieu de passer à des .pro, ce qui nous permet d'avoir un fichier centralisé qui compile tout.

Avec Qt, nous aurions mis beaucoup plus de temps à implémenter ces fonctionnalités que le temps que nous avons pris pour effectuer la transition Qt -> GLFW + ImGui

Le menu permet aussi une plus grande clarté qu'une combinaison obscure de touches.

Cependant, nous n'avons pas accès aux abstractions de OpenGL qui sont données par Qt, nous avons donc réimplémenté une abstraction dans le même style que celle de Qt (pour pouvoir réutiliser le plus de code possible), mais beaucoup moins complète.
Il nous fallait aussi de quoi faire des calculs matriciels, nous avons donc utilisé la librairie glm.
