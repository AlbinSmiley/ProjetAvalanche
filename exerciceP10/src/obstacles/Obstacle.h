#pragma once

#include "Dessinable.h"
#include "SupportADessin.h"
#include "Vecteur3D.h"

class Obstacle : public Dessinable {
protected:
  Vecteur3D position;

public:
  Obstacle(Vecteur3D const &position); // constructeur
  virtual ~Obstacle() = default;       // destructeur qui doit etre virtual car
                                       // Obstacle est une classe polymorphe

  Vecteur3D getPosition() const;

  virtual Vecteur3D PointPlusProche(Vecteur3D const &x_i)
      const = 0; // car chauqe forme géométrique a une facon différente de
                 // calculer le point le plus proche

  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  } // elle demande au support de "me" dessiner
};

std::ostream &operator<<(std::ostream &, Obstacle const &);
