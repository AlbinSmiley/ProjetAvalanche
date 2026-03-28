#pragma once

#include <vector>
#include <iostream>

#include "Dessinable.h"
#include "SupportADessin.h"
#include "Particule.h"
#include "Obstacle.h"
#include "Source.h"

class Systeme : public Dessinable {
private:
    std::vector<Particule> particules;
    std::vector<Obstacle*> obstacles; //on veut du polymorphisme donc des pointeurs
    std::vector<Source*> sources;//on veut du polymorphisme donc des pointeurs

public:
    // constructeur par défaut = système vide
    Systeme() = default;

    // getters
    std::vector<Particule> const& getParticules() const;
    std::vector<Obstacle*> const& getObstacles() const;
    std::vector<Source*> const& getSources() const;

    // méthodes ajout d'un objet au système
    void ajouteParticule(Particule const& p);
    void ajouteObstacle(Obstacle* o);
    void ajouteSource(Source* s);

    // dessin
    void dessine_sur(SupportADessin& support) const override
    { support.dessine(*this); }
};

// affichage texte
std::ostream& operator<<(std::ostream& out, Systeme const& s);