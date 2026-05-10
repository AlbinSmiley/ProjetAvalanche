using namespace std;

#include "Grille.h"

// Constructeur : on crée un tableau 3D de dimensions nx * ny * nz.
Grille::Grille(double pas, int nx, int ny, int nz)
    : pas_(pas), nx_(nx), ny_(ny), nz_(nz)
{
  cases_.resize(nx_);

  for (int i = 0; i < nx_; ++i) {
    cases_[i].resize(ny_);

    for (int j = 0; j < ny_; ++j) {
      cases_[i][j].resize(nz_);
    }
  }
}

// Vide toutes les cases, sans supprimer la grille elle-même.
void Grille::vide() {
  for (int i = 0; i < nx_; ++i) {
    for (int j = 0; j < ny_; ++j) {
      for (int k = 0; k < nz_; ++k) {
        cases_[i][j][k].clear();
      }
    }
  }
}

// Transforme une position réelle en coordonnées de case.
Triplet Grille::case_de(Vecteur3D const& position) const {
  int i = int(position.get_x() / pas_);
  int j = int(position.get_y() / pas_);
  int k = int(position.get_z() / pas_);

  return {i, j, k};
}

// Vérifie qu'une case existe dans le tableau 3D.
bool Grille::est_dans_grille(Triplet const& c) const {
  return (c.x >= 0 and c.x < nx_ and
          c.y >= 0 and c.y < ny_ and
          c.z >= 0 and c.z < nz_);
}

// Ajoute une particule dans sa case.
void Grille::ajoute(Particule* p) {
  Triplet c = case_de(p->get_position());

  // Avec un tableau 3D, il faut vérifier que les indices existent.
  if (est_dans_grille(c)) {
    cases_[c.x][c.y][c.z].push_back(p);
  }
}

// Reconstruit la grille à partir des positions actuelles.
void Grille::remplit(vector<Particule*> const& particules) {
  vide();

  for (vector<Particule*>::const_iterator p(particules.begin());
       p != particules.end();
       ++p) {
    ajoute(*p);
  }
}

// Renvoie les particules dans la case de p et les cases voisines.
vector<Particule*> Grille::voisines(Particule const& p) const {
  vector<Particule*> resultat;

  Triplet c = case_de(p.get_position());

  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      for (int dz = -1; dz <= 1; ++dz) {

        Triplet voisine{c.x + dx, c.y + dy, c.z + dz};

        if (est_dans_grille(voisine)) {

          vector<Particule*> const& contenu =
              cases_[voisine.x][voisine.y][voisine.z];

          for (vector<Particule*>::const_iterator particule(contenu.begin());
               particule != contenu.end();
               ++particule) {
            resultat.push_back(*particule);
          }
        }
      }
    }
  }

  return resultat;
}