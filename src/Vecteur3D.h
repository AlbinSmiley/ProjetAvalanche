#pragma once
#include <ostream>
#include <string>

class Vecteur3D {
private : 
    double x_;
    double y_;
    double z_;
public:
    // Constructeur par défaut qui renvoi le vecteur nul
    Vecteur3D() : x_(0.0), y_(0.0), z_(0.0) {}
    // Constructeur usuel qui se comporte comme on le voudrait 
    Vecteur3D(double x, double y, double z) : x_(x), y_(y), z_(z) {}
    // Constructeur de copie (qui ne semble pas "incroyablement" utile mais ça ne coute rien de l'ajouter pour l'instant)
    Vecteur3D(Vecteur3D const& autre) : x_(autre.x_), y_(autre.y_), z_(autre.z_) {}

    // surchage d'operateur interne
    // comparaison
    bool operator==(Vecteur3D const&) const;
    bool operator!=(Vecteur3D const&) const;
    
    // modificateur 
    Vecteur3D& operator+=(Vecteur3D const&); //retour de reference d'un vecteur pour pouvoir définir + par += 
    Vecteur3D& operator-=(Vecteur3D const&); 
    Vecteur3D& operator*=(double const); 
    Vecteur3D& operator/=(double const); 
    Vecteur3D& operator^=(Vecteur3D const&); 
    
    // Produit scalaire 
    double operator*(Vecteur3D const&) const ;

    // Vecteur unitaire 
    Vecteur3D operator~() ; 

    // Vecteur opposé
    Vecteur3D operator-() const ; 

    // Normes
    double norme2() const;
    double norme() const;

    // Méthode d'affichage pour éviter l'utilisation de getter
    // std::string vecToString() const& ; 

    // Getters pour les méthodes et surchage externe 
    double get_x() const { return x_; }
    double get_y() const { return y_; }
    double get_z() const { return z_; }
};

/* 
    Surchage d'operateur externe 
*/

// Affichage de vecteur
std::ostream& operator<<(std::ostream&, Vecteur3D const&) ; 

// Addition et soustraction
Vecteur3D operator+(Vecteur3D, Vecteur3D const&) ; // on ne met pas de const devant le type de retour car cela ne nous semble pas très utile, nous n'allons pas faire des trucs trop "bizarre" avec les oprations ... par exemple on ne feras pas de truc du genre : (vec1+vec2) = vec3 ... 
Vecteur3D operator-(Vecteur3D, Vecteur3D const&) ;

// multiplication par un scalaire 
Vecteur3D operator*(double, Vecteur3D) ; 
Vecteur3D operator*(Vecteur3D,double) ; 

Vecteur3D operator/(double, Vecteur3D) ; 
Vecteur3D operator/(Vecteur3D,double) ; 

// Produit vectoriel
Vecteur3D operator^(Vecteur3D, Vecteur3D const&); 
