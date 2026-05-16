#include "Obstacle.h"

Obstacle::Obstacle(Vecteur3D const &position) : position(position) {}

Vecteur3D Obstacle::getPosition() const { return position; }

std::ostream &operator<<(std::ostream &out, Obstacle const &o) {
  out << "Obstacle de position " << o.getPosition();
  return out;
}
