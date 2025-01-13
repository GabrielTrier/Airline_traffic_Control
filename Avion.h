#ifndef CONTROLEAERIEN_AVION_H
#define CONTROLEAERIEN_AVION_H

#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include "Aeroport.h"
#include "arc.h"
#include "case.h"
#include <SFML/Graphics.hpp>



class Avion {
private:
    int m_heureRestanteAvantDepart, limiteCases;
    std::string m_type;
    float m_consommation,m_capacite,m_vitesseAvion,m_altitude,m_position_x,m_position_y;
    bool m_fuite,m_crash, m_escale,m_EstdansAeroport;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Aeroport* m_depart;
    Aeroport* m_arrivee;
    std::vector<Case*> m_chemin;
    int m_parcourschemin;

public:
    Avion(float consommation,float vitesseAvion, float altitude, std::string type,float capacite);

    virtual ~Avion();

    bool isMEstdansAeroport() const;
    void setMEstdansAeroport(bool mEstdansAeroport);

    bool isMFuite() const;
    void setMFuite(bool mFuite);

    bool isMCrash() const;
    void setMCrash(bool mCrash);

    bool contient(float x, float y);

    Aeroport *getDepart() const;
    void setDepart(Aeroport* depart);

    Aeroport *getArrivee() const;
    void setArrivee(Aeroport* arrivee);

    std::vector<Case *> getChemin() const;
    void setChemin(const std::vector<Case *> &chemin);


    std::string getMType() const;


    float getMConsommation() const;
    void setMConsommation(float mConsommation);

    void fuiteReservoir();

    float getMCapacite() const;


    float getMVitesseAvion() const;
    void setMVitesseAvion(float mVitesseAvion);

    float getMAltitude() const;
    void setMAltitude(float mAltitude);

    float getMPositionX() const;
    void setMPositionX(float mPositionX);

    float getMPositionY() const;
    void setMPositionY(float mPositionY);

    int getMHeureRestanteAvantDepart() const;
    void setMHeureRestanteAvantDepart(int mHeureRestanteAvantDepart);

    bool isMEscale() const;
    int getLimiteCases() const;


    void drawAvion(sf::RenderWindow &window);
    void setPositionImage(float mPositionX,float mPositionY);
    void deplacer();
    void deplacerSelonArc();
    void calculPCC(std::vector<Case*> &cases);
    void testEscale();


    void setParcourschemin(int parcourschemin);

    void attributionAltitudeApresDepart();

    ///Fonctions non finalisées
    /*
    void affichagePCC();
    void calculAStar(std::vector<Case*> &cases);
    float calculEstimation(Case* c);
    int getParcourschemin() const;
    void setMCapacite(float mCapacite);
    void setMType(std::string mType);
    static bool tousSommetsMarques(std::vector<Case*> &cases);*/

};

#endif
