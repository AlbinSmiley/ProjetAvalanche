#include <cmath>
#include <iostream>

#include "Particule.h"
#include "Vecteur3D.h"
#include "constantes.h"
#include "Plan.h"

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

double Particule::forceLJ(Particule const &particule) const & {
  double f;

  double dis = distance((*this), particule);
  double x = dis / sigma;

  if (abs(x - 1) <= PRECISION) {
    f = -1.0;
  } else if (abs(2 - x) <= PRECISION) {
    f = 0.0;
  } else {
    f = (pow(x, 6) - 2) / (pow(x, 13));
  }

  return (24 * epsilon * f) / (sigma * sigma);
}

Vecteur3D Particule::lambda() const {
  double lamb;

  double vit = (get_vitesse()).norme();
  double temp = (80 * ETA_MILIEU) / (3 * RHO_MILIEU * get_rayon());

  bool condition = (abs(vit - temp) <= PRECISION);

  if (condition) {
    lamb = 6 * PI * get_rayon() * ETA_MILIEU;
  } else {
    lamb = (9 * PI * get_rayon() * get_rayon() * RHO_MILIEU * vit) / 40;
  }

  Vecteur3D result = get_vitesse();
  result *= lamb;

  return result;
}

Vecteur3D Particule::ajouteForce(Vecteur3D const &force) {
  force_ += force;
  return force;
}
Vecteur3D Particule::ajouteForce() {
  Vecteur3D df = get_masse() * G - lambda();
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
Vecteur3D Particule::ajouteForce(Plan const& plan) {

    Vecteur3D P = plan.PointPlusProche(position_);
    Vecteur3D e = position_ - P; //vecteur entre le plan et la particule

    double d = e.norme();//distance entre la particule et le plan

    if (d < PRECISION) return Vecteur3D(0,0,0); // sécurité si la particule est exacteemtn sur le plan (division par 0)

    Vecteur3D u = ~e;

    double x = d / SIGMA;
    double f;

    if (abs(x - 1) <= PRECISION) {
        f = -1.0;
    } else if (abs(2 - x) <= PRECISION) {
        f = 0.0;
    } else {
        f = (pow(x, 6) - 2) / (pow(x, 13));
    }

    double F = 2 * (24 * EPSILON * f) / (SIGMA * SIGMA); // fois 2 car obsactle fixe

    Vecteur3D df = F * u;

    force_ += df;

    return df;
}
