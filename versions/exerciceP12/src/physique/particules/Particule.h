#pragma once

#include "Agent.h"
#include "Dessinable.h"
#include "SupportADessin.h"
#include "Vecteur3D.h"
#include "constantes.h"

class Particule : public Agent, public Dessinable {
protected:
  Vecteur3D position_; // distance en mm
  Vecteur3D vitesse_;
  double rayon_;
  double rho_; // mg/mm³

  /*
      Puisque la masse d'une particule n'est pas susceptible de changer on la
     définit comme attribut qui seras calculer par le constructeur en utilisant
     la méthode masse().

      Cela permet de limiter du potentiel calcul.
  */
  double masse_; // mg
  const double masse() const;

  // attribut suseptible de changer
  Vecteur3D force_;

  virtual Vecteur3D lambda(double eta_milieu_, double rho_milieu_) const;

public:
  // constructeur
  Particule(Vecteur3D const &position, Vecteur3D const &vitesse, double rayon,
            double rho = cst::RHO_PARTICULE // par défaut les particules ont
                                            // toutes la même masse volumique
            )
      : position_(position), vitesse_(vitesse), rayon_(rayon), rho_(rho),
        masse_(masse()) {}

  // constructeur par copie
  Particule(Particule const &autre)
      : position_(autre.position_), vitesse_(autre.vitesse_),
        rayon_(autre.rayon_), rho_(autre.rho_), masse_(autre.masse_) {}

  // Getters pour les méthodes et surcharge externe
  Vecteur3D get_position() const { return position_; }
  Vecteur3D get_vitesse() const { return vitesse_; }
  double get_rayon() const { return rayon_; }
  double get_rho() const { return rho_; }
  double get_masse() const {
    return masse_;
  } // un getter pour la masse car la méthode est privé et comme ça la classe et
    // plus homogène
  Vecteur3D get_force() const { return force_; }
  void add_force(Vecteur3D const &f) { force_ += f; }

  void setVitesse(Vecteur3D const &);
  void setRayon(double);

  void bouger(double dt = cst::DT);

  virtual void ajouteForce(Agent const &) = 0;
  // les seul méthodes qui ne dependent pas du type de particules
  virtual void ajouteForce(double eta_milieu_, double rho_milieu_);
  virtual Particule *clone() const = 0;
};

std::ostream &operator<<(std::ostream &, Particule const &);

Vecteur3D ecartOriente(Particule const &, Particule const &);
double distance(Particule const &, Particule const &);
