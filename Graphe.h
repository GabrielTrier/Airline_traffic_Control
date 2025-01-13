#ifndef CONTROLEAERIEN_GRAPHE_H
#define CONTROLEAERIEN_GRAPHE_H
#include <list>
#include <ostream>
#include <valarray>
#include "Aeroport.h"
#include "arc.h"
#include "Avion.h"
#include "case.h"

class Graphe {
private:
    std::vector<Aeroport *> m_aeroports;
    std::vector<Arc*> m_arcs;
    std::vector<Avion*> m_avions;
    std::vector<Case*> m_cases;
    Aeroport* aeroportSelect= nullptr;
    sf::Text infoTAeroport;
    sf::Text infoArc;
    sf::Font font;
    Avion* avionSelect=nullptr;
    sf::RectangleShape infoAeroport; //localisation, carrés sur la map
    sf::Text infoTAvion;
    sf::RectangleShape infoAvion;

public:
    Graphe(const std::string& filename_Aeroport, const std::string& filename_Arc, const std::string& filename_Avion);
    ~Graphe();
    void initCasesAeroports();
    void attribuerAeroport();
    void dessinerGraphe(sf::RenderWindow& window);
    void testerCollision();
    void nouvelleDestination();
    void initCases();
    void initPredecesseurs();

    void PCCTotal();
    void PCCAvionUnique(Avion* avion);

    void calculEscales();
    Case* selectionnerCase(int x, int y);

    void sauvF_CA(int compteur);

    void trouverAeroport(float x, float y);
    void trouverAvion(float x, float y);
    void AeroportBloque();

    const std::vector<Aeroport *> &getMAeroports() const;
    const std::vector<Avion *> &getMAvions() const;

    void gererQueue();

    ///Fonctions de vérification ou non finalisées
    /*void AStar();
    std::vector<Case*> Astar(int s0,int arrivee);
    Case* selectionnerCasePixel(float x, float y);
    float heuristique(int S0, Case * S1);
    void affichagePCC(std::vector<Case*> &chemin);
    bool tousSommetsMarques() const;
    Aeroport* selectionnerAeroport(const std::string& nom);
    void AstarTotal();
    void lectF_CA();
    Avion* selectionnerAvion(int nb);*/
;};

#endif
