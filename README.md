# ProjetAvalanche

Un projet universitaire qui à pour but de simuler une "avalanche" dans le cadre d'un cours de programmation orientée objet en c++.

__Contribution :__ Fabienne Unterkircher et Albin Ismaili

## Comment commencer

1. Se placer dans la racine du projet ...
2. Rendre le fichier d'installation executable `chmod +x install.sh`
3. Excecuté le fichier `./install.sh`. Ce dernier ce chargera de compiler le nécéssaire avec CMake

## structure du projet

"Racine du projet"
├── install.sh
├── README.md
├── CMakeLists.txt
├── compile_commands.json
├── data/
├── docs
│   ├── CONCEPTION.md
│   ├── CONCEPTION.svg
│   ├── JOURNAL.md
│   └── REPONSES.md
├── build
│   ├── bin
│   │   ├── chute_libre
│   │   ├── exerciceP12
│   │   ├── exerciceP9
│   │   ├── simulation
│   │   ├── testAleatoire
│   │   ├── testObstacle
│   │   ├── testP5
│   │   ├── testParticule
│   │   ├── testSource
│   │   ├── testSysteme
│   │   ├── testTextViewer
│   │   └── testVecteur3D
│   └── ...
├── out/
├── src
│   ├── CMakeLists.txt
│   ├── constantes.h
│   ├── math
│   │   ├── Aleatoire.cc
│   │   ├── Aleatoire.h
│   │   ├── Vecteur3D.cc
│   │   └── Vecteur3D.h
│   ├── physique
│   │   ├── Agent.h
│   │   ├── Grille.cc
│   │   ├── Grille.h
│   │   ├── obstacles
│   │   │   ├── Dalle.cc
│   │   │   ├── Dalle.h
│   │   │   ├── Obstacle.cc
│   │   │   ├── Obstacle.h
│   │   │   ├── Plan.cc
│   │   │   └── Plan.h
│   │   ├── particules
│   │   │   ├── Particule.cc
│   │   │   ├── Particule.h
│   │   │   ├── ParticuleNeige.cc
│   │   │   ├── ParticuleNeige.h
│   │   │   ├── ParticuleRoche.cc
│   │   │   └── ParticuleRoche.h
│   │   ├── Source.cc
│   │   ├── Source.h
│   │   ├── Systeme.cc
│   │   ├── Systeme.h
│   │   └── Triplet.h
│   └── rendu
│       ├── Dessinable.h
│       ├── raylib
│       │   ├── raygui.h
│       │   ├── raylib_render.cc
│       │   └── raylib_render.h
│       ├── SupportADessin.h
│       └── text
│           ├── TextViewer.cc
│           └── TextViewer.h
└── tests
    ├── oldTests
    ├── chute_libre.cc
    ├── CMakeLists.txt
    ├── exerciceP12.cc
    ├── exerciceP9.cc
    ├── simulation.cc
    ├── testAleatoire.cc
    ├── testObstacle.cc
    ├── testP5.cc
    ├── testParticule.cc
    ├── testSource.cc
    ├── testSysteme.cc
    ├── testTextViewer.cc
    └── testVecteur3D.cc

## Comment utiliser les test

Les tests se trouvent dans le dossier `build/bin/` et on les execute simplement en faisant `./build/bin/<nom du test>`. Le fichier test le plus abouti est évidemment `./build/bin/simulation` qui est un bon point de départ pour faire connaissance avec le contenu du projet.
