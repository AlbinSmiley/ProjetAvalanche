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
  double eta_milieu = cst::ETA_AIR; // par défaut le système est dans l'air
  double rho_milieu = cst::RHO_AIR;

public:
  // constructeur par défaut = système vide
  Systeme() = default;

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

  // les setters pour les attributs numérique du systèmes
  void set_dt(double dt_) { dt = dt_; }
  void set_eta(double eta) { eta_milieu = eta; }
  void set_rho(double rho) { rho_milieu = rho; }

  // On interdit la copie puisqu'on travaille avec des pointeurs
  Systeme(Systeme const &) = delete;
  Systeme &operator=(Systeme const &) = delete;

  // dessin
  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  }

  // méthode d'évolution du système
  void evolue();
  // une méthode qui fait évoluer le système pendant un temps
  // donné en affichant le sysètme à chaques pas de temps
  void evolution(double, std::ostream &out);
  void dataEvolution(double);
};

// affichage texte
std::ostream &operator<<(std::ostream &out, Systeme const &s);
