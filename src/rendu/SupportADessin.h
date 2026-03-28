#pragma once

class Particule;
class Systeme;
class Obstacle;
class Plan;
class Dalle;
class Source;
//prédéclaration dans SupportADessin.h car SupportADessin dépend de Particule,Systeme et Obstacle. On utilise aussi seulement des références

class SupportADessin {
    public: 
    virtual ~SupportADessin() = default; //destructeur virtuel pour éviter qu'une destruction d'objet ne soit que partielle et que le comportement de notre projet soit incorrect

    //chose qu'on veut dessiner:
    virtual void dessine(Particule const&) = 0;
    virtual void dessine(Obstacle const&) = 0;
    virtual void dessine(Plan const&) = 0;
    virtual void dessine(Dalle const&) = 0;
    virtual void dessine(Source const&) = 0;
    virtual void dessine(Systeme const&) = 0;
   
};