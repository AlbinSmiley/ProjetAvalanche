#pragma once

#include <iostream>
#include "SupportADessin.h" //car TextViewer hérite de SupportADessin

//la classe TextViewer "est un" SupportADessin
class TextViewer : public SupportADessin {
    private:
        std::ostream& flot; //attribut privé

    public:
        TextViewer(std::ostream& flot);//constreucteur

        void dessine(Particule const& pa) override;
        void dessine(Systeme const& sy) override;
        void dessine(Obstacle const& ob) override;
        void dessine(Dalle const& da) override;
        void dessine(Plan const& pl) override;
        void dessine(Source const& so) override;

};