#include <iostream> 
#include "Particule.h"
#include <iomanip>
#include <vector> 

using namespace std;

using Systeme = vector<Particule>; 

void indent(int n) { cout << setw(n) << "" ; }

void afficheParticuleEtat(size_t num_particule, Systeme sys) {
    Particule main_part = sys[num_particule] ; 
    // sys.erase(sys.begin() + num_particule) ; 

    cout << "Particule " << num_particule + 1 << " : "<< endl ; 
    cout << "Force \"perso\" : " << endl ; 
    indent(6); cout << "f = " << main_part.get_force() << " --> " ; 

    main_part.ajouteForce() ; 

    cout << "f = " << main_part.get_force() << endl
        << "Force des autres grains : " << endl ; 

    for (size_t i = 0; i < sys.size() ; i++) {
        if (i==num_particule) {
            continue ; 
        } else {
            indent(6) ; cout << "Particule " << i + 1 << " : " << endl ;  
            indent(12); cout << "distance entre grains = " << distance(main_part,sys[i]) << endl ; 
            indent(12); cout << "forceLJ = " << main_part.forceLJ(sys[i]) << endl ; 
            indent(12); cout << "df = " << main_part.ajouteForce(sys[i]) << ", f = " << (main_part).get_force() << endl ; 
        }
    }

    cout << "Bouger : " << endl; 

    indent(12); cout << "f  = " << main_part.get_force() << endl; 

    Vecteur3D dv = -main_part.get_vitesse(); 
    Vecteur3D dx = -main_part.get_position(); 

    main_part.bouger(); 

    dv += main_part.get_vitesse(); 
    dx += main_part.get_position(); 

    indent(12); cout << "dv = " << dv << endl; 
    indent(12); cout << "dx = " << dx << endl; 
    indent(12); cout << "v  = " << main_part.get_vitesse() << endl; 
    indent(12); cout << "x  = " << main_part.get_position() << endl; 
}


int main () {
    double rho2 = 12.5; 

    Particule p1(Vecteur3D(0,0,0), Vecteur3D(0,0,0), 0.4); 
    Particule p2(Vecteur3D(1,0,0), Vecteur3D(0,0.2,0), 0.15, rho2); 
    Particule p3(Vecteur3D(0,0,1), Vecteur3D(0,0,-0.05),0.1, rho2); 

    Systeme sys = {p1,p2,p3}; 

    cout << "Test de l'affichage : " << endl ;  

    indent(6); cout << "Particule 1 : " << p1 << endl ; 
    indent(6); cout << "Particule 2 : " << p2 << endl ; 
    indent(6); cout << "Particule 3 : " << p3 << endl << endl << setw(0) ; 

    Particule p4(p1) ; 
    Particule p5 = p2; 

    cout << "Test des constructeur de copie : " << endl ; 
    indent(6); cout << "Particule 4 : " << p4 << endl ; 
    indent(6); cout << "Particule 5 : " << p5 << endl << endl ; 

    for (size_t i; i < sys.size(); i++) {
        afficheParticuleEtat(i, sys); 
        cout << endl << endl; 
    }
    return 0;
}
