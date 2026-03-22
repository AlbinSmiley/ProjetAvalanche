#include "Obstacle.h"

Obstacle::Obstacle(Vecteur3D const &position) : position(position) {}

Vecteur3D Obstacle::getPosition() const { return position; }
