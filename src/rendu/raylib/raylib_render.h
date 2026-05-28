#pragma once

#include "SupportADessin.h" //car TextViewer hérite de SupportADessin
#include "Systeme.h"
#include <raylib.h>

// la classe TextViewer "est un" SupportADessin
class RaylibRender : public SupportADessin {
private:
  Camera3D camera;
  bool deplacement = false;
  bool pointeur = false;
  bool lecture = false;
  bool rk4 = false;

  float vitesse_sim = 1.0f;

  bool fenetre_ajout = false;
  bool ajout_particule = false;
  bool ajout_plan = false;

  // des emplacement pour les champs texte pour l'ajout d'éléments
  char buf_px[16] = "0";
  bool edit_px = false;
  char buf_py[16] = "0";
  bool edit_py = false;
  char buf_pz[16] = "2";
  bool edit_pz = false;
  char buf_vx[16] = "0";
  bool edit_vx = false;
  char buf_vy[16] = "0";
  bool edit_vy = false;
  char buf_vz[16] = "0";
  bool edit_vz = false;
  char buf_r[16] = "0.4";
  bool edit_r = false;

public:
  static constexpr int PANEL_WIDTH = 220;
  static constexpr int MIN_WINDOW_HAUTEUR = 800;
  static constexpr int MIN_WINDOW_LARGEUR = 1000;

  RaylibRender(); // constreucteur
  ~RaylibRender() override;

  void run(Systeme &);

  void dessine(Particule const &) override;
  void dessine(Systeme const &) override;
  void dessine(Obstacle const &) override { /*whatever it doesn't exist*/ }
  void dessine(Dalle const &) override;
  void dessine(Plan const &) override;
  void dessine(Source const &) override { /*whatever it doesn't exist*/ }

  void dessinePanel(Systeme &);
  void fenetreParticule(Systeme &);
  void fenetrePlan(Systeme &);
};
