
#include "ParticuleNeige.h"
#include "Systeme.h"
#include <fstream>

using namespace std;

int main() {
  Systeme systeme;

  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), 0.4));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(1, 0, 0), Vecteur3D(0, 0.2, 0), 0.15));
  systeme.ajouteParticule(
      new ParticuleNeige(Vecteur3D(0, 0, 1), Vecteur3D(0, 0, -0.5), 0.1));

  systeme.dataEvolution(0.1); // pour mettres les données dans un nouveau
  // dossier data
  // systeme.affichageEvolution(0.1, cout); // pour un affichage détaillé

  return 0;
}
