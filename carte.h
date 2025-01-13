#ifndef CONTROLEAERIEN_CARTE_H
#define CONTROLEAERIEN_CARTE_H

#include <SFML/Graphics.hpp>
#include <iostream>
class Carte {
public:
    Carte();
    void dessiner(sf::RenderWindow& window);

private:
    sf::Texture texture;
    sf::Sprite sprite;

};

#endif
