#include "Systeme.h"
#include "TextViewer.h"

using namespace std;

// accesseurs
vector<Particule> const& Systeme::getParticules() const {
    return particules;
}

vector<Obstacle*> const& Systeme::getObstacles() const {
    return obstacles;
}

vector<Source*> const& Systeme::getSources() const {
    return sources;
}

// ajouts
void Systeme::ajouteParticule(Particule const& p) {
    particules.push_back(p);
}

void Systeme::ajouteObstacle(Obstacle* o) {
    obstacles.push_back(o);
}

void Systeme::ajouteSource(Source* s) {
    sources.push_back(s);
}

// affichage
//c'est l'opérateur d'affichage
ostream& operator<<(ostream& out, Systeme const& s) {

    TextViewer vue(out);//outil d'afficahge 
    out << "Le systeme est constitue des "
        << s.getParticules().size()
        << " particules suivantes :" << endl;

    for (auto const& p : s.getParticules()) {
        out << p << endl;
    }

    out << "et des "
        << s.getObstacles().size()
        << " obstacles suivants :" << endl;

    for (auto const& o : s.getObstacles()) {
        (*o).dessine_sur(vue); //c'est du polymorphsime 
        out<<endl;
    }

    if (!s.getSources().empty()){
    out << "et des "
        << s.getSources().size()
        << " sources suivantes :" << endl;

    for (auto const& source : s.getSources()) {
        (*source).dessine_sur(vue);
        out << *source << endl;
    }
}

    return out;
}