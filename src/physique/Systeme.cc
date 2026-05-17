#include "Systeme.h"
#include "Grille.h" //j'ai du changer ma méthode evolue ()
#include "Particule.h"
#include "TextViewer.h"
#include "Vecteur3D.h"
#include <fstream>

using namespace std;
using namespace cst;

// accesseurs
vector<Particule *> const &Systeme::getParticules() const { return particules; }

vector<Obstacle *> const &Systeme::getObstacles() const { return obstacles; }

vector<Source *> const &Systeme::getSources() const { return sources; }

// ajouts
void Systeme::ajouteParticule(Particule *p) { particules.push_back(p); }

void Systeme::ajouteObstacle(Obstacle *o) { obstacles.push_back(o); }

void Systeme::ajouteSource(Source *s) { sources.push_back(s); }

// implémentation de l'afficahge en CLI avec l'opérateur <<
ostream &operator<<(ostream &out, Systeme const &s) {

  TextViewer vue(out); // outil d'afficahge
  out << "Le systeme est constitue des " << s.getParticules().size()
      << " particules suivantes :" << endl;

  for (auto const &p : s.getParticules()) {
    p->dessine_sur(vue);
    out << endl;
  }

  out << "et de(s) " << s.getObstacles().size()
      << " obstacles suivants :" << endl;

  for (auto const &o : s.getObstacles()) {
    o->dessine_sur(vue); // c'est du polymorphsime
    out << endl;
  }

  if (!s.getSources().empty()) {
    out << "et de(s) " << s.getSources().size()
        << " sources suivantes :" << endl;

    for (auto const &s : s.getSources()) {
      s->dessine_sur(vue);
      out << endl;
    }
  }

  return out;
}

// ancienne versioin de evolue()

// void Systeme::evolue() {
// for (size_t i = 0; i < particules.size(); i++) {
//  force perso
// particules[i]->ajouteForce(eta_milieu, rho_milieu);

// on ajoute a la particule i la force qu'exerce l'obstactle j
// for (size_t j = 0; j < obstacles.size(); j++) {
// particules[i]->ajouteForce(*obstacles[j]);
//}

// on ajoute a la particule i la force qu'exerce la particule j
// for (size_t j = 0; j < particules.size(); j++) {
// if (i != j) {
// particules[i]->ajouteForce(*particules[j]);
//}
// }
//}

// après avoir calcule la force pour toute les particules on les applique à
// chaque particules. Ce choix d'algorithme nous semble plus "physiquement"
// logique.
// for (auto particule : particules) {
// particule->bouger(dt);
//}
//}

// Méthode intermédiaire qui permet le calcule de toute les forces appliqué à
// toute les particules du système
void Systeme::calculerForces() {
  // On choisit une taille de case
  // Ici je prends 2.1 * SIGMA pour être strictement plus grand que 2*SIGMA.
  // P12 : Grille grille(2.1 * SIGMA, 100, 100, 100);
  // P13:
  Grille grille(2.1 * SIGMA);

  // On remplit la grille avec les positions actuelles des particules.
  grille.remplit(particules);

  for (size_t i = 0; i < particules.size(); i++) {

    particules[i]->ajouteForce(eta_milieu, rho_milieu);

    // Force due aux obstacles.
    // Cette partie ne change pas avec la grille.
    for (size_t j = 0; j < obstacles.size(); j++) {
      particules[i]->ajouteForce(*obstacles[j]);
    }
    // Nouvelle méthode :
    // on ne regarde que les particules dans la même case et les cases voisines
    // directes

    vector<Particule *> candidates = grille.voisines(*particules[i]);

    for (auto autre : candidates) {
      // Il faut éviter qu'une particule interagisse avec elle-même
      if (autre != particules[i]) {
        particules[i]->ajouteForce(*autre);
      }
    }
  }
}

