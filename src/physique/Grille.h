#pragma once

using namespace std;
#include <map>
#include <vector>

#include "Particule.h"
#include "Triplet.h"
#include "Vecteur3D.h"

class Grille {
private:
  // Taille d'une case.
  // Elle doit être choisie > 2*sigma.
  double pas_;

  // À chaque case, on associe la liste des particules qu'elle contient.
  map<Triplet,vector<Particule*>> cases_;

public:
  // Constructeur : on donne le pas d'espace.
  explicit Grille(double pas);

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