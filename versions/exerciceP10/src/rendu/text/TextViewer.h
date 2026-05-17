#pragma once

#include "SupportADessin.h" //car TextViewer hérite de SupportADessin
#include <iostream>

// la classe TextViewer "est un" SupportADessin
class TextViewer : public SupportADessin {
private:
  std::ostream &flot; // attribut privé

public:
  TextViewer(std::ostream &); // constreucteur
  ~TextViewer() override;

  void dessine(Particule const &) override;
  void dessine(Systeme const &) override;
  void dessine(Obstacle const &) override;
  void dessine(Dalle const &) override;
  void dessine(Plan const &) override;
  void dessine(Source const &) override;
};
