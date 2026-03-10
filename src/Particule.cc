#include <iostream>

#include "Particule.h"

using namespace std;

const double Particule::masse() const {// on part du principe qu'une particule est une sphère
    return (4*cst::PI*rho_*rayon_*rayon_*rayon_)/3; 
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
