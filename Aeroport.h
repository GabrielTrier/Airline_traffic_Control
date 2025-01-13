#ifndef CONTROLEAERIEN_AEROPORT_H
#define CONTROLEAERIEN_AEROPORT_H
#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "case.h"

class Avion;

class Aeroport{
private:
    int m_id;
    int m_NbPistes,m_NbPlaces;
    std::string m_Nom;
    float m_Chargement,m_Dechargement,m_AccesPistes,m_position_X,m_position_Y;
    float m_Anticollision,m_Tdecollage,m_Tatterissage, m_BoucleAttente;
    int m_xCase,m_yCase;
    Case* m_positionCase;
    bool m_isAccessible;
    std::deque<Avion *> m_file;
    sf::RectangleShape rect;

public:
    Aeroport(int id, int mNbPistes, int mNbPlaces, std::string mNom, float mChargement,float mDechargement,
             float mAccesPistes, float mAnticollision,float mTdecollage,float mTatterissage,
             float mBoucleAttente,float mX, float mY,int xCase,int yCase);
    Aeroport(float mX,float mY);
    ~Aeroport();

    void dessiner(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;

    bool isMIsAccessible() const;
    void setMIsAccessible(bool mIsAccessible);

    int getMId() const;
    void setMId(int mId);

    int getMNbPistes() const;
    void setMNbPistes(int mNbPistes);

    int getMNbPlaces() const;
    void setMNbPlaces(int mNbPlaces);

    std::string getMNom() const;
    void setMNom(char mNom);

    float getMChargement() const;
    void setMChargement(float mChargement);

    float getMDechargement() const;
    void setMDechargement(float mDechargement);


    float getMAccesPistes() const;
    void setMAccesPistes(float mAccesPistes);

    float getMAnticollision() const;
    void setMAnticollision(float mAnticollision);

    float getMTdecollage() const;
    void setMTdecollage(float mTdecollage);

    float getMTatterissage() const;
    void setMTatterissage(float mTatterissage);

    float getMBoucleAttente() const;
    void setMBoucleAttente(float mBoucleAttente);

    float getMx() const;
    void setMx(float mX);

    float getMy() const;
    void setMy(float mY);

    Case* getPositionCase();
    void setPositionCase(Case* &positionCase);
    void setDistancePositionCase(int nb);

    int getMXCase() const;

    int getMYCase() const;

    std::deque<Avion *> &getFile();

    bool contient(float x, float y);
    void marquerAeroportBloque()  ;

};

#endif
