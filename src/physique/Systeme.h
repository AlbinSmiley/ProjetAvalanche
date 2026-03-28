#pragma once

#include <iostream>
#include <vector>

#include "Dessinable.h"
#include "Obstacle.h"
#include "Particule.h"
#include "Source.h"
#include "SupportADessin.h"
#include "constantes.h"

class Systeme : public Dessinable {
private:
  std::vector<Particule *> particules;
  std::vector<Obstacle *>
      obstacles;                 // on veut du polymorphisme donc des pointeurs
  std::vector<Source *> sources; // on veut du polymorphisme donc des pointeurs
  //
  double dt = cst::DT;
  double eta_milieu = cst::ETA_AIR;
  double rho_milieu = cst::RHO_AIR;

public:
  // constructeur par défaut = système vide
  Systeme() = default;
  Systeme(double dt_, double eta_milieu_, double rho_milieu_)
      : dt(dt_), eta_milieu(eta_milieu_), rho_milieu(rho_milieu_) {}

  ~Systeme() {
    for (auto p : particules)
      delete p;
    for (auto o : obstacles)
      delete o;
    for (auto s : sources)
      delete s;
  }

  // getters
  std::vector<Particule *> const &getParticules() const;
  std::vector<Obstacle *> const &getObstacles() const;
  std::vector<Source *> const &getSources() const;

  // méthodes ajout d'un objet au système
  void ajouteParticule(Particule *p);
  void ajouteObstacle(Obstacle *o);
  void ajouteSource(Source *s);

  // On interdit la copie puisqu'on travaille avec des pointeurs
  Systeme(Systeme const &) = delete;
  Systeme &operator=(Systeme const &) = delete;

  // dessin
  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  }

  // méthode d'évolution du système
  void evolue();
};

// affichage texte
std::ostream &operator<<(std::ostream &out, Systeme const &s);
