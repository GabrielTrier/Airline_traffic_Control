#include "Aeroport.h"


///CONSTRUCTEURS-DESTRUCTEUR///

Aeroport::Aeroport(int id, int mNbPistes, int mNbPlaces, std::string mNom, float mChargement, float mDechargement,
                   float mAccesPistes, float mAnticollision, float mTdecollage, float mTatterissage,
                   float mBoucleAttente, float mX, float mY, int xCase, int yCase) : m_id(id),
                                                                                     m_NbPistes(mNbPistes),
                                                                                     m_NbPlaces(mNbPlaces),
                                                                                     m_Nom(std::move(mNom)),
                                                                                     m_Chargement(mChargement),
                                                                                     m_Dechargement(mDechargement),
                                                                                     m_AccesPistes(mAccesPistes),
                                                                                     m_Anticollision(mAnticollision),
                                                                                     m_Tdecollage(mTdecollage),
                                                                                     m_Tatterissage(mTatterissage),
                                                                                     m_BoucleAttente(mBoucleAttente),
                                                                                     m_position_X(mX), m_position_Y(mY),
                                                                                     m_xCase(xCase), m_yCase(yCase) {
    m_isAccessible=true;
    rect.setSize(sf::Vector2f(30, 30));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(m_position_X, m_position_Y));

}
Aeroport::Aeroport(float mX, float mY) {
    rect.setSize(sf::Vector2f(30, 30));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(mX, mY));
}
Aeroport::~Aeroport(){
    m_file.clear();
}


///GETTERS-SETTERS///

sf::Vector2f Aeroport::getPosition() const {
    return rect.getPosition() + rect.getSize() / 2.f;//arc au centre
}

int Aeroport::getMNbPistes() const {
    return m_NbPistes;
}
void Aeroport::setMNbPistes(int mNbPistes) {
    m_NbPistes = mNbPistes;
}

int Aeroport::getMNbPlaces() const {
    return m_NbPlaces;
}
void Aeroport::setMNbPlaces(int mNbPlaces) {
    m_NbPlaces = mNbPlaces;
}

std::string Aeroport::getMNom() const {
    return m_Nom;
}
void Aeroport::setMNom(char mNom) {
    m_Nom = mNom;
}

float Aeroport::getMChargement() const {
    return m_Chargement;
}
void Aeroport::setMChargement(float mChargement) {
    m_Chargement = mChargement;
}

float Aeroport::getMDechargement() const {
    return m_Dechargement;
}
void Aeroport::setMDechargement(float mDechargement) {
    m_Dechargement = mDechargement;
}

float Aeroport::getMAccesPistes() const {
    return m_AccesPistes;
}
void Aeroport::setMAccesPistes(float mAccesPistes) {
    m_AccesPistes = mAccesPistes;
}

float Aeroport::getMAnticollision() const {
    return m_Anticollision;
}
void Aeroport::setMAnticollision(float mAnticollision) {
    m_Anticollision = mAnticollision;
}

float Aeroport::getMTdecollage() const {
    return m_Tdecollage;
}
void Aeroport::setMTdecollage(float mTdecollage) {
    m_Tdecollage = mTdecollage;
}

float Aeroport::getMTatterissage() const {
    return m_Tatterissage;
}
void Aeroport::setMTatterissage(float mTatterissage) {
    m_Tatterissage = mTatterissage;
}

float Aeroport::getMBoucleAttente() const {
    return m_BoucleAttente;
}
void Aeroport::setMBoucleAttente(float mBoucleAttente) {
    m_BoucleAttente = mBoucleAttente;
}

float Aeroport::getMx() const {
    return m_position_X;
}
void Aeroport::setMx(float mX) {
    Aeroport::m_position_X = mX;
}

float Aeroport::getMy() const {
    return m_position_Y;
}
void Aeroport::setMy(float mY) {
    Aeroport::m_position_Y = mY;
}

Case *Aeroport::getPositionCase() {
    return m_positionCase;
}
void Aeroport::setPositionCase(Case *&positionCase) {
    m_positionCase = positionCase;
}

void Aeroport::setDistancePositionCase(int nb) {
    m_positionCase->setDistance(nb);
}

int Aeroport::getMXCase() const {
    return m_xCase;
}
int Aeroport::getMYCase() const {
    return m_yCase;
}

int Aeroport::getMId() const {
    return m_id;
}
void Aeroport::setMId(int mId) {
    m_id = mId;
}

bool Aeroport::isMIsAccessible() const {
    return m_isAccessible;
}
void Aeroport::setMIsAccessible(bool mIsAccessible) {
    m_isAccessible = mIsAccessible;
}


///AFFICHAGE///

void Aeroport::dessiner(sf::RenderWindow &window) {
    window.draw(rect);
}


///METHODES///

std::deque<Avion *> &Aeroport::getFile() {
    return m_file;
}

bool Aeroport::contient(float x, float y) {
    return rect.getGlobalBounds().contains(x,y);// on récupère les positions graphique de l'aeroport pour savoir si le
    // est bien positionée dans le carré
}

void Aeroport::marquerAeroportBloque()  {
    rect.setFillColor(sf::Color(100,100,100));
}

