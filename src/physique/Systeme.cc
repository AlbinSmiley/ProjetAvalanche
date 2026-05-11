#include "Systeme.h"
#include "Particule.h"
#include "TextViewer.h"
#include "Vecteur3D.h"
#include "Grille.h" //j'ai du changer ma méthode evolue ()
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

// affichage
// c'est l'opérateur d'affichage
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

//ancienne versioin de evolue()

//void Systeme::evolue() {
  //for (size_t i = 0; i < particules.size(); i++) {
    // force perso
    //particules[i]->ajouteForce(eta_milieu, rho_milieu);

    // on ajoute a la particule i la force qu'exerce l'obstactle j
    //for (size_t j = 0; j < obstacles.size(); j++) {
      //particules[i]->ajouteForce(*obstacles[j]);
    //}

    // on ajoute a la particule i la force qu'exerce la particule j
    //for (size_t j = 0; j < particules.size(); j++) {
      //if (i != j) {
       // particules[i]->ajouteForce(*particules[j]);
      //}
   // }
  //}

  // après avoir calcule la force pour toute les particules on les applique à
  // chaque particules. Ce choix d'algorithme nous semble plus "physiquement"
  // logique.
  //for (auto particule : particules) {
   // particule->bouger(dt);
  //}
//}

void Systeme::evolue() {
  // On choisit une taille de case
  // Ici je prends 2.1 * SIGMA pour être strictement plus grand que 2*SIGMA.
  //P12 : Grille grille(2.1 * SIGMA, 100, 100, 100);
  //P13:
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
    // on ne regarde que les particules dans la même case et les cases voisines directes

    vector<Particule*> candidates = grille.voisines(*particules[i]);

    for (auto autre : candidates) {
      // Il faut éviter qu'une particule interagisse avec elle-même
      if (autre != particules[i]) {
        particules[i]->ajouteForce(*autre);
      }
    }
  }

  // Après avoir calculé toutes les forces, on déplace les particules
  //
  // on ne bouge les particules après avoir calculé toutes les forces 
  for (auto particule : particules) {
    particule->bouger(dt);
  }
}


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
    // fichiers[i] << "t x y z\n";
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
