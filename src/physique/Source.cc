#include "Source.h"
#include "Particule.h"

using namespace std;

void Source::on() { etat_ = true; }
void Source::off() { etat_ = false; }

void Source::creation(vector<Particule *> &ensemble, Aleatoire &generateur,
                      double dt, double eta_milieu, double rho_milieu) {
  if (etat_ == true) {
    double frac = debit_ * dt;
    int nombre = frac;
    frac -= nombre;
    if (generateur.uniforme(0.0, 1.0) < frac) {
      ++nombre;
    }

    for (int i = 0; i < nombre; i++) {
      // Particule* copie = &modele_;
      Particule *copie = modele_.clone();

      double mean_x = vitesse_moyenne_initial_.get_x();
      double mean_y = vitesse_moyenne_initial_.get_y();
      double mean_z = vitesse_moyenne_initial_.get_z();

      double mean_rayon = modele_.get_rayon();

      Vecteur3D nouvelleVitesse(
          generateur.gaussienne(mean_x, ecart_type_vitesse_initial_),
          generateur.gaussienne(mean_y, ecart_type_vitesse_initial_),
          generateur.gaussienne(mean_z, ecart_type_vitesse_initial_));

      copie->setPosition(position_);
      copie->setVitesse(nouvelleVitesse);
      copie->setRayon(generateur.gaussienne(mean_rayon, ecart_type_rayons_));

      copie->ajouteForce(eta_milieu, rho_milieu);
      copie->bouger(dt);

      ensemble.push_back(copie);
    }
  } else {
    return;
  }
}

// getter:
Vecteur3D Source::getPosition() const { return position_; }

ostream &operator<<(ostream &out, Source const &s) {
  out << "Source de position " << s.getPosition();
  return out;
}
