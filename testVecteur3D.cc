#include <iostream>
#include "Vecteur3D.h"

using namespace std;


int main() {



    Vecteur3D v1;
    Vecteur3D v2;
    Vecteur3D v3;
    Vecteur3D v0;
v0.set_coord(0, 0.0);
v0.set_coord(1, 0.0);
v0.set_coord(2, 0.0);
    // v1 = (1.0, 2.0, -0.1)
    v1.set_coord(0, 1.0);
    v1.set_coord(1, 2.0);
    v1.set_coord(2, -0.1);

    // v2 = (2.6, 3.5, 4.1)
    v2.set_coord(0, 2.6);
    v2.set_coord(1, 3.5);
    v2.set_coord(2, 4.1);

    v3 = v1;

    cout << "Vecteur 1 : ";
    v1.affiche();
    cout << endl;

    cout << "Vecteur 2 : ";
    v2.affiche();
    cout << endl;

    cout << "Le vecteur 1 est ";

    if (v1.compare(v2)) {
        cout << "egal au vecteur 2";
    } else {
        cout << "different du vecteur 2";
    }

    cout << endl;

    cout << "Le vecteur 1 est ";

    if (v1.compare(v3)) {
        cout << "egal au vecteur 3";
    } else {
        cout << "different du vecteur 3";
    }











    // 1) addition
    // (1.0, 2.0, -0.1) + (2.6, 3.5, 4.1) = (3.6, 5.5, 4.0)
    Vecteur3D s = v1.addition(v2);


    s.affiche(); 
    cout << endl;

    // 2) addition du vecteur nul ne fait rien
    Vecteur3D s0 = v1.addition(v0);
   s0.affiche(); 
   cout << endl;

    // 3) soustraction
    // (1.0,2.0,-0.1) - (2.6,3.5,4.1) = (-1.6,-1.5,-4.2)
    Vecteur3D d = v1.soustraction(v2);
    

    d.affiche(); 
    cout << endl;

    // 4) v - v = 0
    Vecteur3D dn = v1.soustraction(v1);
    dn.affiche(); 
    cout << endl;

    // 5) oppose
    // oppose de (1.0,2.0,-0.1) = (-1.0,-2.0,0.1)
    Vecteur3D op = v1.oppose();

    op.affiche(); cout << endl;

    // 6) v + (-w) = v - w
    Vecteur3D a1 = v1.addition(v2.oppose());
    Vecteur3D a2 = v1.soustraction(v2);

    a1.affiche(); cout << endl;
    a2.affiche(); cout << endl;


    // 7) mult scalaire
    // 3*(1.0,2.0,-0.1) = (3.0,6.0,-0.3)
    Vecteur3D m = v1.mult(3.0);
    m.affiche(); cout << endl;

    // 8) produit scalaire
    // (1.0,2.0,-0.1) * (2.6,3.5,4.1) = 9.19
    double ps = v1.prod_scal(v2);
    cout << ps << endl;

    // 9) produit vectoriel
    // (1.0,2.0,-0.1) ^ (2.6,3.5,4.1) = (8.55, -4.36, -1.7)
    Vecteur3D pv = v1.prod_vect(v2);
    
    pv.affiche(); cout << endl;

    // 10) norme2 v1 = 5.01
    double n1 = v1.norme2();
    cout << n1 << endl;

    // 11) norme2 v2 = 35.82
    double n2 = v2.norme2();
    cout << n2 << endl;








    return 0;
}