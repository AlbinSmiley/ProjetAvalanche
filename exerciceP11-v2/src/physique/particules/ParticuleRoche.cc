#include <cmath>

#include "ParticuleRoche.h"
#include "Vecteur3D.h"
#include "constantes.h"
#include "ParticuleNeige.h"

using namespace std;
using namespace cst;

double ParticuleRoche::forceRepulsive(Particule const& autre) const {

  // distance entre les deux particules

  double dis = distance(*this, autre);

  /*
   * sécurité : si les deux particules sont exactement au même endroit,
   * on évite une division par 0 ou une direction impossible.
   */

  if (dis == 0.0) {
    return 0.0;

  }
  /*
   * Si les particules sont trop éloignées alors on considère qu'elles ne s'influencent plus
   * Ici on choisit arbitrairement -> portée maximale = 2 * SIGMA
   */

  if (dis >= 2.0 * SIGMA) {
    return 0.0;
  }

  /*Force répulsive simple.
   * Plus la distance est petiteplus la force devient grande
   * Quand dis = 2*SIGMA :
   *      force = 0 (choix)
   * Quand dist diminue : force augment
   */

  return EPSILON * (2.0 * SIGMA - dis) / SIGMA;

}
//interaction roche -> roche
void ParticuleRoche::opere_sur(ParticuleRoche &other) const {
  
  Vecteur3D direction = ~(ecartOriente(other, *this));
  //ecartOriente donne le vecteur et on normalise la direction 
  double force = forceRepulsive(other);
  //on clalcule la norme de la force repulsive
  other.add_force(2.0 * force * direction);
  //on a décidé que lorsqu'une roche rencontre une roche alors on multiplie par 2 
  //(la force repulsive est plus forte qu'avec une neige )
}

void ParticuleRoche::opere_sur(ParticuleNeige& other) const {
  Vecteur3D direction = ~(ecartOriente(other, *this));
   double force = forceRepulsive(other);
   other.add_force(force * direction);
}
