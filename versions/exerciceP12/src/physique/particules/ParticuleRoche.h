#pragma once

#include "Particule.h"
#include "SupportADessin.h"
#include "constantes.h"

class ParticuleRoche : public Particule {
public:
  // Attribut statique publique qu'on pose en tant qu'alias pour eviter la copie
  // et pour ne pas avoir à specifier le namespace à chaque fois
  static constexpr double epsilon = cst::EPSILON;
  static constexpr double sigma = cst::SIGMA;

  using Particule::Particule; // on a les même constructeur

  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  }

  virtual void opere_sur(ParticuleRoche &) const override;
  virtual void opere_sur(ParticuleNeige &) const override;
  virtual void ajouteForce(Agent const &autre) override {
    autre.opere_sur(*this);
  }

  Particule *clone() const override { return new ParticuleRoche(*this); }
};
