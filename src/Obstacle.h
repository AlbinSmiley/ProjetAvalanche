#pragma once

#include "Vecteur3D.h"

class Obstacle {
protected:
    Vecteur3D position;

public:
    Obstacle(Vecteur3D const& position);
    Vecteur3D getPosition() const;
};