// implémentation de l'algoritme rk4
void Systeme::evolue_rk4() {
  // on copie les vitesses et positions actuelles des particules
  int n = particules.size();

  vector<Vecteur3D> p0(n);
  vector<Vecteur3D> v0(n);

  for (int i = 0; i < n; i++) {
    p0[i] = particules[i]->get_position();
    v0[i] = particules[i]->get_vitesse();
  }

  // on créer des tableau vide qui contienderons les "pentes" des particules,
  // les quatres points permettent une meilleur approximations du résultat de
  // l'équations différentiel F=ma.
  vector<Vecteur3D> kp[4];
  vector<Vecteur3D> kv[4];

  // on pose les coefficient qui donne la fraction de dt à laquelle on évalue
  // chaque pente, ce sont les "noeuds".
  double coeff[] = {0.0, 0.5, 0.5, 1.0};

  for (int step = 0; step < 4; step++) {
    // Si on est pas à la première étape on met à jour les positions des
    // particules
    if (step > 0) {
      // on place la particule à l'état intermédiaire ou l'on veut évaluer la
      // pente suivante
      for (int i = 0; i < n; i++) {
        particules[i]->setPosition(p0[i] + coeff[step] * kp[step - 1][i]);
        particules[i]->setVitesse(v0[i] + coeff[step] * kv[step - 1][i]);
      }
    }

    // on remet les forces à 0 et on calcule les forces à l'état actuelle
    for (auto part : particules) {
      part->resetForce();
    }
    calculerForces();

    // on alloue l'espace nécéssaire
    kp[step].resize(n);
    kv[step].resize(n);

    for (int i = 0; i < n; i++) {
      // on évalue la pente de la position (dp = (dp/dt)*dt = v*dt) à partir de
      // la vitesse
      kp[step][i] = particules[i]->get_vitesse() * dt;
      // on évalue la pente de la vitesse (dv = (dv/dt)*dt = a*dt = (F/m)*dt) à
      // partir de la force
      kv[step][i] =
          particules[i]->get_force() * (dt / particules[i]->get_masse());
    }
    // ses valeurs sont alors utilisé pour l'étape suivante
  }

  // on fait la moyenne pondérée des quatres points calculé précédemment pour
  // trouver la valeurs approché de la positions et de la vitesse
  for (size_t i = 0; i < n; i++) {
    particules[i]->resetForce();
    particules[i]->setPosition(
        p0[i] +
        (kp[0][i] + kp[1][i] * 2.0 + kp[2][i] * 2.0 + kp[3][i]) * (1.0 / 6.0));
    particules[i]->setVitesse(
        v0[i] +
        (kv[0][i] + kv[1][i] * 2.0 + kv[2][i] * 2.0 + kv[3][i]) * (1.0 / 6.0));
  }
}

// méthode évolue qui permet d'utilisation des deux algoritme mis en place.
void Systeme::evolue() {
  for (auto source : sources) {
    source->creation(particules, gen, dt, eta_milieu, rho_milieu);
  }
  if (use_rk4) {
    evolue_rk4();
  } else {
    // on remet les forces à 0 et on calcule les forces à l'état actuelle
    for (auto part : particules) {
      part->resetForce();
    }
    calculerForces();
    // Après avoir calculé toutes les forces, on déplace les particules
    //
    // on ne bouge les particules après avoir calculé toutes les forces
    for (auto particule : particules) {
      particule->bouger(dt);
    }
  }
}

// méthode permettant d'afficher les données en CLI.
void Systeme::evolution(double t_final, ostream &out) {
  TextViewer vue(out);
  double t = 0;
  out << "Condition initiale du système : " << endl;
  out << (*this) << endl;
  do {
    out << "----------------------------- t = " << t
        << " -----------------------------" << endl;
    for (size_t i = 0; i < particules.size(); i++) {
      out << i + 1 << " : ";
      particules[i]->dessine_sur(vue);
      out << endl;
    }
    evolue();
    t += dt;
  } while (t <= t_final);
}

void Systeme::dataEvolution(
    double t_final) { // méthode qui ajoute dans un dossier data les données
                      // d'évolution au format txt
  vector<ofstream> fichiers;
  for (size_t i = 0; i < particules.size(); ++i) {
    fichiers.emplace_back("./data/particule_" + to_string(i) + ".txt");
  }

  double t = 0;
  do {
    for (size_t i = 0; i < particules.size(); ++i) {
      Vecteur3D pos = particules[i]->get_position();
      fichiers[i] << pos.get_x() << " " << pos.get_y() << " " << pos.get_z()
                  << "\n";
    }
    evolue();
    t += dt;
  } while (t <= t_final);
}
