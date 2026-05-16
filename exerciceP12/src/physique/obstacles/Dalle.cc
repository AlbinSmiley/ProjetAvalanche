#include "Dalle.h"

// constructeur
Dalle::Dalle(Vecteur3D const& position,Vecteur3D & n, double largeur,double longueur,Vecteur3D & directionLongueur)
    : Plan(position, n),
      largeur(largeur),
      longueur(longueur),
      directionLongueur(~directionLongueur)
{}


double Dalle::getLargeur() const {
    return largeur;
}

double Dalle::getLongueur() const {
    return longueur;
}

Vecteur3D Dalle::getDirectionLongueur() const {
    return directionLongueur;
}

Vecteur3D Dalle::getDirectionLargeur() const {
    return normale ^ directionLongueur;
}

std::ostream& operator<<(std::ostream& out, Dalle const& d) {
    out << "Dalle de position " << d.getPosition()
        << ", normale " << d.getNormale()
        << ", largeur " << d.getLargeur()
        << ", longueur " << d.getLongueur();
    return out;
}