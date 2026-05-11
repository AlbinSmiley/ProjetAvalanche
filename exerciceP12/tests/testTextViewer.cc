#include "ParticuleNeige.h"
#include "Plan.h"
#include "Systeme.h"
#include "TextViewer.h"

using namespace std;

int main() {
  Systeme systeme;

  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(1, 0, 0), Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(new ParticuleNeige(Vecteur3D(0.5, sqrt(3.0) / 2.0, 0),
                                             Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(0.5, sqrt(3.0) / 6.0, sqrt(6.0) / 3.0),
                         Vecteur3D(0, 0, 0), 0.4));

  systeme.ajouteObstacle(new Plan(Vecteur3D(0, 0, -0.9), Vecteur3D(0, 0, 1)));
  // systeme.set_dt(0.001);
  // systeme.set_eta(1.8e-3);
  // systeme.set_rho(1.3e-3);

  TextViewer vueCLI(cout);
  vueCLI.dessine(systeme);

  systeme.evolue();

  vueCLI.dessine(systeme);

  return 0;
}
