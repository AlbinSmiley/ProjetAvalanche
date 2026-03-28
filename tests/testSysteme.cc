#include <iostream>
#include <cmath>

#include "Systeme.h"
#include "Plan.h"
#include "Particule.h"

using namespace std;

int main() {
    Systeme systeme;

    Particule p1(Vecteur3D(0,0,0), Vecteur3D(0,0,0), 0.4);
    Particule p2(Vecteur3D(1,0,0), Vecteur3D(0,0,0), 0.4);
    Particule p3(Vecteur3D(0.5, sqrt(3.0)/2.0, 0), Vecteur3D(0,0,0), 0.4);
    Particule p4(Vecteur3D(0.5, sqrt(3.0)/6.0, sqrt(6.0)/3.0), Vecteur3D(0,0,0), 0.4);

    systeme.ajouteParticule(p1);
    systeme.ajouteParticule(p2);
    systeme.ajouteParticule(p3);
    systeme.ajouteParticule(p4);

    Plan plan(Vecteur3D(0,0,-0.9), Vecteur3D(0,0,1));
    systeme.ajouteObstacle(&plan);

    cout << "./testSystem" << endl;
    cout << systeme << endl;

    return 0;
}