#include "arc.h"

///CONSTRUCTEURS-DESTRUCTEUR///

Arc::Arc(Aeroport* premier, Aeroport* second,int poids){
    m_premier=premier;
    m_second=second;
    m_poids=poids;
    ligne[0].position.x=premier->getPosition().x;//pour avoir la première extrémité (premier aéroport) position en x
    ligne[0].position.y=premier->getPosition().y;//idem avec position en y
    ligne[1].position.x=second->getPosition().x;// 2eme aeroport x
    ligne[1].position.y=second->getPosition().y;//y
    ligne[0].color=sf::Color::Black;
    ligne[1].color=sf::Color::Black;
}
Arc::Arc(){
    m_premier= nullptr;
    m_second= nullptr;
    m_poids=0;
}
Arc::~Arc()=default;


///GETTERS-SETTERS///
void Arc::setPremier(Aeroport *premier) {
    m_premier=premier;
}
void Arc::setSecond(Aeroport *second) {
    m_second=second;
}

Aeroport* Arc::getPremier() {
    return m_premier;
}
Aeroport* Arc::getSecond() {
    return m_second;
}

int Arc::getMPoids() const {
    return m_poids;
}
void Arc::setMPoids(int mPoids) {
    m_poids = mPoids;
}


///AFFICHAGE///
void Arc::dessiner(sf::RenderWindow& window){
    window.draw(ligne,2,sf::Lines);

}


