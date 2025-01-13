#ifndef CONTROLEAERIEN_CASE_H
#define CONTROLEAERIEN_CASE_H


#include <iostream>
#include <SFML/Graphics.hpp>

class Case{
private:
    int m_id;
    std::pair<int, int> m_position;
    std::pair<float,float> m_positionPixel;
    std::vector<std::pair<Case*,float>> m_successeurs;
    std::vector<Case*> m_predecesseurs;
    int m_distance;
    int m_marque;

    sf::RectangleShape rect; //localisation, carrés sur la map

public:
    Case(std::pair<int,int> position, std::pair<float,float> positionPixel,int id);
    Case();
    virtual ~Case()=default;

    void addSuccesseur(Case* successeur, float poids);
    std::vector<std::pair<Case*,float>> getSuccesseurs();
    void addPredecesseur(Case* predecesseur);
    void clearPredecesseurs();

    void afficherPosition() const;
    std::string getPositionString();

    void recursivePredecesseurs(std::vector<Case*> &chemin);

    int getDistance() const;
    void setDistance(int nb);

    int getMarque() const;
    void setMarque(int b);

    const std::pair<float, float> &getMPositionPixel() const;
    std::pair<int,int> getPosition();

    ///Fonctions utilisées dans d'autres fonctions non finalisées
    /*int getMId() const;
    void setMId(int mId);
    std::vector<Case*> getPredecesseurs();
    void dessiner(sf::RenderWindow& window);
     void setPosition(std::pair<int,int> position);*/

};

#endif




