#include "Dalle.h"

// constructeur
Dalle::Dalle(Vecteur3D const& position,Vecteur3D const& normale, double largeur,double longueur,Vecteur3D const& directionLongueur)
    : Plan(position, normale),
      largeur(largeur),
      longueur(longueur),
      directionLongueur(~directionLongueur)
{}
