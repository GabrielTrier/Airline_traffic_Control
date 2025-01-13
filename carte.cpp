#include "carte.h"

Carte::Carte() { //constructeur pour loader l'image
    if (!texture.loadFromFile("../Images/CarteMondeFinale.png")){
        std::cout << "Erreur chargement de l'image\n";
    }
    sprite.setTexture(texture);

}
void Carte::dessiner(sf::RenderWindow &window) { //fonction dessine la carte
    window.draw(sprite);
}