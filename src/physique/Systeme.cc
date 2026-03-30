#include "Systeme.h"
#include "Particule.h"
#include "TextViewer.h"
#include "Vecteur3D.h"
#include "constantes.h"
#include <execution>
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
    // force perso
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

void Systeme::evolution(double t_final, ostream &out) {
  double t = 0;
  out << "Condition initiale du système : " << endl;
  out << (*this) << endl;
  do {
    out << "----------------------------- t = " << t
        << " -----------------------------" << endl;
    for (size_t i = 0; i < particules.size(); i++) {
      out << i + 1 << " : " << *particules[i] << endl;
    }
    evolue();
    t += dt;
  } while (t <= t_final);
}

void Systeme::dataEvolution(double t_final) {
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

void affichageForcePerso(Particule *part, double eta, double rho,
                         ostream &out) {
  out << "\t\tf= "
      << part->get_force()
      // << "---(l=" << (part->lambda(eta, rho)).norme()
      << "---(l=" << part->lambda(eta, rho) << ")--> f= " << part->ajouteForce()
      << endl;
}

void affichageForceLJ(double dist, ostream &out) {
  out << "\t\tforceLJ: 24 * " << EPSILON << " / " << SIGMA << "^2 * f(" << dist
      << " / " << SIGMA << ")" << endl;
  out << "\t\t\t = " << 24 * EPSILON / (SIGMA * SIGMA) << " * "
      << facteur_f(dist / SIGMA) << endl;
  out << "\t\t\t = " << 24 * EPSILON / (SIGMA * SIGMA) * facteur_f(dist / SIGMA)
      << endl;
}

void affichageForceObstacle(Particule *part, Obstacle *obst, ostream &out) {
  Vecteur3D ppp = obst->PointPlusProche(part->get_position());
  double dist = (ppp - (part->get_position())).norme();
  out << "\t\tpoint plus proche = " << ppp << ", distance = " << dist << endl;
  affichageForceLJ(dist, out);
  out << "\t\tf= " << part->ajouteForce(*obst) << ", f=" << part->get_force()
      << endl;
}

void affichageForceParticule(Particule *main_part, Particule *sec_part,
                             ostream &out) {
  double dist = distance(*main_part, *sec_part);
  out << "\t\tdistance entre particules = " << dist << endl;
  affichageForceLJ(dist, out);
  out << "\t\tdf= " << main_part->ajouteForce(*sec_part)
      << ", f= " << main_part->get_force() << endl;
}

void affichageBouger(Particule *main_part, double dt, ostream &out) {
  Vecteur3D x1 = main_part->get_position();
  Vecteur3D v1 = main_part->get_vitesse();
  main_part->bouger(dt);
  Vecteur3D x2 = main_part->get_position();
  Vecteur3D v2 = main_part->get_vitesse();

  out << "\tf = " << main_part->get_force() << endl;
  out << "\tdv= " << v2 - v1 << endl;
  out << "\tdx= " << x2 - x1 << endl;
  out << "\tx = " << x2 << endl;
  out << "\tv = " << v2 << endl;
}

void Systeme::affichageEvolution(double t_final, ostream &out) {
  double t = 0;

  do {
    out << "\n============================================================\n";
    out << "                      Temps : " << t << "\n";
    out << "============================================================\n\n";

    out << (*this) << "\n";

    out << "\n---------------------- evolue() -----------------------------\n";

    for (size_t i = 0; i < particules.size(); i++) {
      out << "\n[Particule " << i + 1 << "]\n";

      out << "(a) Force \"perso\" :\n";
      affichageForcePerso(particules[i], eta_milieu, rho_milieu, out);

      out << "(b) Forces des obstacles :\n";
      for (size_t j = 0; j < obstacles.size(); j++) {
        out << "\t\t- Obstacle " << j + 1 << "\n";
        affichageForceObstacle(particules[i], obstacles[j], out);
      }

      out << "(c) Forces des autres particules :\n";
      for (size_t j = 0; j < particules.size(); j++) {
        if (j != i) {
          out << "\t\t------ Particule " << j + 1 << "------" << "\n";
          affichageForceParticule(particules[i], particules[j], out);
        }
      }
    }

    out << "\n---------------------- bouger() -----------------------------\n";

    for (size_t i = 0; i < particules.size(); i++) {
      out << "\n[Particule " << i + 1 << "]" << endl;
      affichageBouger(particules[i], dt, out);
      out << "\t------" << endl;
    }
    t += dt;

  } while (t <= t_final);
}
