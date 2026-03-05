#include "Vecteur3D.h"

#include <iostream> 
#include <cmath>

using namespace std;

// // surchage d'operateur interne
// // comparaison
// bool Vecteur3D::operator==(Vecteur3D const& autre) const { return compare(autre); }
//
// bool Vecteur3D::operator!=(Vecteur3D const& autre) const { return !(compare(autre)); }
//
// // modificateur 
// Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& autre) { 
//     x_ += autre.x_ ; 
//     y_ += autre.y_ ; 
//     z_ += autre.z_ ; 
//
//     return *this; 
// } 
//
// Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& autre) {
//     x_ -= autre.x_ ; 
//     y_ -= autre.y_ ; 
//     z_ -= autre.z_ ; 
//
//     return *this; 
// }
//
// Vecteur3D& Vecteur3D::operator*=(double const lambda) {
//     x_ *= lambda ; 
//     y_ *= lambda ; 
//     z_ *= lambda ; 
//
//     return *this; 
// }
//
// std::ostream& operator<<(std::ostream& out, Vecteur3D const& vec) {
//     out << vec.get_x() << " " << vec.get_y() << " " << vec.get_z() ; 
//
//     return out; 
// }
//
// const Vecteur3D operator+(Vecteur3D vec1, Vecteur3D const& vec2) { return vec1+=vec2; }
//
// const Vecteur3D operator-(Vecteur3D vec1, Vecteur3D const& vec2) { return vec1-=vec2; }
//
// const Vecteur3D operator*(double lambda, Vecteur3D const& vec) { return vec*=lambda ; }

void Vecteur3D::set_coord(int i, double valeur){
    if (i == 0){
        x_ = valeur;
    } else if (i == 1){
        y_ = valeur;
    } else if (i==2){
        z_ = valeur;
    }
    // si i est invalide on ne fait rien 
}

void Vecteur3D::affiche() const{
    cout << x_ << " " << y_ << " " << z_ << endl;
}

bool Vecteur3D::compare(const Vecteur3D& autre, const double& presision ) const{
    return ((abs(x_-autre.x_)< presision) and (abs(y_-autre.y_)< presision) and (abs(z_-autre.z_)< presision));
}

Vecteur3D Vecteur3D::addition(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, x_ + autre.x_);
    r.set_coord(1, y_ + autre.y_);
    r.set_coord(2, z_ + autre.z_);
    return r;
}

Vecteur3D Vecteur3D::soustraction(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, x_ - autre.x_);
    r.set_coord(1, y_ - autre.y_);
    r.set_coord(2, z_ - autre.z_);
    return r;
}

Vecteur3D Vecteur3D::oppose() const {
    Vecteur3D r;
    r.set_coord(0, -x_);
    r.set_coord(1, -y_);
    r.set_coord(2, -z_);
    return r;
}

Vecteur3D Vecteur3D::mult(double lambda) const {
    Vecteur3D r;
    r.set_coord(0, lambda * x_);
    r.set_coord(1, lambda * y_);
    r.set_coord(2, lambda * z_);
    return r;
}

double Vecteur3D::prod_scal(const Vecteur3D& autre) const {
    return x_ * autre.x_ + y_ * autre.y_ + z_ * autre.z_;
}

Vecteur3D Vecteur3D::prod_vect(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, y_ * autre.z_ - z_ * autre.y_);
    r.set_coord(1, z_ * autre.x_ - x_ * autre.z_);
    r.set_coord(2, x_ * autre.y_ - y_ * autre.x_);
    return r;
}

double Vecteur3D::norme2() const {
    return x_ * x_ + y_ * y_ + z_ * z_;
}

double Vecteur3D::norme() const {
    return sqrt(norme2());
}

Vecteur3D Vecteur3D::unitaire() const {
    double n = norme();
    Vecteur3D r;

    if (abs(n) < 1e-15) { // vecteur nul => on renvoie le vecteur nul
        r.set_coord(0, 0.0);
        r.set_coord(1, 0.0);
        r.set_coord(2, 0.0);
        return r;
    }

    r.set_coord(0, x_ / n);
    r.set_coord(1, y_ / n);
    r.set_coord(2, z_ / n);
    return r;
}
