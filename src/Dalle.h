#pragma once

#include "Plan.h"

class Dalle : public Plan { // Dalle hérite de Plan
private:                    //"les nouvelles informations"
  double largeur;
  double longueur;
  Vecteur3D
      directionLongueur; // vecteur unitaire dans la direction de la longueur

public:
  // le constructeur
  Dalle(Vecteur3D const &, Vecteur3D const &, double, double,
        Vecteur3D const &);
};
