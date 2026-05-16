#include "Plan.h"
#include "ParticuleRoche.h"

Plan ::Plan(Vecteur3D const &position, Vecteur3D const &normale)
    : Obstacle(position), normale(~normale) {
} // la formule de projection marche seuleemnt si la norme est unitaire(défini
  // dans Vecteur3D)
// les getters

Vecteur3D Plan::getNormale() const { return normale; }

// la projection
Vecteur3D Plan::PointPlusProche(Vecteur3D const &x_i) const {
  Vecteur3D OP = x_i - position;
  double coeff(OP * normale); // c'est le produit scalaire
  return x_i - coeff * normale;
}

std::ostream &operator<<(std::ostream &out, Plan const &p) {
  out << "Plan d'origine " << p.getPosition() << " et de normale "
      << p.getNormale();
  return out;
}

void Plan::opere_sur(ParticuleNeige &part) const {
  Vecteur3D positionParticule = part.get_position();

  Vecteur3D P = PointPlusProche(positionParticule);
  Vecteur3D e = P - positionParticule;

  double distance = e.norme();

  part.add_force(2 * part.facteurLJ(distance) * (~e));
}

void Plan::opere_sur(ParticuleRoche &part) const {
  
  //On récupère la position actuelle de la particule de roche
  Vecteur3D positionParticule = part.get_position();

  
  //On cherche le point du plan le plus proche de la particule.
  Vecteur3D P = PointPlusProche(positionParticule);

  //e est le vecteur qui va de la particule vers le plan
  //Sa norme correspond à la distance entre la particule
  
  Vecteur3D e = P - positionParticule;
  //Distance entre la particule et le plan.

  double distance = e.norme();

  /*
   * Sécurité :
   * si la particule est exactement sur le planalors e est le vecteur nul
   * On ne peut pas normaliser un vecteur nul donc on arrête
   */
  if (distance == 0.0) {
    return;
  }

  /*
   * Si la particule est assez loin du plan,
   * on décide que le plan n'exerce pas de force.
   * Ici on prend : 2 * sigma.
   */
  if (distance >= 2.0 * ParticuleRoche::sigma) {
    return;
  }

  /*
   * Direction de la force.
   * e va de la particule vers le plan Donc -e va du plan vers la particule.
   * Comme on veut que le plan repousse la roche la force doit aller dans la direction opposée à e.
   */
  Vecteur3D direction = -(~e);

  /*
   * Force répulsive simple
   * Plus la particule est proche du plan plus la force est grande
   * Quand distance = 2*sigma -> force = 0.
   * Quand distance diminue -> force augmente.
   */
  double force = ParticuleRoche::epsilon *
                 (2.0 * ParticuleRoche::sigma - distance)
                 / ParticuleRoche::sigma;

  /*
   * On ajoute la force à la particule de roche.
   */
  part.add_force(force * direction);
}
