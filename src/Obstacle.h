#pragma once

#include "Vecteur3D.h"

class Obstacle {
protected:
    Vecteur3D position;

public:
    Obstacle(Vecteur3D const& position);
    Vecteur3D getPosition() const;
    virtual Vecteur3D PointPlusProche(Vecteur3D const& x_i) const = 0; //car chauqe forme géométrique a une facon différente de claucler le point le plus proche 
    //je laisse le constructeur par défaut

};