#include <iostream>
#include "Vecteur3D.h"

using namespace std;

int main() {

    Vecteur3D v0;
    Vecteur3D v1(1.0, 2.0, -0.1);
    Vecteur3D v2(2.6,3.5,4.1);
    Vecteur3D v3(3.1,4,1);
    Vecteur3D v4 = v1;
    Vecteur3D v5(v1); 

    cout << "Vecteur 0 : " << v0 << endl;
    cout << "Vecteur 1 : " << v1 << endl; 
    cout << "Vecteur 2 : " << v2 << endl; 
    cout << "Vecteur 3 : " << v3 << endl; 
    cout << "Vecteur 4 : " << v4 << endl; 

    // cout << "Le vecteur 1 est " ;
    // if (v1 == v2) {
    //     cout << "egal au vecteur 2";
    // } else {
    //     cout << "different du vecteur 2";
    // }
    //
    // cout << endl;
    //
    // cout << "Le vecteur 1 est ";
    //
    // if (v1 != v3 ) {
    //     cout << "different du vecteur 3";
    // } else {
    //     cout << "egal au vecteur 3";
    // }

    v4+=v1;
    cout << "v4 += v1 : "<< v4 << endl;

    v4-=v1; 
    cout << "v4 -= v1 : "<< v4 << endl;

    cout << "v4 + v0 : "<< v4+v0 << endl;

    cout << "-v4 : " << -v4 << endl; 

    v4*=3; 
    cout << "v4 *= 3 : " << v4 << endl; 

    cout << "v4*3 : " << v4*3 << endl; 
    cout << "3*v4 : " << 3*v4 << endl; 
    cout << "v4*3 == 3*v4 : " << ((3*v4)==(v4*3)) << endl; 

    v5^=v1; 
    cout << "v5 ^= v1 : " << v5 << endl; 

    cout << "v3^v2 : " << (v3^v2) << endl; 

    cout << "v3*v4 : " << v3*v4 << endl; 

    cout << "~v4 : " << ~v4 << endl; 

    cout << "norme de (~v4) : " << (~v4).norme() << endl; 

    return 0;
}
