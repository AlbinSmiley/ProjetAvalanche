#include <iostream> 
#include <cmath>
#include "Vecteur3D.h"
using namespace std;

void Vecteur3D::set_coord(int i, double valeur){
    if (i == 0){
        x = valeur;
    } else if (i == 1){
        y = valeur;
    } else if (i==2){
        z = valeur;
    }
    // si i est invalide on ne fait rien 
}

void Vecteur3D:: affiche() const{
    cout << x << " " << y << " " << z << endl;
}

bool Vecteur3D::compare(const Vecteur3D& autre, const double& presision ) const{
    return ((abs(x-autre.x)< presision) and (abs(y-autre.y)< presision) and (abs(z-autre.z)< presision));
}







Vecteur3D Vecteur3D::addition(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, x + autre.x);
    r.set_coord(1, y + autre.y);
    r.set_coord(2, z + autre.z);
    return r;
}

Vecteur3D Vecteur3D::soustraction(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, x - autre.x);
    r.set_coord(1, y - autre.y);
    r.set_coord(2, z - autre.z);
    return r;
}

Vecteur3D Vecteur3D::oppose() const {
    Vecteur3D r;
    r.set_coord(0, -x);
    r.set_coord(1, -y);
    r.set_coord(2, -z);
    return r;
}

Vecteur3D Vecteur3D::mult(double lambda) const {
    Vecteur3D r;
    r.set_coord(0, lambda * x);
    r.set_coord(1, lambda * y);
    r.set_coord(2, lambda * z);
    return r;
}

double Vecteur3D::prod_scal(const Vecteur3D& autre) const {
    return x * autre.x + y * autre.y + z * autre.z;
}

Vecteur3D Vecteur3D::prod_vect(const Vecteur3D& autre) const {
    Vecteur3D r;
    r.set_coord(0, y * autre.z - z * autre.y);
    r.set_coord(1, z * autre.x - x * autre.z);
    r.set_coord(2, x * autre.y - y * autre.x);
    return r;
}

double Vecteur3D::norme2() const {
    return x * x + y * y + z * z;
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

    r.set_coord(0, x / n);
    r.set_coord(1, y / n);
    r.set_coord(2, z / n);
    return r;
}

