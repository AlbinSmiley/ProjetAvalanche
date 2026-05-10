using namespace std;
#include "Grille.h"

#include <cmath>


Grille::Grille(double pas)
    : pas_(pas)
{}

// On vide toutes les cases.
// Après ça, la grille ne contient plus aucune particule.
void Grille::vide() {
  cases_.clear();
}

// Cette fonction transforme une position réelle en coordonnées entières de case.
//
// Exemple :
// si pas_ = 1.0 et position = (2.3, 4.8, -0.2)
// alors la case est (2, 4, -1)
//
// il faut juste prendre en compte que int(-0.2) donne 0 et pas -1 mais c'est un choix 
Triplet Grille::case_de(Vecteur3D const& position) const {
  

  int i = int(position.get_x() / pas_);
  int j = int(position.get_y() / pas_);
  int k = int(position.get_z() / pas_);

  return {i, j, k};
}

// Ajoute une particule dans la case correspondant à sa position actuelle.
void Grille::ajoute(Particule* p) {
  Triplet c = case_de(p->get_position());

  // cases_[c] crée la case si elle n'existe pas encore.
  cases_[c].push_back(p);
}

// Reconstruit toute la grille à partir des positions actuelles des particules.
void Grille::remplit(vector<Particule*> const& particules) {
  vide();

  for (auto p : particules) {
    ajoute(p);
  }
}

// Renvoie les particules dans la case de p et dans les 26 cases voisines.
// En 3D, les voisines directes sont obtenues avec :
// dx = -1, 0, 1
// dy = -1, 0, 1
// dz = -1, 0, 1
// Cela fait 3^3 = 27 cases à regarder.
vector<Particule*> Grille::voisines(Particule const& p) const {

  vector<Particule*> resultat;

  Triplet c = case_de(p.get_position());

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      for (int dz = -1; dz <= 1; ++dz) {

        Triplet voisine{c.x + dx, c.y + dy, c.z + dz};

        // Recherche de la case voisine dans la map
        map<Triplet, vector<Particule*>>::const_iterator it(
            cases_.find(voisine)
        );

        // Si la case existe
        if (it != cases_.end()) {

          // Parcours des particules contenues dans cette case
          for (vector<Particule*>::const_iterator particule(it->second.begin());
               particule != it->second.end();
               ++particule) {

            resultat.push_back(*particule);
          }
        }
      }
    }
  }

  return resultat;
}