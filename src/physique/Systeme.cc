#include "Systeme.h"
#include "TextViewer.h"

using namespace std;

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
    out << *p << endl;
  }

  out << "et de(s) " << s.getObstacles().size()
      << " obstacles suivants :" << endl;

  for (auto const &o : s.getObstacles()) {
    (*o).dessine_sur(vue); // c'est du polymorphsime
    out << endl;
  }

  if (!s.getSources().empty()) {
    out << "et de(s) " << s.getSources().size()
        << " sources suivantes :" << endl;

    for (auto const &source : s.getSources()) {
      (*source).dessine_sur(vue);
      out << *source << endl;
    }
  }

  return out;
}

void Systeme::evolue() {
  for (size_t i = 0; i < particules.size(); i++) {
    particules[i]->ajouteForce(eta_milieu, rho_milieu);

    // on ajoute a la particule i la force qu'exerce l'obstactle j
    for (size_t j = 0; j < obstacles.size(); j++) {
      particules[i]->ajouteForce(*obstacles[j]);
    }

    // on ajoute a la particule i la force qu'exerce la particule j
    for (size_t j = 0; j < particules.size(); j++) {
      if (i != j) {
        particules[i]->ajouteForce(*particules[j]);
      }
    }
  }
  // après avoir calcule la force pour toute les particules on les applique à
  // chaque particules. Ce choix d'algorithme nous semble plus "physiquement"
  // logique.
  for (auto particule : particules) {
    particule->bouger(dt);
  }
}
