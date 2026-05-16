 ---
  Problèmes CRITIQUES

  1. Forces répulsives inversées (attraction au lieu de répulsion)
  src/physique/particules/ParticuleRoche.cc:52,60 et ParticuleNeige.cc:61

  ecartOriente(other, *this) pointe de other vers this. En multipliant par forceRepulsive() (positif) et en l'ajoutant à other, la force
  résultante attire other vers la source au lieu de le repousser. La neige-neige est correct par accident (le signe de LJ compense), mais
  rocher-rocher et rocher-neige sont inversés.

  <!-- 2. Division par zéro dans Vecteur3D::operator~() -->
  <!-- src/math/Vecteur3D.cc:68 -->

  Si deux particules se retrouvent à la même position, norme() == 0 et la normalisation produit NaN/Inf, corrompant toute la simulation.

  1. Systeme::affichageEvolution déclarée mais jamais définie
  src/physique/Systeme.h:62

  Tout appel à cette méthode causerait une erreur de linker.

  ---
  Problèmes MODÉRÉS

  1. Source::creation ne positionne jamais la nouvelle particule
  src/physique/Source.cc:21–40 — clone() copie la position du modèle, pas position_. L'attribut position_ de la source est donc inutile.

  2. Les sources ne sont jamais activées dans evolue()
  src/physique/Systeme.cc — Systeme::evolue() n'appelle jamais source->creation(...). Les sources sont du code mort.

  3. Grille::case_de utilise la troncature au lieu de floor
  src/physique/Grille.cc:48–52 — Pour des coordonnées négatives (ex. z), int(-0.3/1.0) = 0 au lieu de -1. Les particules tombant vers le bas sont
   placées dans la mauvaise case de la grille.

  4. setRayon ne met pas à jour masse_
  src/physique/particules/Particule.cc:36 — La masse est mise en cache à la construction. Quand Source::creation appelle setRayon(), la masse
  reste incorrecte → dynamique fausse.

  5. Plan::opere_sur(ParticuleRoche&) est un stub vide
  src/physique/obstacles/Plan.cc:35–37 — Les rochers traversent tous les obstacles sans réaction.

  6. Dalle n'applique pas ses propres limites géométriques
  Une Dalle (carrée/rectangulaire) applique une force comme si c'était un plan infini.

  7. SupportADessin n'a pas d'overloads pour ParticuleNeige/ParticuleRoche
  src/rendu/SupportADessin.h — Impossible de rendre les deux types différemment ; tout se résout vers dessine(Particule const&).

  ---
  Problèmes MINEURS

  1. using namespace std dans un header
  src/physique/Grille.h:3 — Pollue l'espace de noms de tous les fichiers qui incluent ce header.

  2. tests/exerciceP12.cc est vide
  Le fichier contient juste int main() { Systeme systeme; return 0; } — aucun test réel.

  3. Paramètre etat de Source typé double au lieu de bool
  src/physique/Source.h:26

  4. const double masse() const — const redondant sur la valeur de retour
  src/physique/particules/Particule.h:24 — Génère un avertissement compilateur.

  ---
  Les deux priorités les plus urgentes sont le sens des forces répulsives (bug de physique fondamental) et la grille avec floor (affecte toutes
  les interactions quand z < 0). Tu veux que je corrige certains de ces problèmes ?

