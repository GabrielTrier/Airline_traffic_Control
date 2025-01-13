#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Graphe.h"
#include "carte.h"
#include "menu.h"
#include "case.h"
#include "menu.h"
#define UT 2
#define NB_METEO 8
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 950


int main() {

    bool end=false;
    Menu menu;
    int choixAvion;
    std::string choixDepart, choixArrivee;

    do {
        menu.lancer(end);
        if (menu.getMChoix() == 0) {

            ///Aleatoire pour les rand()%
            srand(time(nullptr));

            ///Initialisation
            Graphe g{"../aeroport.txt", "../arc.txt", "../avion.txt"};
            g.initCases();
            g.initPredecesseurs();
            g.initCasesAeroports();
            sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "ControleAerien!");
            Carte carte;
            sf::Clock clock;
            sf::Clock clockMeteo;
            int nbTourSimulation = 0;
            std::vector<sf::RectangleShape> meteos(NB_METEO);//constructeur afin de définir le nombres d'intempéries
            int nombreMeteoAffiches = 0;//Par défaut
            for (auto &m: meteos) {
                m.setSize(sf::Vector2f(60, 60));
                m.setPosition(10000, 10000);//pour pas qu'on le voit au départ
                m.setFillColor(sf::Color::Black);
            }


            ///********Boucle graphique***///

            g.AeroportBloque();
            g.attribuerAeroport();//attribution des aeroports avant la boucle
            //g.AStar();
            g.PCCTotal();
            g.calculEscales();
            g.sauvF_CA(nbTourSimulation);
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    switch (event.type) {
                        case sf::Event::Closed:
                            window.close();
                            break;
                        case sf::Event::KeyPressed:
                            switch (event.key.code) {
                                case sf::Keyboard::Escape:
                                    window.close();
                                    break;
                            }
                        case sf::Event::MouseButtonPressed:
                            float x = event.mouseButton.x;
                            float y = event.mouseButton.y;
                            g.trouverAeroport(x, y);
                            g.trouverAvion(x, y);
                            break;
                    }
                }
                //simulation(clock,window,g,carte);
                sf::Time elapsed = clock.getElapsedTime();
                //std::cout<< "Visualisation du Timer: "<<elapsed.asSeconds()<<std::endl;// visualisation temporaire
                if (elapsed.asSeconds() >= UT) {
                    window.clear();
                    carte.dessiner(
                            window); /// Pour eviter de relancer le programme pour voir si les avions sont bien associes au bon point
                    g.testerCollision();
                    g.dessinerGraphe(window);/// mettre la fonction attribuer aeroport(l.34) avant dessinerGraphe.
                    g.nouvelleDestination(); // permet a l'avion qui a termine le trajet d'en demarrer un autre
                    clock.restart();
                    for (int i = 0; i < nombreMeteoAffiches; i++) {// mise a jour nb météos
                        window.draw(meteos[i]);
                    }//pour chaque météo du tableau meteos
                    window.display();
                    nbTourSimulation++; //a sauvegarder
                }
                sf::Time elapsedMeteo = clockMeteo.getElapsedTime();
                if (elapsedMeteo.asSeconds() > 20) {
                    nombreMeteoAffiches = rand() % NB_METEO + 1;
                    for (int i = 0; i < nombreMeteoAffiches; i++) {// mise a jour n premières météos
                        float x = rand() % 57 * 31.57;//taille écran divisé par taille d'une case en X
                        float y = rand() % 30 * 31.66;
                        meteos[i].setPosition(x, y);
                    }
                    clockMeteo.restart();

                }
            }
            std::cout << "Notre simulateur a pu realiser: " << nbTourSimulation << " tours de simulations" << std::endl;
        } else if(menu.getMChoix() == 1) {
            menu.parametrerSimulation(choixAvion, choixDepart, choixArrivee);
        }else if (menu.getMChoix() == 2) {
            menu.afficherListes();
        }
    }while(!end);
    return 0;
}