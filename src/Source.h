#pragma once
#include "Aleatoire.h"
#include "Particule.h"
#include <memory>
#include <vector>

using EnsembleParticule = std::vector<Particule *>;

class Source {
private:
  Particule const &modele_;
  Vecteur3D position_;
  Vecteur3D vitesse_moyenne_initial_;
  double ecart_type_vitesse_initial_;
  double ecart_type_rayons_;
  double debit_;
  bool etat_;

public:
  Source(Particule const &modele, Vecteur3D const &position,
         Vecteur3D const &vitesse_moyenne_initial,
         double ecart_type_vitesse_initial, double ecart_type_rayons,
         double debit, double etat = true)
      : modele_(modele), position_(position),
        vitesse_moyenne_initial_(vitesse_moyenne_initial),
        ecart_type_vitesse_initial_(ecart_type_vitesse_initial),
        ecart_type_rayons_(ecart_type_rayons), debit_(debit), etat_(etat) {}

  void on();
  void off();

  void creation(EnsembleParticule &, double, Aleatoire &);
};
