#include "Particule.h"
#include "Vecteur3D.h"
#include "constantes.h"

using namespace std;
using namespace cst;

ostream &operator<<(ostream &out, Particule const &particule) {
  out << "[ pos = " << particule.get_position()
      << ", vit = " << particule.get_vitesse()
      << ", m = " << particule.get_masse() << ", r = " << particule.get_rayon()
      << " ]";
  return out;
}

const double Particule::masse()
    const { // on part du principe qu'une particule est une sphère
  return (4 * PI * rho_ * rayon_ * rayon_ * rayon_) / 3;
}

Vecteur3D ecartOriente(Particule const &p1, Particule const &p2) {
  return p2.get_position() - p1.get_position();
}

double distance(Particule const &p1, Particule const &p2) {
  return (ecartOriente(p1, p2)).norme();
}

void Particule::bouger(double dt) {
  vitesse_ += force_ * (dt / masse_);
  position_ += dt * vitesse_;

  force_ = Vecteur3D(0.0, 0.0, 0.0);
}

void Particule::setRayon(double rayon) { rayon_ = rayon; }
void Particule::setVitesse(Vecteur3D const &vitesse) { vitesse_ = vitesse; }

Vecteur3D Particule::lambda(double eta_milieu_, double rho_milieu_) const {
  double lamb;

  double vit = (get_vitesse()).norme();
  double temp = (80 * eta_milieu_) / (3 * rho_milieu_ * get_rayon());

  bool condition = (vit <= temp);

  if (condition) {
    lamb = 6 * PI * get_rayon() * eta_milieu_;
  } else {
    lamb = (9 * PI * get_rayon() * get_rayon() * rho_milieu_ * vit) / 40;
  }

  Vecteur3D result = get_vitesse();
  result *= lamb;

  return result;
}

void Particule::ajouteForce(double eta_milieu_, double rho_milieu_) {
  add_force(get_masse() * G - lambda(eta_milieu_, rho_milieu_));
}
