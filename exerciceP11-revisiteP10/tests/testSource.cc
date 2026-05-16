#include "ParticuleNeige.h"
#include "Source.h"
#include <iostream>

using namespace std;

int main() {

  ParticuleNeige modele(Vecteur3D(0, 0, 0), Vecteur3D(1, 2, 3), 0.4, 12.5);

  Vecteur3D origine(0, 0, 0);
  Vecteur3D vitesseInitial(1, 2, 3);

  // initialisation des paramètres (pour générer 5 particules par unité de
  // temps)
  double ecart_type_vitesse = 0.5;
  double ecart_type_rayon = 0.5;
  double debit = 50;
  double dt = 0.1;

  // Appel au constructeur de Source
  Source source(modele, origine, vitesseInitial, ecart_type_vitesse,
                ecart_type_rayon, debit);
  vector<Particule *> ensemble = {};

  Aleatoire generateur;

  // Creation de particules
  source.creation(ensemble, generateur, dt);

  for (auto const &part : ensemble) {
    cout << *part << endl;
  }

  for (Particule *part : ensemble) {
    delete part;
  }
  ensemble.clear();
  return 0;
}
