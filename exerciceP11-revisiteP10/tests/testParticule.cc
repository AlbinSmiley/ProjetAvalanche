#include "ParticuleNeige.h"
#include "constantes.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace cst;

int main() {
  double rho2 = 12.5;

  vector<Particule *> sys = {
      new ParticuleNeige(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 0), 0.4),
      new ParticuleNeige(Vecteur3D(1, 0, 0), Vecteur3D(0, 0.2, 0), 0.15, rho2),
      new ParticuleNeige(Vecteur3D(0, 0, 1), Vecteur3D(0, 0, -0.05), 0.1,
                         rho2)};

  cout << "Affichage initial :" << endl;
  for (size_t i = 0; i < sys.size(); i++)
    cout << "  P" << i + 1 << " : " << *sys[i] << endl;

  cout << "\nTest copie :" << endl;
  Particule *copie = sys[0]->clone();
  cout << "  copie de P1 : " << *copie << endl;
  delete copie;

  cout << "\nForces et deplacement :" << endl;
  for (size_t i = 0; i < sys.size(); i++) {
    Particule *p = sys[i]->clone();
    p->ajouteForce(ETA_AIR, RHO_AIR);
    for (size_t j = 0; j < sys.size(); j++) {
      if (j != i)
        p->ajouteForce(*sys[j]);
    }
    cout << "  P" << i + 1 << " : f = " << p->get_force() << endl;
    p->bouger();
    cout << "       v = " << p->get_vitesse() << ", x = " << p->get_position()
         << endl;
    delete p;
  }

  for (Particule *p : sys)
    delete p;
  return 0;
}
