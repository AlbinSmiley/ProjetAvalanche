#include "Source.h"
#include <iostream>

using namespace std;

int main() {

  Particule modele(Vecteur3D(0, 0, 0), Vecteur3D(1, 2, 3), 0.4, 12.5);

  Vecteur3D origine(0, 0, 0);
  Vecteur3D vitesseInitial(1, 2, 3);

  double ecart_type_vitesse = 0.5;
  double ecart_type_rayon = 0.5;
  double debit = 100;
  double dt = 0.1;

  Source source(modele, origine, vitesseInitial, ecart_type_vitesse,
                ecart_type_rayon, debit);
  EnsembleParticule ensemble = {};

  source.creation(ensemble, dt);

  for (auto const &part : ensemble) {
    cout << *part << endl;
  }
  return 0;
}
