#include <iostream> 
#include <cmath>

#include "Vecteur3D.h"
#include "constantes.h"

using namespace std;
using namespace cst;

// surchage d'operateur interne
// comparaison
bool Vecteur3D::operator==(Vecteur3D const& autre) const {
    bool a = (abs(x_-autre.x_) < PRECISION) ; 
    bool b = (abs(y_-autre.y_) < PRECISION) ; 
    bool c = (abs(z_-autre.z_) < PRECISION) ; 
    return a and b and c ; 
}

bool Vecteur3D::operator!=(Vecteur3D const& autre) const {
    return !(*this == autre); 
}

// modificateur 
Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& autre) { // la fonction modifie un objet existant, c'est pour ça qu'on retourne une référence
    x_ += autre.x_ ; 
    y_ += autre.y_ ; 
    z_ += autre.z_ ; 

    return *this; 
} 

Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& autre) {
    (*this) += -autre; 
    return *this; 
}

Vecteur3D& Vecteur3D::operator*=(double const lambda) {
    x_ *= lambda ; 
    y_ *= lambda ; 
    z_ *= lambda ; 

    return *this; 
}

Vecteur3D& Vecteur3D::operator/=(double const lambda) {
    (*this) *= (1/lambda) ; 
    return *this; 
}

Vecteur3D& Vecteur3D::operator^=(Vecteur3D const& autre) {
    double x = x_;  double y = y_;  double z = z_; // copie temporaire  
    x_ = y*autre.z_ - z*autre.y_; 
    y_ = z*autre.x_ - x*autre.z_; 
    z_ = x*autre.y_ - y*autre.x_; 

    return *this; 
}

double Vecteur3D::operator*(Vecteur3D const& autre) const {// surchage interne pour éviter l'utilisation de getters
    return x_*autre.x_ + y_*autre.y_ + z_*autre.z_ ; 
}

Vecteur3D Vecteur3D::operator~() {
    return (*this) *= (1/norme());
}

Vecteur3D Vecteur3D::operator-() const {
    return (*this) * -1 ;
}

string Vecteur3D::vecToString() const& {
    return "(" + to_string(x_) + "," + to_string(y_) + "," + to_string(z_) + ")";
}

ostream& operator<<(ostream& out, Vecteur3D const& vec) {
    out << vec.vecToString() ;  
    return out; 
}

Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1+=vec2;
}

Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1-=vec2;
}

Vecteur3D operator*(double lambda, Vecteur3D vec) {// on copie vec car on ne le modifie pas
    return vec*=lambda ;
}

Vecteur3D operator*(Vecteur3D vec,double lambda) {// on ajoute cette méthode pour plus de féxiblité dans la multiplication par un scalaire (vec*lambda = lambda*vec) 
    return lambda*vec ;
}

Vecteur3D operator/(double lambda, Vecteur3D vec) {
    return vec/=lambda ;
}

Vecteur3D operator/(Vecteur3D vec,double lambda) {
    return lambda/vec ;
}

Vecteur3D operator^(Vecteur3D vec1, Vecteur3D const& vec2) {
    return vec1^=vec2; 
}

double Vecteur3D::norme2() const {
    return (*this)*(*this); 
}

double Vecteur3D::norme() const {
    return sqrt(norme2());
}
