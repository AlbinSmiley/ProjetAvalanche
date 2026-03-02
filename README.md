# ProjetAvalanche
Un projet universitaire qui à pour but de simuler une avalanche dans le cadre d'un cours de programmation orientée objet en c++. 

__Contribution :__ Fabienne Unterkircher et Albin Ismaili

## Rappel personnel 
Avant de changer le code : 
1. `git pull`

Après avoir changé le code : 
1. `git add .`
2. `git commit -m "<message qui dit ce qu'on a fait>"` 
3. `git push`

## Execution du programme et `Makefile`
Cette section du `README.md` a été écrite par ChatGPT dans un but purement explicatif et de rappel.  

### Commandes de base `make` et structure du projet Avalanche

#### 1. Structure du projet

Le projet est organisé de manière standard pour un projet C++.

```
.
├── build/
│   ├── bin/      → exécutables compilés
│   └── obj/      → fichiers objets (.o)
├── docs/         → documentation du projet
│   ├── CONCEPTION.md
│   ├── JOURNAL.md
│   └── REPONSES.md
├── Makefile      → règles de compilation
├── README.md     → description du projet
├── src/          → code source principal
│   ├── Vecteur3D.cc
│   └── Vecteur3D.h
├── tests/        → programmes de test
│   └── testVecteur3D.cc
├── testVecteur3D → exécutable compilé (temporaire)
└── trash/        → anciens fichiers inutiles
```

##### Rôle de chaque dossier

* **src/**
  Contient le code principal du projet.
  Exemple : classes, fonctions, structures de données.

* **tests/**
  Contient les programmes servant à tester le code de `src/`.

* **build/obj/**
  Contient les fichiers objets générés pendant la compilation.
  Ces fichiers sont intermédiaires.

* **build/bin/**
  Contient les exécutables compilés.

* **docs/**
  Contient la documentation du projet.

* **trash/**
  Contient les anciens fichiers ou brouillons.
  Peut être supprimé quand inutile.

---

#### 2. Commandes de base avec `make`

Le `Makefile` automatise la compilation.

##### 2.1 Compiler le projet

```bash
make
```

Cette commande :

1. Compile les fichiers `.cc`
2. Crée les fichiers `.o` dans `build/obj`
3. Crée l’exécutable dans `build/bin`

---

##### 2.2 Exécuter le programme

Si le Makefile contient une règle `run` :

```bash
make run
```

Sinon :

```bash
./build/bin/testVecteur3D
```

---

##### 2.3 Nettoyer les fichiers compilés

```bash
make clean
```

Cette commande supprime :

* fichiers objets
* exécutables

Utile avant une compilation propre.

---

##### 2.4 Recompiler entièrement

```bash
make clean
make
```

---

#### 3. Comment ajouter un nouveau fichier

Exemple : ajouter `Matrice.cc` et `Matrice.h`.

1. Mettre les fichiers dans `src/`
2. Ajouter un test dans `tests/`
3. Modifier le Makefile pour inclure ces fichiers

---

#### 4. Bonnes pratiques

* Ne jamais versionner les fichiers compilés (`.o`, exécutables)
* Mettre uniquement le code source sur Git
* Garder `src/` propre
* Écrire les tests dans `tests/`
* Documenter dans `docs/`
