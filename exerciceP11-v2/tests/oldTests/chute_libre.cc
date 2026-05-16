#include <cmath>
#include <iostream>

#include "Systeme.h"

using namespace std;

int main() {
  Systeme systeme;

  systeme.ajouteParticule(
      new Particule(Vecteur3D(0, 0, 0), Vecteur3D(5, 0, 7), 0.4));

  systeme.set_dt(0.01);

  systeme.evolution(0.06, cout);

  return 0;
}