----------
Voici exactement quoi faire, fichier par fichier :

  ---

  1. Particule.h — ajouter 2 méthodes inline

  Après void setVitesse(...) et void setRayon(...), ajoute :
  void setPosition(Vecteur3D const& p) { position_= p; }
  void resetForce() { force_ = Vecteur3D(0.0, 0.0, 0.0); }

  ---

  1. Systeme.h — ajouter l'enum, le setter, et 2 méthodes privées

  Dans la section private, ajoute :
  enum class Integrateur { EULER, RK4 };
  Integrateur integrateur_ = Integrateur::EULER;
  void calculerForces();
  void evolueRK4();

  Dans la section public, ajoute le setter :
  void set_integrateur(Integrateur i) { integrateur_ = i; }

  ---

  1. Systeme.cc — 3 modifications

  a) Remplace le corps de evolue() par un simple dispatcher :
  void Systeme::evolue() {
    if (integrateur_ == Integrateur::RK4) { evolueRK4(); return; }
    // ... le code Euler actuel reste ici, inchangé
  }

  b) Ajoute calculerForces() — c'est le corps de calcul actuel de evolue() extrait, avec un reset au début :
  void Systeme::calculerForces() {
    for (auto p : particules) p->resetForce();
    Grille grille(2.1 *SIGMA);
    grille.remplit(particules);
    for (size_t i = 0; i < particules.size(); i++) {
      particules[i]->ajouteForce(eta_milieu, rho_milieu);
      for (auto o : obstacles) particules[i]->ajouteForce(*o);
      for (auto autre : grille.voisines(*particules[i]))
        if (autre != particules[i]) particules[i]->ajouteForce(*autre);
    }
  }

  c) Ajoute evolueRK4() :
  void Systeme::evolueRK4() {
    size_t n = particules.size();
    std::vector<Vecteur3D> p0(n), v0(n);
    for (size_t i = 0; i < n; i++) {
      p0[i] = particules[i]->get_position();
      v0[i] = particules[i]->get_vitesse();
    }

    std::vector<Vecteur3D> kp[4], kv[4];
    double coeff[] = {0.0, 0.5, 0.5, 1.0};  // offset pour chaque sous-pas

    for (int s = 0; s < 4; s++) {
      if (s > 0) {
        for (size_t i = 0; i < n; i++) {
          particules[i]->setPosition(p0[i] + kp[s-1][i] * coeff[s]);
          particules[i]->setVitesse(v0[i] + kv[s-1][i] * coeff[s]);
        }
      }
      calculerForces();
      kp[s].resize(n); kv[s].resize(n);
      for (size_t i = 0; i < n; i++) {
        kp[s][i] = particules[i]->get_vitesse() * dt;
        kv[s][i] = particules[i]->get_force() * (dt / particules[i]->get_masse());
      }
    }

    for (size_t i = 0; i < n; i++) {
      particules[i]->setPosition(p0[i] + (kp[0][i] + kp[1][i]*2.0 + kp[2][i]*2.0 + kp[3][i]) * (1.0/6.0));
      particules[i]->setVitesse(v0[i] + (kv[0][i] + kv[1][i]*2.0 + kv[2][i]*2.0 + kv[3][i]) * (1.0/6.0));
    }
  }

  ---
  Pour l'utiliser dans un test

  systeme.set_integrateur(Systeme::Integrateur::RK4);

  La valeur par défaut reste Euler, donc rien ne casse.

---------
  Structure de Source

  Le constructeur prend ces paramètres :

  Source(
      Particule const& modele,          // particule-type à cloner
      Vecteur3D const& position,        // position d'émission
      Vecteur3D const& vitesse_moyenne, // vitesse initiale moyenne
      double ecart_type_vitesse,        // dispersion de vitesse (gaussienne)
      double ecart_type_rayons,         // dispersion de rayon (gaussienne)
      double debit                      // particules émises par unité de temps
  );

  Exemple concret pour simulation.cc

  #include "ParticuleNeige.h"
  #include "Source.h"
  #include "Systeme.h"
  #include "Aleatoire.h"

  int main() {
      Systeme systeme;

      // Modèle : particule type qui sera cloné par la source
      ParticuleNeige modele(Vecteur3D(0,0,5), Vecteur3D(0,0,0), 0.1);

      // Création de la source
      Source* src = new Source(
          modele,
          Vecteur3D(0, 0, 5),   // position de la source
          Vecteur3D(0, 0, -1),  // vitesse initiale moyenne (vers le bas)
          0.2,                   // écart-type vitesse
          0.05,                  // écart-type rayon
          10.0                   // débit : 10 particules/s
      );

      systeme.ajouteSource(src);
      // ...
  }

  Problème important : les sources ne sont pas appelées dans evolue()

  En regardant Systeme::evolue() (Systeme.cc:190), source.creation() n'est jamais appelé — les sources sont stockées mais pas utilisées
  automatiquement. Il faut l'ajouter manuellement.

  Option 1 — modifier Systeme::evolue() pour que la génération soit automatique :

  // Systeme.cc, dans evolue(), avant le calcul des forces
  Aleatoire gen; // à mettre en attribut de Systeme pour éviter une re-création
  for (auto s : sources) {
      s->creation(particules, gen, dt, eta_milieu, rho_milieu);
  }

  Option 2 — appel manuel dans la boucle de simulation (plus de contrôle) :

  Aleatoire gen;
  RaylibRender vue3D;
  // ou votre boucle personnalisée :
  for (double t = 0; t < 10.0; t += cst::DT) {
      for (auto s : systeme.getSources())
          s->creation(/*besoin d'un accès aux particules*/);
      systeme.evolue();
  }

  L'option 1 est plus propre pour l'architecture existante. Il faudrait ajouter un attribut Aleatoire aleatoire_ à Systeme pour ne pas recréer le
   générateur à chaque pas.
