#include "Aleatoire.h"
#include <iostream>

using namespace std;

int main() {
  Aleatoire generateur;
  cout << generateur.uniforme(1.0, 2.5) << endl;
  cout << generateur.uniforme(1.0, 2.5) << endl;
  return 0;
}
