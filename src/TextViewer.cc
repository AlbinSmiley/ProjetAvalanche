#include "TextViewer.h"

#include "Particule.h"
#include "Obstacle.h"
#include "Plan.h"
#include "Dalle.h"
#include "Source.h"
#include "Systeme.h"


using namespace std;

TextViewer::TextViewer(ostream& flot)
    : flot(flot)
{}//constructeur : on mémorise le flot que lequel on veut écrire

void TextViewer::dessine(Particule const& pa) {
    flot << pa;
}//dessine une particule

void TextViewer::dessine(Obstacle const& ob) {
    flot << ob;
}//dessin un obstalce


void TextViewer::dessine(Plan const& pl) {
    flot << pl;
}// dessine un plan

void TextViewer::dessine(Dalle const& de) {
    flot << de;
}//dessine une dalle

void TextViewer::dessine(Source const& so) {
    flot << so;
}//dessine une source

void TextViewer::dessine(Systeme const& sy) {
    flot << sy;
}