#ifndef CONTROLEAERIEN_ARC_H
#define CONTROLEAERIEN_ARC_H

#include <iostream>
#include "Aeroport.h"
#include <SFML/Graphics.hpp>

class Arc{
private:
    Aeroport* m_premier;
    Aeroport* m_second;
    sf::Vertex ligne[2];
    int m_poids;
public:
    Arc(Aeroport* premier, Aeroport* second,int poids);
    Arc();
    ~Arc();

    void dessiner(sf::RenderWindow& window);

    Aeroport* getPremier();
    void setPremier(Aeroport* premier);

    Aeroport* getSecond();
    void setSecond(Aeroport* second);

    int getMPoids() const;
    void setMPoids(int mPoids);
};

#endif //CONTROLEAERIEN_ARC_H
