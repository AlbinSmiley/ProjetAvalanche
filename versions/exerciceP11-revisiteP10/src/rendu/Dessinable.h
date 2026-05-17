#pragma once

class SupportADessin; // prédéclaration dans Dessinable.h car Dessinable dépend
                      // de SupportADessin

class Dessinable {
public:
  virtual ~Dessinable() =
      default; // destructeur virtuel pour éviter qu'une destruction d'objet ne
               // soit que partielle et que le comportement de notre projet soit
               // incorrect
  virtual void dessine_sur(SupportADessin &support)
      const = 0; // cette méthode ne doit pas etre définie dans cette classe
                 // pour des raisons techniques
};
