#include "Particule.h"
#include "Plan.h"
#include "Systeme.h"
#include "Vecteur3D.h"
#include "raygui.h"
#include "raylib_render.h"

using namespace std;

int main() {
  Systeme systeme;

  systeme.ajouteParticule(
      new Particule(Vecteur3D(0, 0, 0), Vecteur3D(1, 0, 0), 0.1));
  systeme.ajouteParticule(
      new Particule(Vecteur3D(1, 0, 0), Vecteur3D(0, 0.2, 0), 0.15));
  systeme.ajouteParticule(
      new Particule(Vecteur3D(0, 0, 1), Vecteur3D(0, 0, -0.5), 0.1));

  systeme.ajouteObstacle(new Plan(Vecteur3D(0, 0, -0.9), Vecteur3D(0, 0, 1)));

  RaylibRender vue3D;
  vue3D.run(systeme);

  return 0;
}
