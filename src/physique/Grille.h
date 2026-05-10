#pragma once

using namespace std;
#include <vector>

#include "Particule.h"
#include "Triplet.h"
#include "Vecteur3D.h"

class Grille {
private:
  private:
  double pas_;

  int nx_;
  int ny_;
  int nz_;

  vector<vector<vector<vector<Particule*>>>> cases_;

  bool est_dans_grille(Triplet const& c) const;

  // Tableau tridimensionnel de cases.

  // cases_[i][j][k] contient la liste des particules

  // présentes dans la case (i,j,k)

  
  

public:
  // Constructeur : 
 Grille(double pas, int nx, int ny, int nz);

  // Supprime toutes les particules dans la grille.
  // Utile avant de reconstruire la grille à chaque étape.
  void vide();

  // Donne la case correspondant à une position.
  Triplet case_de(Vecteur3D const& position) const;

  // Ajoute une particule dans la bonne case.
  void ajoute(Particule* p);

  // Remplit la grille avec toutes les particules du système.
  void remplit(vector<Particule*> const& particules);

  // Donne toutes les particules dans la case de p et les cases voisines.
  vector<Particule*> voisines(Particule const& p) const;


};