#include <cmath>

#include "ParticuleNeige.h"
#include "ParticuleRoche.h"
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

void ParticuleNeige::opere_sur(ParticuleRoche &other) const {
  //distance entre la particule et la neige  
  double dis = distance(*this, other);
  //cas de sécurité si les deux particules sont au meme endroit 
   if (dis == 0.0) {
    return;
  }

  //si les particules sont trop loin 
  if (dis >= 2.0 * SIGMA) {
    return;
  }

//permet d'avoir la direction
  Vecteur3D direction = ~(ecartOriente(other, *this));

  //ici on a une repulsion plus faible qu'avec roche-roche
//plus les particules sont ptroches plus la force devient grande
   double force = 0.5 * EPSILON * (2.0 * SIGMA - dis) / SIGMA;

   //on ajoute la force à la roche 
   other.add_force(force * direction);
  }
