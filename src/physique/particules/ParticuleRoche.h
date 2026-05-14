#pragma once

#include "Particule.h"
#include "SupportADessin.h"
#include "constantes.h"

//Déclaration anticipée :
//on dit juste au compilateur que cette classe existe.
class ParticuleNeige;

// interaction plus simple elle est juste essentiellement répulsive
class ParticuleRoche : public Particule {
public:
  // Attribut statique publique qu'on pose en tant qu'alias pour eviter la copie
  // et pour ne pas avoir à specifier le namespace à chaque fois
  static constexpr double epsilon = cst::EPSILON;
  static constexpr double sigma = cst::SIGMA;

  using Particule::Particule; // on a les même constructeur

  //calcule une force repulsive simple 
  double forceRepulsive(Particule const& autre) const;
  
  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  }

  //interactioin roche->roche
  virtual void opere_sur(ParticuleRoche &) const override;
  //interaction roche -> neige
  virtual void opere_sur(ParticuleNeige &) const override;
  //demande à lautre d'agir sur la particule
  virtual void ajouteForce(Agent const &autre) override {
    autre.opere_sur(*this);
  }
//copie polymorphique 
  Particule *clone() const override { return new ParticuleRoche(*this); }
};
