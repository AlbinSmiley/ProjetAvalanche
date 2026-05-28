#pragma once

#include <iostream>
#include <vector>

#include "Aleatoire.h"
#include "Dessinable.h"
#include "Obstacle.h"
#include "Particule.h"
#include "Source.h"
#include "SupportADessin.h"
#include "constantes.h"

class Systeme : public Dessinable {
private:
  // on a des ensemble hétérogène il nous faut donc utiliser des pointeurs.
  std::vector<Particule *> particules;
  std::vector<Obstacle *> obstacles;
  std::vector<Source *> sources;

  // on pose les valeurs qui dicte comment le système ce comporte ici (elle ne
  // sont pas constante car dans la simulation il est possible de changer
  // certaines valeurs)
  double dt = cst::DT;
  double eta_milieu = cst::ETA_AIR;
  double rho_milieu = cst::RHO_AIR;

  // on utilise un generateur aleatoire comme attribut pour ne pas avoir a le
  // redefinir dans les boucles
  Aleatoire gen = Aleatoire();

  // Méthode intermédiaire qui permet le calcule de toute les forces appliqué à
  // toute les particules du système. permet un code plus clair.
  void calculerForces();

  // attribut et méthodes pour l'utilisation de rk4, on utilise euler-cromer par
  // défaut. Le booléen définit si c'est rk4 ou non qui sera utilisé.
  bool use_rk4 = false;
  void evolue_rk4();

public:
  // constructeur par défaut = système vide
  Systeme() = default;

  ~Systeme() {
    for (auto &p : particules)
      delete p;
    for (auto &o : obstacles)
      delete o;
    for (auto &s : sources)
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

  // On interdit la copie puisqu'on travaille avec des pointeurs et que copier
  // un systeme pourrait s'avérer gourment en calcule.
  Systeme(Systeme const &) = delete;
  Systeme &operator=(Systeme const &) = delete;

  // méthode d'évolution du système
  void evolue();
  // une méthode qui fait évoluer le système pendant un temps
  // donné en affichant le sysètme à chaques pas de temps
  void evolution(double, std::ostream &out);
  void dataEvolution(double);
  void affichageEvolution(double, std::ostream &out);

  // méthodes nécéssaire à l'utilisation de rk4
  void rk4_On() { use_rk4 = true; }
  void rk4_Off() { use_rk4 = false; }

  // dessin
  void dessine_sur(SupportADessin &support) const override {
    support.dessine(*this);
  }
};

// affichage texte
std::ostream &operator<<(std::ostream &out, Systeme const &s);
