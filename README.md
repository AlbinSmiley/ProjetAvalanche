# Projet Avalanche

> Simulation d'avalanche en C++ — cours de programmation orientée objet

**Contribution :** Fabienne Unterkircher et Albin Ismaili

---

## Réponses aux questions pour ce document

Nous avons fait toute la partie obligatoire de ce projet, nous avons également apporté quelques compléments :

- Dalle comme obstacles
- La positibilité d'utilisé l'algorithme RK4
- La couleur des particules dans la simulation graphique dépend de ses dimensions physiques
- Nous avons également ajouté quelques options dans la simulation graphique

Nous avons donc bien une version graphique qui utilise la bibliothèques raylib

Nous estimons avoir passé en moyenne 5h par semaine tout les deux sur ce projet ...

## Démarrage rapide

1. Se placer à la racine du projet
2. Rendre `install.sh` exécutable : `chmod +x install.sh`
3. Exécuter `./install.sh` — CMake compilera le nécessaire

Ou ce mettre à la racine du projet et éxécuter :

```bash
chmod +x install.sh && ./install.sh
```

---

## Tests

Les exécutables se trouvent dans `build/bin/` :

```bash
./build/bin/<nom du test>
```

Par exemple pour voire la simulation graphique : `./build/bin/simulation`.

---

## Structure du projet

Les versions demandé pour le rendu final se trouvent dans le dossier `versions/`, l'ensemble du programme se trouve dans le dossier `src/`, le code pour les tests et autres `main` se trouve dans `tests/`. Le journal, le fichier de conception et de réponses se trouvent dans le dossier `docs/` accompagné d'un diagramm de class généré par clang-uml précédemment.

La structure du projet peut se résumé grâce à l'arbre suivant :

```
.
├── install.sh
├── README.md
├── CMakeLists.txt
├── data/
├── out/
├── docs/
│   ├── CONCEPTION.md
│   ├── CONCEPTION.svg -> diagramm de class (généré par clang-uml)
│   ├── JOURNAL.md
│   └── REPONSES.md
├── src/
│   ├── constantes.h
│   ├── math/
│   │   ├── Aleatoire.{cc,h}
│   │   └── Vecteur3D.{cc,h}
│   ├── physique/
│   │   ├── Agent.h
│   │   ├── Grille.{cc,h}
│   │   ├── Systeme.{cc,h}
│   │   ├── Source.{cc,h}
│   │   ├── obstacles/
│   │   │   ├── Obstacle.{cc,h}
│   │   │   ├── Plan.{cc,h}
│   │   │   └── Dalle.{cc,h}
│   │   └── particules/
│   │       ├── Particule.{cc,h}
│   │       ├── ParticuleNeige.{cc,h}
│   │       └── ParticuleRoche.{cc,h}
│   └── rendu/
│       ├── Dessinable.h
│       ├── SupportADessin.h
│       ├── raylib/
│       │   ├── raylib_render.{cc,h}
│       │   └── raygui.h
│       └── text/
│           └── TextViewer.{cc,h}
├── tests/
│   ├── simulation.cc
│   ├── chute_libre.cc
│   ├── testParticule.cc
│   ├── testSysteme.cc
│   ├── testObstacle.cc
│   ├── testSource.cc
│   ├── testVecteur3D.cc
│   ├── testTextViewer.cc
│   ├── testAleatoire.cc
│   ├── testP5.cc
│   ├── exerciceP9.cc
│   └── exerciceP12.cc
└── build/
    └── bin/
        ├── simulation
        ├── chute_libre
        ├── testParticule
        ├── testSysteme
        ├── testObstacle
        ├── testSource
        ├── testVecteur3D
        ├── testTextViewer
        ├── testAleatoire
        ├── testP5
        ├── exerciceP9
        └── exerciceP12
```
