#pragma once

#include "SupportADessin.h" //car TextViewer hérite de SupportADessin
#include "Systeme.h"
#include <raylib.h>

// la classe TextViewer "est un" SupportADessin
class RaylibRender : public SupportADessin {
private:
  Camera3D camera;

public:
  RaylibRender(); // constreucteur
  ~RaylibRender() override;

  void run(Systeme &);

  void dessine(Particule const &) override;
  void dessine(Systeme const &) override;
  //   // void dessine(Obstacle const &) override;
  //   void dessine(Dalle const &) override;
  //   void dessine(Plan const &) override;
  //   void dessine(Source const &) override;
};
