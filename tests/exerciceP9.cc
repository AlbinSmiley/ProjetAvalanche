#include <cmath>
#include <iostream>

#include "Systeme.h"

using namespace std;

int main() {
  Systeme systeme;

  systeme.ajouteParticule(
      new Particule(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(
      new Particule(Vecteur3D(1, 0, 0), Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(new Particule(Vecteur3D(0.5, sqrt(3.0) / 2.0, 0),
                                        Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(
      new Particule(Vecteur3D(0.5, sqrt(3.0) / 6.0, sqrt(6.0) / 3.0),
                    Vecteur3D(0, 0, 0), 0.4));

  systeme.ajouteObstacle(new Plan(Vecteur3D(0, 0, -0.9), Vecteur3D(0, 0, 1)));

  cout << systeme << endl;
  return 0;
}
