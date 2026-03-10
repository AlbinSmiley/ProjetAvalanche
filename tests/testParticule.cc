#include <iostream> 
#include "Particule.h"

using namespace std;

int main () {
    Vecteur3D origine; 
    Vecteur3D vitesse_nul; 

    double rho1 = 1; 
    double rho2 = 12.5; 

    Particule p1(origine,vitesse_nul,0.4,rho1); 
    Particule p2(Vecteur3D(1,0,0), Vecteur3D(0,0.2,0),0.15,rho2); 
    Particule p3(p2); 
    Particule p4 = p1 ;

    cout << "Particule 1 : " << p1 << endl ; 
    cout << "Particule 2 : " << p2 << endl ; 
    cout << "Particule 3 : " << p3 << endl ; 
    cout << "Particule 4 : " << p4 << endl ; 

    return 0;
}
