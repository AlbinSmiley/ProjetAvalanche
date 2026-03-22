#include <iostream>
#include <vector>

#include "Plan.h"
#include "Vecteur3D.h"

using namespace std;

int main() {
    vector<Plan> plans; // on stocke les 5 plans dans un tableau dynamique
    plans.push_back(Plan(Vecteur3D(0, 0, 0), Vecteur3D(0, 0, 2)));
    plans.push_back(Plan(Vecteur3D(0, 0, 0), Vecteur3D(0, 1, 0)));
    plans.push_back(Plan(Vecteur3D(0, 0, 0), Vecteur3D(1, 0, 0)));
    plans.push_back(Plan(Vecteur3D(0, 0, 0), Vecteur3D(1, 1, 1)));
    plans.push_back(Plan(Vecteur3D(1, 2, 3), Vecteur3D(1.1, 3.3, 2.2)));

    vector<Vecteur3D> points; // on stocke les 4 points à tester
    points.push_back(Vecteur3D(0, 7, 0));
    points.push_back(Vecteur3D(0, 0, 10));
    points.push_back(Vecteur3D(2, 0, 0));
    points.push_back(Vecteur3D(5, -4, 6));

    for (auto const& plan : plans) { // on teste chauqe point sur ce plan
        cout << "Plan d'origine " << plan.getPosition()
             << " et de normale " << plan.getNormale() << " :" << endl;

        for (auto const& point : points) {
            cout << "distance à " << point << " : "
                 << plan.PointPlusProche(point) << endl; // on claule la projection orthogonale du point sur le plan
        }
    }

    return 0;
}