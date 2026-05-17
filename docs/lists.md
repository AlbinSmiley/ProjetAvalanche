# Structure complète du projet `avalanche`

Liste exhaustive de toutes les classes, attributs, méthodes, opérateurs, fonctions libres et leurs signatures complètes.

---

## Sommaire

1. [`math/Vecteur3D`](#vecteur3d)
2. [`math/Aleatoire`](#aleatoire)
3. [`physique/Agent`](#agent)
4. [`physique/particules/Particule`](#particule)
5. [`physique/particules/ParticuleNeige`](#particuleneige)
6. [`physique/particules/ParticuleRoche`](#particuleroche)
7. [`physique/obstacles/Obstacle`](#obstacle)
8. [`physique/obstacles/Plan`](#plan)
9. [`physique/obstacles/Dalle`](#dalle)
10. [`physique/Source`](#source)
11. [`physique/Systeme`](#systeme)
12. [`physique/Triplet`](#triplet)
13. [`physique/Grille`](#grille)
14. [`rendu/Dessinable`](#dessinable)
15. [`rendu/SupportADessin`](#supportadessin)
16. [`rendu/text/TextViewer`](#textviewer)
17. [`rendu/raylib/RaylibRender`](#raylibrender)

---

## `Vecteur3D`

Fichier : `src/math/Vecteur3D.h` / `.cc`
Héritage : aucun.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `private` | `double` | `x_` | composante x |
| `private` | `double` | `y_` | composante y |
| `private` | `double` | `z_` | composante z |

### Constructeurs (public)

| Signature | Description |
|---|---|
| `Vecteur3D()` | vecteur nul `(0, 0, 0)` |
| `Vecteur3D(double x, double y, double z)` | construction par coordonnées |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `norme2() const` | `double` | norme au carré |
| `norme() const` | `double` | norme euclidienne |
| `get_x() const` | `double` | getter |
| `get_y() const` | `double` | getter |
| `get_z() const` | `double` | getter |
| `set_x(double x)` | `void` | setter |
| `set_y(double y)` | `void` | setter |
| `set_z(double z)` | `void` | setter |

### Opérateurs internes (membres, public)

| Signature | Retour | Description |
|---|---|---|
| `operator==(Vecteur3D const&) const` | `bool` | égalité à `PRECISION` près |
| `operator!=(Vecteur3D const&) const` | `bool` | différence |
| `operator+=(Vecteur3D const&)` | `Vecteur3D&` | addition assignée |
| `operator-=(Vecteur3D const&)` | `Vecteur3D&` | soustraction assignée |
| `operator*=(double const)` | `Vecteur3D&` | multiplication scalaire assignée |
| `operator/=(double const)` | `Vecteur3D&` | division scalaire assignée |
| `operator^=(Vecteur3D const&)` | `Vecteur3D&` | produit vectoriel assigné |
| `operator*(Vecteur3D const&) const` | `double` | produit scalaire |
| `operator~() const` | `Vecteur3D` | vecteur unitaire |
| `operator-() const` | `Vecteur3D` | opposé |

### Opérateurs externes (fonctions libres)

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Vecteur3D const&)` | affichage `(x y z)` |
| `Vecteur3D operator+(Vecteur3D, Vecteur3D const&)` | addition |
| `Vecteur3D operator-(Vecteur3D, Vecteur3D const&)` | soustraction |
| `Vecteur3D operator*(double, Vecteur3D)` | scalaire × vecteur |
| `Vecteur3D operator*(Vecteur3D, double)` | vecteur × scalaire |
| `Vecteur3D operator/(double, Vecteur3D)` | division |
| `Vecteur3D operator/(Vecteur3D, double)` | division |
| `Vecteur3D operator^(Vecteur3D, Vecteur3D const&)` | produit vectoriel |

---

## `Aleatoire`

Fichier : `src/math/Aleatoire.h` / `.cc`
Héritage : aucun. Copie et affectation supprimées.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `private static` | `std::uniform_real_distribution<double>` | `distribution_uniforme` | partagée entre toutes les instances |
| `private static` | `std::normal_distribution<double>` | `distribution_normale` | partagée |
| `private static` | `std::random_device` | `rd` | seed system |
| `private` | `std::mt19937` | `generateur` | générateur Mersenne Twister |

### Constructeurs (public)

| Signature | Description |
|---|---|
| `Aleatoire(int graine)` | génération à partir d'une graine |
| `Aleatoire()` | graine récupérée depuis `rd` |

### Constructeurs supprimés (private)

| Signature |
|---|
| `Aleatoire(Aleatoire const&) = delete` |
| `Aleatoire& operator=(Aleatoire const&) = delete` |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `uniforme(double min = 0.0, double max = 1.0)` | `double` | tirage uniforme |
| `gaussienne(double moyenne, double ecart_type)` | `double` | tirage gaussien |

---

## `Agent`

Fichier : `src/physique/Agent.h`
Héritage : aucun. Classe abstraite.
Pré-déclarations : `class ParticuleNeige;`, `class ParticuleRoche;`.

### Attributs

Aucun.

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `opere_sur(ParticuleNeige&) const = 0` | `void` | virtuelle pure |
| `opere_sur(ParticuleRoche&) const = 0` | `void` | virtuelle pure |
| `~Agent() = default` | — | destructeur virtuel par défaut |

---

## `Particule`

Fichier : `src/physique/particules/Particule.h` / `.cc`
Héritage : `public Agent`, `public Dessinable`. **Classe abstraite**.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `protected` | `Vecteur3D` | `position_` | position (mm) |
| `protected` | `Vecteur3D` | `vitesse_` | vitesse |
| `protected` | `double` | `rayon_` | rayon |
| `protected` | `double` | `rho_` | masse volumique (mg/mm³) |
| `protected` | `double` | `masse_` | masse, calculée à la construction |
| `protected` | `Vecteur3D` | `force_` | force résultante (peut changer) |

### Méthodes protégées

| Signature | Retour | Description |
|---|---|---|
| `masse() const` | `const double` | calcule la masse depuis `rho_` et `rayon_` (sphère) |
| `lambda(double eta_milieu_, double rho_milieu_) const` | `Vecteur3D` | terme de frottement, virtuelle |

### Constructeurs (public)

| Signature | Description |
|---|---|
| `Particule(Vecteur3D const& position, Vecteur3D const& vitesse, double rayon, double rho = cst::RHO_PARTICULE)` | usuel |
| `Particule(Particule const& autre)` | par copie |

### Getters publics

| Signature | Retour |
|---|---|
| `get_position() const` | `Vecteur3D` |
| `get_vitesse() const` | `Vecteur3D` |
| `get_rayon() const` | `double` |
| `get_rho() const` | `double` |
| `get_masse() const` | `double` |
| `get_force() const` | `Vecteur3D` |

### Setters / mutateurs publics

| Signature | Retour | Description |
|---|---|---|
| `add_force(Vecteur3D const& f)` | `void` | `force_ += f` |
| `setPosition(Vecteur3D const&)` | `void` | |
| `setVitesse(Vecteur3D const&)` | `void` | |
| `setRayon(double)` | `void` | |
| `bouger(double dt = cst::DT)` | `void` | met à jour vitesse et position, reset force |
| `resetForce()` | `void` | `force_ = Vecteur3D()` |

### Méthodes virtuelles publiques

| Signature | Retour | Description |
|---|---|---|
| `ajouteForce(Agent const&) = 0` | `void` | virtuelle pure, double dispatch |
| `ajouteForce(double eta_milieu_, double rho_milieu_)` | `void` | gravité + frottement |
| `clone() const = 0` | `Particule*` | virtuelle pure |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Particule const&)` | affichage `[ pos, vit, m, r ]` |
| `Vecteur3D ecartOriente(Particule const& p1, Particule const& p2)` | `p2.position - p1.position` |
| `double distance(Particule const& p1, Particule const& p2)` | norme de l'écart orienté |

---

## `ParticuleNeige`

Fichier : `src/physique/particules/ParticuleNeige.h` / `.cc`
Héritage : `public Particule`.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `public static constexpr` | `double` | `epsilon` | alias de `cst::EPSILON` |
| `public static constexpr` | `double` | `sigma` | alias de `cst::SIGMA` |

### Constructeurs

`using Particule::Particule;` → réutilise tous les constructeurs de `Particule`.

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `facteurLJ(double dis) const` | `double` | facteur de Lennard-Jones |
| `forceLJ(ParticuleNeige const&) const &` | `double` | norme de la force LJ |
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |
| `opere_sur(ParticuleNeige&) const override` | `void` | interaction LJ |
| `opere_sur(ParticuleRoche&) const override` | `void` | répulsion faible |
| `ajouteForce(Agent const& autre) override` | `void` | `autre.opere_sur(*this)` |
| `clone() const override` | `Particule*` | `new ParticuleNeige(*this)` |

### Fonctions libres

| Signature | Retour | Description |
|---|---|---|
| `facteur_f(double x)` | `double` | facteur paramétré par `x = distance/sigma` |
| `facteurLJ(double)` | `double` | déclarée en libre |

---

## `ParticuleRoche`

Fichier : `src/physique/particules/ParticuleRoche.h` / `.cc`
Héritage : `public Particule`.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `public static constexpr` | `double` | `epsilon` | alias de `cst::EPSILON` |
| `public static constexpr` | `double` | `sigma` | alias de `cst::SIGMA` |

### Constructeurs

`using Particule::Particule;`

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |
| `opere_sur(ParticuleRoche&) const override` | `void` | répulsion forte |
| `opere_sur(ParticuleNeige&) const override` | `void` | répulsion simple |
| `ajouteForce(Agent const& autre) override` | `void` | `autre.opere_sur(*this)` |
| `clone() const override` | `Particule*` | `new ParticuleRoche(*this)` |

---

## `Obstacle`

Fichier : `src/physique/obstacles/Obstacle.h` / `.cc`
Héritage : `public Agent`, `public Dessinable`. **Classe abstraite**.

### Attributs

| Visibilité | Type | Nom |
|---|---|---|
| `protected` | `Vecteur3D` | `position` |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `Obstacle(Vecteur3D const& position)` | — | constructeur |
| `~Obstacle() = default` | — | destructeur virtuel |
| `getPosition() const` | `Vecteur3D` | getter |
| `PointPlusProche(Vecteur3D const& x_i) const = 0` | `Vecteur3D` | virtuelle pure |
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Obstacle const&)` | `"Obstacle de position …"` |

---

## `Plan`

Fichier : `src/physique/obstacles/Plan.h` / `.cc`
Héritage : `public Obstacle`.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `protected` | `Vecteur3D` | `normale` | unitaire (normalisé au constructeur) |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `Plan(Vecteur3D const& position, Vecteur3D const& n)` | — | constructeur, normalise `n` |
| `getNormale() const` | `Vecteur3D` | getter |
| `PointPlusProche(Vecteur3D const& x_i) const override` | `Vecteur3D` | projection orthogonale |
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |
| `opere_sur(ParticuleNeige&) const override` | `void` | force LJ |
| `opere_sur(ParticuleRoche&) const override` | `void` | répulsion simple |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Plan const&)` | `"Plan d'origine … et de normale …"` |

---

## `Dalle`

Fichier : `src/physique/obstacles/Dalle.h` / `.cc`
Héritage : `public Plan`.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `private` | `double` | `largeur` | |
| `private` | `double` | `longueur` | |
| `private` | `Vecteur3D` | `directionLongueur` | unitaire |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `Dalle(Vecteur3D const& position, Vecteur3D& n, double largeur, double longueur, Vecteur3D& directionLongueur)` | — | constructeur |
| `getLargeur() const` | `double` | |
| `getLongueur() const` | `double` | |
| `getDirectionLongueur() const` | `Vecteur3D` | |
| `getDirectionLargeur() const` | `Vecteur3D` | `normale ^ directionLongueur` |
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Dalle const&)` | `"Dalle de position …, normale …, largeur …, longueur …"` |

---

## `Source`

Fichier : `src/physique/Source.h` / `.cc`
Héritage : `public Dessinable`.

### Attributs

| Visibilité | Type | Nom |
|---|---|---|
| `private` | `Particule const&` | `modele_` |
| `private` | `Vecteur3D` | `position_` |
| `private` | `Vecteur3D` | `vitesse_moyenne_initial_` |
| `private` | `double` | `ecart_type_vitesse_initial_` |
| `private` | `double` | `ecart_type_rayons_` |
| `private` | `double` | `debit_` |
| `private` | `bool` | `etat_` |

### Constructeur (public)

```cpp
Source(Particule const& modele,
       Vecteur3D const& position,
       Vecteur3D const& vitesse_moyenne_initial,
       double ecart_type_vitesse_initial,
       double ecart_type_rayons,
       double debit,
       double etat = true);
```

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `on()` | `void` | active la source |
| `off()` | `void` | désactive la source |
| `is_on() const` | `bool` | retourne `etat_` |
| `creation(std::vector<Particule*>&, Aleatoire&, double dt = cst::DT, double eta_milieu = cst::ETA_AIR, double rho_milieu = cst::RHO_AIR)` | `void` | génère et ajoute des particules clonées et perturbées |
| `getPosition() const` | `Vecteur3D` | getter |
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Source const&)` | `"Source de position …"` |

---

## `Systeme`

Fichier : `src/physique/Systeme.h` / `.cc`
Héritage : `public Dessinable`. Copie supprimée.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `private` | `std::vector<Particule*>` | `particules` | pointeurs (polymorphisme) |
| `private` | `std::vector<Obstacle*>` | `obstacles` | pointeurs |
| `private` | `std::vector<Source*>` | `sources` | pointeurs |
| `private` | `double` | `dt` | `= cst::DT` |
| `private` | `double` | `eta_milieu` | `= cst::ETA_AIR` |
| `private` | `double` | `rho_milieu` | `= cst::RHO_AIR` |
| `private` | `Aleatoire` | `gen` | générateur interne |
| `private` | `bool` | `use_rk4` | `= false` |

### Méthodes privées

| Signature | Retour | Description |
|---|---|---|
| `calculerForces()` | `void` | calcule les forces sur toutes les particules |
| `evolue_rk4()` | `void` | intégration Runge-Kutta 4 |

### Constructeurs / destructeur

| Signature | Description |
|---|---|
| `Systeme() = default` | système vide |
| `~Systeme()` | libère `particules`, `obstacles`, `sources` |
| `Systeme(Systeme const&) = delete` | copie interdite |
| `Systeme& operator=(Systeme const&) = delete` | affectation interdite |

### Getters publics

| Signature | Retour |
|---|---|
| `getParticules() const` | `std::vector<Particule*> const&` |
| `getObstacles() const` | `std::vector<Obstacle*> const&` |
| `getSources() const` | `std::vector<Source*> const&` |

### Méthodes d'ajout publiques

| Signature | Retour |
|---|---|
| `ajouteParticule(Particule* p)` | `void` |
| `ajouteObstacle(Obstacle* o)` | `void` |
| `ajouteSource(Source* s)` | `void` |

### Setters publics (inline)

| Signature | Retour |
|---|---|
| `set_dt(double dt_)` | `void` |
| `set_eta(double eta)` | `void` |
| `set_rho(double rho)` | `void` |

### Évolution publique

| Signature | Retour | Description |
|---|---|---|
| `evolue()` | `void` | un pas de temps |
| `evolution(double, std::ostream& out)` | `void` | évolue pendant un temps donné en affichant |
| `dataEvolution(double)` | `void` | écrit des données |
| `affichageEvolution(double, std::ostream& out)` | `void` | affichage durant l'évolution |
| `rk4_On()` | `void` | active rk4 |
| `rk4_Off()` | `void` | désactive rk4 |

### Dessin

| Signature | Retour | Description |
|---|---|---|
| `dessine_sur(SupportADessin& support) const override` | `void` | `support.dessine(*this)` |

### Fonctions libres

| Signature | Description |
|---|---|
| `std::ostream& operator<<(std::ostream&, Systeme const&)` | affichage texte complet |

---

## `Triplet`

Fichier : `src/physique/Triplet.h`
Type : `struct` (tout public).

### Attributs

| Type | Nom |
|---|---|
| `int` | `x` |
| `int` | `y` |
| `int` | `z` |

### Opérateurs

| Signature | Retour | Description |
|---|---|---|
| `operator<(Triplet const& autre) const` | `bool` | ordre lexicographique (clé de `std::map`) |

---

## `Grille`

Fichier : `src/physique/Grille.h` / `.cc`
Héritage : aucun.

### Attributs

| Visibilité | Type | Nom | Description |
|---|---|---|---|
| `private` | `double` | `pas_` | taille d'une case |
| `private` | `std::map<Triplet, std::vector<Particule*>>` | `cases_` | cases occupées (P13) |

### Constructeur (public)

| Signature | Description |
|---|---|
| `Grille(double pas)` | constructeur P13 (le constructeur P12 avec `nx, ny, nz` est commenté) |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `vide()` | `void` | `cases_.clear()` |
| `case_de(Vecteur3D const& position) const` | `Triplet` | indice de la case contenant la position |
| `ajoute(Particule* p)` | `void` | ajoute `p` dans sa case |
| `remplit(std::vector<Particule*> const& particules)` | `void` | vide puis remplit avec toutes les particules |
| `voisines(Particule const& p) const` | `std::vector<Particule*>` | particules dans la case de `p` et les 26 cases voisines |

---

## `Dessinable`

Fichier : `src/rendu/Dessinable.h`
Héritage : aucun. **Classe abstraite**.
Pré-déclaration : `class SupportADessin;`.

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `~Dessinable() = default` | — | destructeur virtuel |
| `dessine_sur(SupportADessin& support) const = 0` | `void` | virtuelle pure |

---

## `SupportADessin`

Fichier : `src/rendu/SupportADessin.h`
Héritage : aucun. **Classe abstraite**.
Pré-déclarations : `Particule`, `ParticuleNeige`, `Systeme`, `Obstacle`, `Plan`, `Dalle`, `Source`.

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `~SupportADessin() = default` | — | destructeur virtuel |
| `dessine(Particule const&) = 0` | `void` | virtuelle pure |
| `dessine(Obstacle const&) = 0` | `void` | virtuelle pure |
| `dessine(Plan const&) = 0` | `void` | virtuelle pure |
| `dessine(Dalle const&) = 0` | `void` | virtuelle pure |
| `dessine(Source const&) = 0` | `void` | virtuelle pure |
| `dessine(Systeme const&) = 0` | `void` | virtuelle pure |

---

## `TextViewer`

Fichier : `src/rendu/text/TextViewer.h` / `.cc`
Héritage : `public SupportADessin`.

### Attributs

| Visibilité | Type | Nom |
|---|---|---|
| `private` | `std::ostream&` | `flot` |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `TextViewer(std::ostream&)` | — | constructeur |
| `~TextViewer() override` | — | destructeur |
| `dessine(Particule const&) override` | `void` | |
| `dessine(Systeme const&) override` | `void` | |
| `dessine(Obstacle const&) override` | `void` | |
| `dessine(Dalle const&) override` | `void` | |
| `dessine(Plan const&) override` | `void` | |
| `dessine(Source const&) override` | `void` | |

---

## `RaylibRender`

Fichier : `src/rendu/raylib/raylib_render.h` / `.cc`
Héritage : `public SupportADessin`.

### Attributs privés

| Type | Nom | Valeur initiale | Description |
|---|---|---|---|
| `Camera3D` | `camera` | — | caméra 3D raylib |
| `bool` | `deplacement` | `false` | mode déplacement caméra |
| `bool` | `pointeur` | `false` | mode pointeur |
| `bool` | `lecture` | `false` | simulation en cours |
| `bool` | `rk4` | `false` | utiliser RK4 |
| `bool` | `affiche_vect` | `false` | afficher les vecteurs |
| `float` | `vitesse_sim` | `1.0f` | facteur de vitesse |
| `bool` | `fenetre_ajout` | `false` | fenêtre d'ajout ouverte |
| `bool` | `ajout_particule` | `false` | |
| `bool` | `ajout_plan` | `false` | |
| `char[16]` | `buf_px` | `"0"` | buffer position x |
| `bool` | `edit_px` | `false` | édition active |
| `char[16]` | `buf_py` | `"0"` | |
| `bool` | `edit_py` | `false` | |
| `char[16]` | `buf_pz` | `"2"` | |
| `bool` | `edit_pz` | `false` | |
| `char[16]` | `buf_vx` | `"0"` | |
| `bool` | `edit_vx` | `false` | |
| `char[16]` | `buf_vy` | `"0"` | |
| `bool` | `edit_vy` | `false` | |
| `char[16]` | `buf_vz` | `"0"` | |
| `bool` | `edit_vz` | `false` | |
| `char[16]` | `buf_r` | `"0.4"` | rayon |
| `bool` | `edit_r` | `false` | |

### Constantes publiques statiques

| Type | Nom | Valeur |
|---|---|---|
| `static constexpr int` | `PANEL_WIDTH` | `220` |
| `static constexpr int` | `MIN_WINDOW_HAUTEUR` | `800` |
| `static constexpr int` | `MIN_WINDOW_LARGEUR` | `800` |

### Méthodes publiques

| Signature | Retour | Description |
|---|---|---|
| `RaylibRender()` | — | initialise raylib et la caméra |
| `~RaylibRender() override` | — | `CloseWindow()` |
| `run(Systeme&)` | `void` | boucle principale d'affichage |
| `dessine(Particule const&) override` | `void` | |
| `dessine(Systeme const&) override` | `void` | itère sur particules et obstacles |
| `dessine(Obstacle const&) override` | `void` | corps vide |
| `dessine(Dalle const&) override` | `void` | |
| `dessine(Plan const&) override` | `void` | |
| `dessine(Source const&) override` | `void` | corps vide |
| `dessinePanel(Systeme&)` | `void` | panneau de contrôle raygui |
| `fenetreParticule(Systeme&)` | `void` | fenêtre d'ajout de particule |
| `fenetrePlan(Systeme&)` | `void` | fenêtre d'ajout de plan |

### Fonctions libres (dans `raylib_render.cc`)

| Signature | Retour | Description |
|---|---|---|
| `toRaylib(Vecteur3D const& vec)` | `Vector3` | conversion avec swap Y↔Z |
| `dessineAxes(float l)` | `void` | dessine les axes Ox, Oy, Oz colorés |
| `dessinePlan(Vecteur3D const& n, Vecteur3D const& pos, float longueur, float largeur, Color couleur)` | `void` | dessine un plan via 4 triangles (recto + verso) |
| `dessineDalle(Vecteur3D const& n, Vecteur3D const& pos, Vecteur3D const& e_L, Vecteur3D const& e_l, float longueur, float largeur, Color couleur)` | `void` | dessine une dalle rectangulaire |
| `couleurParLeRayon(double rayon)` | `Color` | couleur HSV en fonction du rayon |
