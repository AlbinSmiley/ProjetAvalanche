#include "Plan.h"

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

// Vecteur3D ParticuleNeige::ajouteForce(Obstacle const &plan) {
//
//   Vecteur3D P = plan.PointPlusProche(position_);
//   Vecteur3D e = P - position_; // vecteur entre le plan et la particule
//
//   double d = e.norme(); // distance entre la particule et le plan
//
//   if (d < PRECISION)
//     return Vecteur3D(0, 0, 0); // sécurité si la particule est exacteemtn
//     sur le
//                                // plan (division par 0)
//
//   Vecteur3D u = ~e;
//
//   double F = 2 * facteurLJ(d);
//
//   Vecteur3D df = F * u;
//
//   force_ += df;
//
//   return df;
// }
