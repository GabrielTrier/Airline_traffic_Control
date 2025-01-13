

#include "case.h"
Case::Case(std::pair<int,int>position, std::pair<float,float>positionPixel,int id){
    rect.setSize(sf::Vector2f (30,30));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f((float)position.first,(float)position.second));
    m_position=position;
    m_positionPixel=positionPixel;
    m_id=id;
}

Case::Case(){
    m_position={0,0};
}

void Case::addSuccesseur(Case *successeur, float poids) {
    m_successeurs.emplace_back(successeur,poids);
}
std::vector<std::pair<Case*,float>> Case::getSuccesseurs() {
    return m_successeurs;
}

void Case::addPredecesseur(Case *predecesseur) {
    m_predecesseurs.push_back(predecesseur);
}


void Case::clearPredecesseurs() {
    m_predecesseurs.clear();
}


void Case::afficherPosition() const {
    std::cout<<"["<<m_position.first<<","<<m_position.second<<"]";
}

int Case::getDistance() const {
    return m_distance;
}
void Case::setDistance(int nb) {
    m_distance=nb;
}
int Case::getMarque() const {
    return m_marque;
}
void Case::setMarque(int b) {
    m_marque = b;
}


std::pair<int,int> Case::getPosition() {
    return m_position;
}



const std::pair<float, float> &Case::getMPositionPixel() const {
    return m_positionPixel;
}


///Fonctions utilisées dans d'autres fonctions non finalisées
/*
 std::vector<Case*> Case::getPredecesseurs() {
    return m_predecesseurs;
}
void Case::setPosition(std::pair<int,int> position) {
    m_position=position;
    rect.setPosition(sf::Vector2f((float)position.first,(float)position.second));
}
void Case::dessiner(sf::RenderWindow &window) {
    window.draw(rect);
}
int Case::getMId() const {
    return m_id;
}

void Case::setMId(int mId) {
    m_id = mId;
}*/
