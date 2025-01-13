#include "Avion.h"
#include <iostream>
#include <limits>
#include <cmath>


///CONSTRUCTEURS-DESTRUCTEURS///

Avion::Avion(float consommation,float vitesseAvion, float altitude, std::string type,float capacite) {
    if (type == "court" && !backgroundTexture.loadFromFile("../Images/avion.png")) {  // load l'image en fonction du type de l'avion
        std::cout << "Erreur durant le chargement de l'image de background." << std::endl;
    }
    else if (type == "moyen" && !backgroundTexture.loadFromFile("../Images/avion_moyen.png")) { // load l'image en fonction du type de l'avion
        std::cout << "Erreur durant le chargement de l'image de background." << std::endl;
    } else if (type == "long" && !backgroundTexture.loadFromFile(
            "../Images/avion_long.png")) { // load l'image en fonction du type de l'avion
        std::cout << "Erreur durant le chargement de l'image de background." << std::endl;
    } else {    // attribution des attributs de l'avion
        m_altitude = altitude;
        m_consommation = consommation;
        m_vitesseAvion = vitesseAvion;
        m_capacite = capacite;
        m_type = std::move(type);
        m_crash = false;
        m_fuite = false;
        m_heureRestanteAvantDepart = rand() % 15;
        background.setTexture(backgroundTexture);
        m_chemin.clear(); //new
        m_parcourschemin = 0;
        m_EstdansAeroport = false;
    }
}

Avion::~Avion() = default;

/// GETTERS-SETTERS///
std::string Avion::getMType() const {
    return m_type;
}

float Avion::getMConsommation() const {
    return m_consommation;
}
void Avion::setMConsommation(float mConsommation) {
    m_consommation = mConsommation;
}

float Avion::getMCapacite() const {
    return m_capacite;
}

float Avion::getMVitesseAvion() const {
    return m_vitesseAvion;
}
void Avion::setMVitesseAvion(float mVitesseAvion) {
    m_vitesseAvion = mVitesseAvion;
}

float Avion::getMAltitude() const {
    return m_altitude;
}
void Avion::setMAltitude(float mAltitude) {
    m_altitude = mAltitude;
}

float Avion::getMPositionX() const {
    return m_position_x;
}
void Avion::setMPositionX(float mPositionX) {
    m_position_x = mPositionX;
}

float Avion::getMPositionY() const {
    return m_position_y;
}
void Avion::setMPositionY(float mPositionY) {
    m_position_y = mPositionY;
}

Aeroport *Avion::getDepart() const {
    return m_depart;
}
void Avion::setDepart(Aeroport *depart) {
   m_depart = depart;
}

Aeroport *Avion::getArrivee() const {
    return m_arrivee;
}
void Avion::setArrivee(Aeroport *arrivee) {
    m_arrivee = arrivee;
}

bool Avion::isMFuite() const {
    return m_fuite;
}
void Avion::setMFuite(bool mFuite) {
    m_fuite = mFuite;
}

bool Avion::isMCrash() const {
    return m_crash;
}
void Avion::setMCrash(bool mCrash) {
    m_crash = mCrash;
}

int Avion::getMHeureRestanteAvantDepart() const {
    return m_heureRestanteAvantDepart;
}
void Avion::setMHeureRestanteAvantDepart(int mHeureRestanteAvantDepart) {
    m_heureRestanteAvantDepart = mHeureRestanteAvantDepart;
}

std::vector<Case *> Avion::getChemin() const {
    return m_chemin;
}
void Avion::setChemin(const std::vector<Case *> &chemin) {
    m_chemin.clear();
    m_chemin = chemin;
}

bool Avion::isMEstdansAeroport() const {
    return m_EstdansAeroport;
}
void Avion::setMEstdansAeroport(bool mEstdansAeroport) {
    m_EstdansAeroport = mEstdansAeroport;
}

void Avion::setParcourschemin(int parcourschemin) {
    m_parcourschemin = parcourschemin;
}



bool Avion::isMEscale() const {
    return m_escale;
}
int Avion::getLimiteCases() const {
    return limiteCases;
}


///AFFICHAGE///

