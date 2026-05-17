# Projet Avalanche

> Simulation d'avalanche en C++ — cours de programmation orientée objet

**Contribution :** Fabienne Unterkircher et Albin Ismaili

---

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
│   ├── exerciceP12.cc
│   └── oldTests/
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
