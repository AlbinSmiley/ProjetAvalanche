#pragma once

#include "Obstacle.h"

class Plan : public Obstacle {
    protected: 
        Vecteur3D normale; // un vecteur unitaire normal au plan

    public : 
        Plan(Vecteur3D const& position, Vecteur3D const& normale); // voici un constructeur avec parametres 

        Vecteur3D getNormale() const;

        Vecteur3D PointPlusProche(Vecteur3D const& x_i) const; //méthode donnée dans l'énoncée
    };