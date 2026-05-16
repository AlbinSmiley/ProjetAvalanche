#include <cmath>

#include "ParticuleNeige.h"
#include "Vecteur3D.h"
#include "constantes.h"

using namespace std;
using namespace cst;

double facteur_f(double x) { // calcul du facteur qui dépend de la distance
  // relative à sigma entre particule (x = distance/sigma)
  double f;
  if (x <= 1.0) {
    f = -1.0;
  } else if (x >= 2) {
    f = 0.0;
  } else {
    f = (pow(x, 6) - 2) / (pow(x, 13));
  }
  return f;
}

double ParticuleNeige::facteurLJ(double dis) const {
  // calcul du facteur de Lenner-Jones pour la force associé
  double x = dis / SIGMA;
  return 24 * EPSILON * facteur_f(x) / (SIGMA * SIGMA);
}

double ParticuleNeige::forceLJ(ParticuleNeige const &particule)
    const & { // calcul de la norme de la force de Lenner-Jones
  double dis = distance((*this), particule);
  return facteurLJ(dis);
}

void ParticuleNeige::opere_sur(ParticuleNeige &other) const {
  other.add_force(forceLJ(other) * (~(ecartOriente(other, *this))));
}
