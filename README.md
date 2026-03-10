# Chaos Demo - Moteur de Jeu multi-couches (C/C++)

### DESCRIPTION

**Chaos Demo** est une démonstration visuelle tournant sur un moteur de jeu 2D fait maison. 

Ce projet a été réalisé en solo dans le cadre de mon évaluation de fin de semestre pour le module de Programmation Orientée Objet. Il a été noté **16/20**, validant avec succès l'ensemble des critères d'ingénierie logicielle demandés.

> ### À propos de ce dépôt
> Ce répertoire a été préparé spécifiquement pour mes candidatures en Master, afin d'offrir un aperçu clair et direct depuis mon CV. Il s'agit d'une version consolidée d'un projet académique :
> * **Historique condensé :** L'ensemble du développement a été regroupé en un commit unique pour mettre immédiatement en valeur le résultat abouti.
> * **Fidélité au projet initial :** Le périmètre et les fonctionnalités restent strictement identiques à la version d'origine.

### ARCHITECTURE TECHNIQUE

Le projet se distingue par une architecture multi-couches stricte, séparant la logique bas niveau de la logique de jeu, tout en utilisant les standards récents du langage (C17 et C++20) :

* **Couche Core (C) :** Une API bas niveau (`system`, `renderer`, `window`) qui encapsule directement les appels bruts à la librairie externe SDL2.
* **Couche Engine (C++) :** Un moteur de jeu orienté objet qui fait le pont avec l'API C. Il gère le système de rendu, la fenêtre, les mathématiques temporelles et la géométrie (`engine::d2`).
* **Couche Game (C++) :** La logique applicative (physique, collisions, entités) qui hérite des classes du moteur pour animer la simulation.

### CONCEPTS C++ & ORIENTÉS OBJET DÉMONTRÉS

Conformément aux exigences académiques, le code source exploite en profondeur la philosophie du C++ moderne :

* **Héritage & Polymorphisme :** Hiérarchie de classes pour les entités (`entity` -> `ball`/`box`) et la géométrie (`figure` -> `surface` -> `rect`/`circle`) avec méthodes virtuelles pures.
* **Gestion mémoire & Move Semantics :** Isolation des pointeurs bruts SDL2 (RAII) et implémentation de la sémantique de déplacement (constructeurs/opérateurs *move*) pour des classes comme `engine::window`.
* **Templates & C++ Moderne :** Structures mathématiques templatisées (`vec2<T>`) et utilisation de fonctionnalités C++17/20 comme `if constexpr` pour la résolution de types à la compilation.
* **Surcharge d'opérateurs :** Redéfinition des opérateurs mathématiques classiques pour une manipulation fluide des vecteurs.
* **Utilisation poussée de la STL :** Pointeurs intelligents (`std::unique_ptr`), gestion des types optionnels (`std::optional`), et encapsulation du générateur Mersenne Twister (`std::mt19937`).

### COMPILATION ET EXÉCUTION

**Prérequis :**
Le projet nécessite un compilateur compatible C++20/C17 (`g++`/`gcc`) ainsi que la librairie **SDL2**.

**Commandes :**
Un `Makefile` est fourni pour automatiser la construction. Exécutez simplement les commandes suivantes à la racine du projet :

```bash
# Compiler le projet
make

# Lancer la démonstration
make run
```

*Note : L'exécutable généré porte le nom de `chaos_demo` et sera placé dans le dossier `bin/`*.
