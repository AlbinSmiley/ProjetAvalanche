#include "Plan.h"


Plan ::Plan(Vecteur3D const& position, Vecteur3D const& normale)
    : Obstacle(position), normale(~normale){} //la formule de projection marche seuleemnt si la norme est unitaire(défini dans Vecteur3D)
//les getters

Vecteur3D Plan::getNormale() const {
    return normale;
}

//la projection
Vecteur3D Plan::PointPlusProche(Vecteur3D const& x_i) const {
    Vecteur3D OP = x_i - position;
    double coeff(OP * normale); //c'est le produit scalaire
    return x_i -coeff * normale;
}

