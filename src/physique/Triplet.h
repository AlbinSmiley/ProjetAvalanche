#pragma once

// Triplet représente les coordonnées entières d'une case de la grille.
// Par exemple, la case (2, -1, 0).
struct Triplet {
  int x;
  int y;
  int z;

  // Nécessaire pour utiliser Triplet comme clé dans std::map.
  // std::map doit savoir comparer deux Triplet pour les ranger.
  bool operator<(Triplet const& autre) const {
    if (x != autre.x) return x < autre.x;
    if (y != autre.y) return y < autre.y;
    return z < autre.z;
  }
};