#include <cmath>
#include <iostream>

#include "Particule.h"
#include "Vecteur3D.h"
#include "constantes.h"

using namespace std;
using namespace cst;

const double Particule::masse()
    const { // on part du principe qu'une particule est une sphère
  return (4 * PI * rho_ * rayon_ * rayon_ * rayon_) / 3;
}

ostream &operator<<(ostream &out, Particule const &particule) {
  out << "[ pos = " << particule.get_position()
      << ", vit = " << particule.get_vitesse()
      << ", m = " << particule.get_masse() << ", r = " << particule.get_rayon()
      << " ]";
  return out;
}

Vecteur3D ecartOriente(Particule const &p1, Particule const &p2) {
  return p2.get_position() - p1.get_position();
}

double distance(Particule const &p1, Particule const &p2) {
  return (ecartOriente(p1, p2)).norme();
}

double facteur_f(double x) {
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

double facteurLJ(double dis) {
  double x = dis / SIGMA;
  return 24 * EPSILON * facteur_f(x) / (SIGMA * SIGMA);
}

double Particule::forceLJ(Particule const &particule) const & {
  double dis = distance((*this), particule);
  return facteurLJ(dis);
}

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

Vecteur3D Particule::ajouteForce(Vecteur3D const &force) {
  force_ += force;
  return force;
}
Vecteur3D Particule::ajouteForce(double eta_milieu_, double rho_milieu_) {
  Vecteur3D df = get_masse() * G - lambda(eta_milieu_, rho_milieu_);
  force_ += df;
  return df;
}
Vecteur3D Particule::ajouteForce(Particule const &particule) {
  Vecteur3D df = (forceLJ(particule)) * (~(ecartOriente((*this), particule)));
  force_ += df;
  return df;
}

void Particule::bouger(double dt) {
  vitesse_ += force_ * (dt / masse_);
  position_ += dt * vitesse_;

  force_ = Vecteur3D(0.0, 0.0, 0.0);
}

void Particule::setRayon(double rayon) { rayon_ = rayon; }
void Particule::setVitesse(Vecteur3D const &vitesse) {
  vitesse_.set_x(vitesse.get_x());
  vitesse_.set_y(vitesse.get_y());
  vitesse_.set_z(vitesse.get_z());
}

// la méthode ajouteForce
Vecteur3D Particule::ajouteForce(Obstacle const &plan) {

  Vecteur3D P = plan.PointPlusProche(position_);
  Vecteur3D e = P - position_; // vecteur entre le plan et la particule

  double d = e.norme(); // distance entre la particule et le plan

  if (d < PRECISION)
    return Vecteur3D(0, 0, 0); // sécurité si la particule est exacteemtn sur le
                               // plan (division par 0)

  Vecteur3D u = ~e;

  double F = 2 * facteurLJ(d);

  Vecteur3D df = F * u;

  force_ += df;

  return df;
}