void Avion::setPositionImage(float mPositionX, float mPositionY) {
    background.setPosition(mPositionX, mPositionY);
}
void Avion::attributionAltitudeApresDepart() { // afin d'assurer que les altitudes se remettent correctement
    if (m_type== "court") {
        m_altitude = 1000; //valeus existante et determiné au préalable dans le txt
    }
    if (m_type== "moyen") {
        m_altitude = 9500;
    }
    if (m_type== "long") {
        m_altitude = 9000;
    }
}
void Avion::deplacer() {
    if (m_consommation >= m_capacite) {//cas d'une fuite qui n'as pas pu etre traites car la consommation a dépassé la capacité
        backgroundTexture.loadFromFile("../Images/avion_crash.png"); //affichage graphique du crash (cause fuite)
        background.setTexture(backgroundTexture); //affichage graphique du crash
    } else if (m_crash) {//cas d'un crash
        setPositionImage(m_position_x, m_position_y); //l'avion ne bouge plus
        backgroundTexture.loadFromFile("../Images/avion_crash.png"); //affichage graphique du crash
        background.setTexture(backgroundTexture); //affichage graphique du crash
    } else {
        if (m_depart->getMx()== m_position_x && m_depart->getMy() == m_position_y || m_arrivee->getMx() == m_position_x && m_arrivee->getMy() == m_position_y){
            setMVitesseAvion(getMVitesseAvion()/2); //si l'avion va decoller ou atterir on reduit la vitesse
        }
        attributionAltitudeApresDepart(); // remet l'altitude des avions a la valeur des fichiers lorsqqu'ils sont en vol
        deplacerSelonArc();//fonction qui permet a l'avion de bouger réellement
        fuiteReservoir(); // teste si une fuite a eu lieu et met a jour la consommation de l'avion en fonction du cas dnas lequel il se situe
    }
}
void Avion::fuiteReservoir() {
    int pourcentageFuite = rand()% 30; // pourcentage d'avoir une defaillance
    if (pourcentageFuite == 1 && !m_fuite){ // le cas d'une fuite naissante
        //std::cout << "L'avion partant de: "<< m_depart->getMNom()<<" en direction de: "<<m_arrivee->getMNom()<< " a une fuite" << std::endl;
        setMVitesseAvion(getMVitesseAvion()/2); // dans le cas d'une fuite, la vitesse diminue par 2
        setMConsommation(getMConsommation()+ m_consommation*0.20);// augmentation de la consommation de l'avion car début de fuite
        setMFuite(true); // marque que l'avion a une fuite
    }
    else if (m_fuite){// le cas ou il est deja en fuite
        setMConsommation(getMConsommation()+ m_consommation*0.20); // consommation de l'avion
    }
    else{ // pas en fuite et pas de début de fuite, la consommation est normale et s'incremente
        setMConsommation(getMConsommation() + m_consommation/6);
    }
}
void Avion::drawAvion(sf::RenderWindow &window) {
    background.setPosition(m_position_x,m_position_y); //set la position qui permet de remettre a jour
    window.draw(background); //dessine l'avion
    //std::cout<<"Heure avant le depart: "<<m_heureRestanteAvantDepart<<std::endl; //test affichage
    m_heureRestanteAvantDepart--; // a chaque boucle de simulation l'heure avant le depart diminue
    if(m_heureRestanteAvantDepart<= 0) {
        m_heureRestanteAvantDepart=0; //sécurité
        deplacer(); //une fois l'heure de départ prévue l'avion peut se déplacer
    }
}
void Avion::deplacerSelonArc() { // ce qui permet  a l'avion de se déplacer graphiquement en fonction du chemin

    if (m_type== "court") { //
        setMPositionX(m_chemin[m_parcourschemin]->getMPositionPixel().first);
        setMPositionY(m_chemin[m_parcourschemin]->getMPositionPixel().second);
    }
    if (m_type== "moyen") {
        setMPositionX(m_chemin[m_parcourschemin/2]->getMPositionPixel().first);
        setMPositionY(m_chemin[m_parcourschemin/2]->getMPositionPixel().second);
    }
    if (m_type== "long") {
        setMPositionX(m_chemin[m_parcourschemin/3]->getMPositionPixel().first);
        setMPositionY(m_chemin[m_parcourschemin/3]->getMPositionPixel().second);
    }
    if (m_position_x == m_arrivee->getPositionCase()->getMPositionPixel().first && m_position_y ==
                                                                                   m_arrivee->getPositionCase()->getMPositionPixel().second) { //pour assurer que l'avion atteigne la dernière position
        //std::cout << "l'avion est a la position de la derniere case du chemin" << std::endl;
        setMPositionX(m_arrivee->getMx());
        setMPositionY(m_arrivee->getMy());
        setParcourschemin(0);
    }
    m_parcourschemin += 1;
}


///CALCULS///

