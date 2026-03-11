#include <iostream>
#include <cmath>

#include "Particule.h"
#include "constantes.h"

using namespace std;
using namespace cst;

const double Particule::masse() const {// on part du principe qu'une particule est une sphère
    return (4*PI*rho_*rayon_*rayon_*rayon_)/3; 
}

ostream& operator<<(ostream& out, Particule const& particule) {
    out 
        << "[ pos = " 
        << particule.get_position() 
        << ", vit = " 
        << particule.get_vitesse() 
        << ", m = " 
        << particule.get_masse() 
        << ", r = " 
        << particule.get_rayon() 
        << " ]";  
    return out ; 
} 

Vecteur3D Particule::ecartOriente(Particule const& particule) const& {
    return get_position() - particule.get_position() ; 
}

double Particule::forceLJ(Particule const& particule) const& {
    double f;

    Vecteur3D ecart_oriente = ecartOriente(particule) ; 
    double distance = (ecart_oriente).norme(); 
    double x = distance/sigma ; 

    if (abs(x-1) <= PRECISION) {
        f = -1.0; 
    } else if (abs(2-x) <= PRECISION) {
        f = 0.0; 
    } else {
        f = (pow(x,6) - 2)/(pow(x,13)); 
    }

    return (24*epsilon*f)/(sigma*sigma); 
}

Vecteur3D Particule::lambda() const {
    double lamb ; 

    double vit = (get_vitesse()).norme();  
    double temp = (80*ETA_MILIEU)/(3*RHO_MILIEU*get_rayon()) ; 

    bool condition = (abs(vit-temp)<=PRECISION) ;

    if (condition) {
        lamb = 6*PI*get_rayon()*ETA_MILIEU ; 
    } else {
        lamb = (9*PI*get_rayon()*get_rayon()*RHO_MILIEU*vit)/40; 
    }

    Vecteur3D result = get_vitesse(); 
    result *= lamb ; 

    return result ; 
}

void Particule::ajouteForce(Vecteur3D const& force) {
    force_ += force; 
}
void Particule::ajouteForce() {
    force_ += get_masse()*G - lambda(); 
}
void Particule::ajouteForce(Particule const& particule) {
    force_ += (forceLJ(particule))*(~(ecartOriente(particule))) ; 
}

void Particule::bouger(double dt = DT) {
    vitesse_ += force_*(dt/masse_);  
    position_+= dt*vitesse_;

    force_ = Vecteur3D(0.0,0.0,0.0) ; 
} 
