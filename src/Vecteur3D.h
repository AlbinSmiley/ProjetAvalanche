#pragma once

#include <bitset>
#include <ostream>

class Vecteur3D {
private : 
    double x_;
    double y_;
    double z_;

    bool compare (const Vecteur3D&, const double& presision = PRECISION) const;
public:
    static constexpr double PRECISION = 1e-10; 

    // 5.3.2026, définitions des constructeurs 
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
    Vecteur3D& operator+=(Vecteur3D const&); 
    Vecteur3D& operator-=(Vecteur3D const&); 
    Vecteur3D& operator*=(double const); 

    // méthodes 
    void set_coord(int i, double valeur);
    void affiche() const;

    // Getters pour les méthodes et surchage externe 
    double get_x() const { return x_; }
    double get_y() const { return y_; }
    double get_z() const { return z_; }

    // Opérations entre vecteurs
    Vecteur3D addition(const Vecteur3D& autre) const;
    Vecteur3D soustraction(const Vecteur3D& autre) const;
    Vecteur3D oppose() const;

    // Multiplication par scalaire
    Vecteur3D mult(double lambda) const;

    // Produit scalaire
    double prod_scal(const Vecteur3D& autre) const;

    // Produit vectoriel
    Vecteur3D prod_vect(const Vecteur3D& autre) const;

    // Normes
    double norme2() const;
    double norme() const;

    // Vecteur unitaire
    Vecteur3D unitaire() const;
};

// // Surchage d'operateur externe
// std::ostream& operator<<(std::ostream&, Vecteur3D const&) ; 
//
// // Addition et soustraction
// const Vecteur3D operator+(Vecteur3D, Vecteur3D const&) ;
// const Vecteur3D operator-(Vecteur3D, Vecteur3D const&) ;
//
// // Produit scalaire 
// const double operator*(Vecteur3D, Vecteur3D const&) ;
//
// // multiplication par un scalaire 
// const Vecteur3D operator*(double, Vecteur3D const&) ; 
//
// // Produit vectoriel
// const Vecteur3D operator^(Vecteur3D, Vecteur3D const&); 