void Avion::calculPCC(std::vector<Case*> &cases) {
    m_chemin.clear();
    for(auto &m : cases){
        m->setMarque(false);
        m->setDistance(std::numeric_limits<int>::max());
    }
    m_depart->setDistancePositionCase(0);
    std::vector<std::vector<Case*>> predecesseurs(57, std::vector<Case*> (30));
    int distancePrec;
    Case* c;
    do {
        distancePrec=std::numeric_limits<int>::max();
        for (auto i: cases) {
            if (!i->getMarque()) {
                if (i->getDistance() < distancePrec ) {
                    c = i;//On récupere la case la plus proche du depart
                    distancePrec=i->getDistance();
                }
            }
        }
        c->setMarque(true);//on marque la case la plus proche du depart
        for (auto j: c->getSuccesseurs()) {
            if (!j.first->getMarque()) {
                if (c->getDistance() + j.second < (float)j.first->getDistance()) {
                    j.first->setDistance(c->getDistance() + j.second);
                    predecesseurs[j.first->getPosition().first][j.first->getPosition().second]=c;
                }
            }
        }
    }while(c!=m_arrivee->getPositionCase());
    //std::cout<<"PCC bien effectue, affichage : "<<std::endl;

    m_chemin.push_back(m_arrivee->getPositionCase());
    Case* j=predecesseurs[m_arrivee->getMXCase()][m_arrivee->getMYCase()];
    do{
        m_chemin.push_back(j);
        j=predecesseurs[j->getPosition().first][j->getPosition().second];
    }while(j!=m_depart->getPositionCase());
    m_chemin.push_back(j);
    std::reverse(m_chemin.begin(), m_chemin.end());
    m_parcourschemin=0;
}

void Avion::testEscale(){
    m_escale=false;
    if(m_type=="court"){
        limiteCases=10;
    }else if (m_type=="moyen"){
        limiteCases=30;
    }else if(m_type=="long"){
        limiteCases=std::numeric_limits<int>::max();
    }
    if(m_chemin.size()>limiteCases){
        std::cout<<"Le trajet est trop long pour un "<<m_type<<" courrier, voyons si une escale est possible"<<std::endl;
        m_escale=true;
    }

}


bool Avion::contient(float x, float y) {
    return background.getGlobalBounds().contains(x,y);
}

///fonctions non finalisées
/*
 auto cmp = [](std::pair<Case*,float> paire1, std::pair<Case*,float> paire2){ return paire2.second < paire1.second;};
float Avion::calculEstimation(Case* c){
    float calculHeuristique;
    float estimation;
    calculHeuristique=(float) sqrt(pow(c->getPosition().first-m_depart->getMXCase(),2)+pow(c->getPosition().second-m_depart->getMYCase(),2));
    estimation=(float) c->getDistance()+calculHeuristique;
    return estimation;
}
 void Avion::calculAStar(std::vector<Case*> &cases){
    std::priority_queue<std::pair<Case*,float>, std::vector<std::pair<Case*,float>>, decltype(cmp)> queue(cmp);
    bool end=false;
    Case* s;

    std::cout<<m_depart->getMNom()<<"->"<<m_arrivee->getMNom()<<std::endl;
    for(auto &m : cases){
        m->setMarque(0);
        m->setDistance(0);
        m->clearPredecesseurs();
    }
    queue.push(std::pair<Case*,float>(m_depart->getPositionCase(), calculEstimation(m_depart->getPositionCase())));
    while(!end){

        s=queue.top().first;
        queue.pop();

        if (s==m_arrivee->getPositionCase()){
            end=true;
        }else{
            s->setMarque(2);
            //std::cout<<"Sommet ";
            //s.first->afficherPosition();
            //std::cout<<" marque : "<<s.first->getMarque()<<std::endl;
            for(auto &x : s->getSuccesseurs()){
                if(x.first->getMarque()==0){
                    x.first->setDistance(s->getDistance()+1);
                    x.first->addPredecesseur(s);
                    x.first->setMarque(1);
                    queue.push(std::pair<Case*,float> (x.first, calculEstimation(x.first)));
                }else {
                    if(x.first->getMarque()==1) {
                        if ((s->getDistance() + 1) < x.first->getDistance()) {
                            x.first->setDistance(s->getDistance() + 1);
                            x.first->addPredecesseur(s);
                            queue.push(std::pair<Case *, float>(x.first, calculEstimation(x.first)));
                        }
                    }
                    if(x.first->getMarque()==2){
                        if((s->getDistance()+1)<x.first->getDistance()){
                            x.first->setDistance(s->getDistance()+1);
                            x.first->addPredecesseur(s);
                            queue.push(std::pair<Case*,float>(x.first, calculEstimation(x.first)));
                        }
                    }
                }
            }
        }
    }
    std::cout << "Sommets explores :" << std::endl;
    for(auto c:cases) {
        if(c->getMarque()==2){
            c->afficherPosition();
        }
    }
}

bool Avion::contient(float x, float y) {
    return background.getGlobalBounds().contains(x,y);
}
void Avion::setMType(std::string mType) {
    m_type = std::move(mType);
}

void Avion::setMCapacite(float mCapacite) {
    m_capacite = mCapacite;
}
int Avion::getParcourschemin() const {
    return m_parcourschemin;
}
void Avion::affichagePCC(){
    auto i=m_chemin.size();
    while (i!=0){
        m_chemin[i-1]->afficherPosition();
        std::cout<<"--->";
        i--;
    }
}

bool Avion::tousSommetsMarques(std::vector<Case*> &cases) {
    bool retour;
    for(auto i : cases){
        if (i->getMarque()){
            retour=true;
        }
        else return false;
    }
    return retour;
}
 */