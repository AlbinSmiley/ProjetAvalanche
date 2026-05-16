#include "ParticuleNeige.h"
#include "Plan.h"
#include "Systeme.h"
#include "Vecteur3D.h"
#include "raygui.h"
#include "raylib_render.h"

using namespace std;

int main() {
  Systeme systeme;

  ParticuleNeige modele(Vecteur3D(), Vecteur3D(), 0.1);

  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(), Vecteur3D(1, 0, 0), 0.1));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(1, 0, 0), Vecteur3D(0, 0.2, 0), 0.15));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(0, 0, 1), Vecteur3D(0, 0, -0.5), 0.1));

  systeme.ajouteObstacle(new Plan(Vecteur3D(0, 0, -2), Vecteur3D(0, 0, 1)));

  systeme.ajouteSource(
      new Source(modele, Vecteur3D(), Vecteur3D(0, 0, 2), 1, 0.2, 100));

  RaylibRender vue3D;
  vue3D.run(systeme);

  return 0;
}
