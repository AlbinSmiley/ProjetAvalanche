#pragma once

#include "Plan.h"

class Dalle : public Plan { //Dalle hérite de Plan
private: //"les nouvelles informations"
    double largeur;
    double longueur;
    Vecteur3D directionLongueur; // vecteur unitaire dans la direction de la longueur

public:
    //le constructeur
    Dalle(Vecteur3D const& position,
          Vecteur3D const& normale,
          double largeur,
          double longueur,
          Vecteur3D const& directionLongueur);

    double getLargeur() const;
    double getLongueur() const;
    Vecteur3D getDirectionLongueur() const;
    Vecteur3D getDirectionLargeur() const;

};