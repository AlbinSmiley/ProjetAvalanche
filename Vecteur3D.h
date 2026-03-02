#pragma once
class Vecteur3D {
private : 
    double x;
    double y;
    double z;

public:
    void set_coord(int i, double valeur);
    void affiche() const;
    bool compare (const Vecteur3D&, const double& presision = 1e-10) const;

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
