#ifndef CONTROLEAERIEN_MENU_H
#define CONTROLEAERIEN_MENU_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include "Aeroport.h"
#include "Avion.h"
#include "single_include/tabulate/tabulate.hpp"


using namespace tabulate;

class Menu {
private:
    int m_choix;
    std::vector<Avion*> avions;
    std::vector<Aeroport*> aeroports;
public:
    Menu();
    ~Menu();
    void lancer(bool &end);
    void lancerSimulation();
    void afficher();
    void afficherListes();
    void parametrerSimulation(int choixAvion, std::string choixDepart, std::string choixArrivee);
    bool verif(std::string choix);

    int getMChoix() const;
};

#endif //CONTROLEAERIEN_MENU_H
