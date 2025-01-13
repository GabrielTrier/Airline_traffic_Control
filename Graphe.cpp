#include "Graphe.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <valarray>


Graphe::Graphe(const std::string &filename_Aeroport, const std::string &filename_Arc,
               const std::string &filename_Avion) {

    ///LECTURE DES AEROPORTS
    std::ifstream ifs{filename_Aeroport};
    if (!ifs) { throw std::runtime_error("Impossible d'ouvrir " + filename_Aeroport); }

    int nbAeroports = 0;
    ifs >> nbAeroports;
    if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de l'ordre du graphe."); }

    for (int i = 0; i < nbAeroports; ++i) {
        char retourAlaligne;
        ifs >> retourAlaligne;
        std::string mNom;
        std::string Nom;
        std::getline(ifs, Nom);
        mNom = retourAlaligne + Nom;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mNom de l'aeroport."); }
        int mNbPistes = 0;
        ifs >> mNbPistes;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mNbPistes de l'aeroport."); }
        int mNbPlaces = 0;
        ifs >> mNbPlaces;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mNbPlaces de l'aeroport."); }
        float mChargement = 0;
        ifs >> mChargement;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mChargement de l'aeroport."); }
        float mDechargement = 0;
        ifs >> mDechargement;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mDechargement de l'aeroport."); }
        float mAccesPistes = 0;
        ifs >> mAccesPistes;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mAccesPistes de l'aeroport."); }
        float mAnticollision = 0;
        ifs >> mAnticollision;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de nbAeroports de l'aeroport."); }
        float mTdecollage = 0;
        ifs >> mTdecollage;
        if (ifs.fail()) { throw std::runtime_error("Problème de lecture de mTdecollage de l'aeroport."); }
        float mTatterissage = 0;
        ifs >> mTatterissage;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mTatterissage de l'aeroport."); }
        float mBoucleAttente = 0;
        ifs >> mBoucleAttente;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mBoucleAttente de l'aeroport."); }
        float mX = 0;
        ifs >> mX;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mX de l'aeroport."); }
        float mY = 0;
        ifs >> mY;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de mY de l'aeroport."); }
        int xCase, yCase;
        ifs >> xCase;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de xCase de l'aeroport."); }
        ifs >> yCase;
        if (ifs.fail()) { throw std::runtime_error("Probleme de lecture de yCase de l'aeroport."); }
        m_aeroports.push_back(new Aeroport((int) i, mNbPistes, mNbPlaces, mNom, mChargement, mDechargement,
                                           mAccesPistes, mAnticollision, mTdecollage, mTatterissage, mBoucleAttente, mX,
                                           mY, xCase, yCase));
    }
    ifs.close();

    if (!font.loadFromFile("../Arial.ttf")) {
        std::cout << "Erreur chargement";
    }
    infoTAeroport.setFont(font);
    infoTAeroport.setCharacterSize(20);
    infoTAeroport.setFillColor(sf::Color::White);
    infoAeroport.setSize(sf::Vector2f(400, 200));
    infoAeroport.setFillColor((sf::Color(127, 100, 200)));
    infoArc.setFont(font);
    infoArc.setCharacterSize(20);
    infoArc.setFillColor(sf::Color::Black);
    //dessin avion
    infoTAvion.setFont(font);
    infoTAvion.setCharacterSize(20);
    infoTAvion.setFillColor(sf::Color::White);
    infoAvion.setSize(sf::Vector2f(400, 200));
    infoAvion.setFillColor((sf::Color(127, 100, 200)));

    ///LECTURE DES ARCS
    std::ifstream ifA{filename_Arc};
    if (!ifA) { throw std::runtime_error("Impossible d'ouvrir " + filename_Arc); }

    int ordre;
    ifA >> ordre;
    if (ifA.fail()) { throw std::runtime_error("Probleme de lecture de l'ordre du graphe."); }

    int taille;
    ifA >> taille;
    if (ifA.fail()) {
        throw std::runtime_error("Probleme de lecture de la taille du graphe.");
    }

    int num1 = 0, num2 = 0, poids = 0;
    for (int i = 0; i < taille; ++i) {
        ifA >> num1 >> num2 >> poids;
        if (ifA.fail()) { throw std::runtime_error("Problème de lecture d'un arc."); }

        m_arcs.push_back(new Arc(m_aeroports[num1], m_aeroports[num2],
                                 poids)); //permet d'ajouter directement les arcs grace aux données récupérés du fichier
    }
    ifA.close();

    ///Lecture des avions
    std::ifstream ifsAvion{filename_Avion}; // lecture du fichier avion
    if (!ifsAvion) { throw std::runtime_error("Impossible d'ouvrir " + filename_Avion); }

    int nbAvions = 0;
    ifsAvion >> nbAvions;
    if (ifsAvion.fail()) { throw std::runtime_error("Probleme de lecture du nbr d'avions."); }

    float avionCapacite = 0, avionConsommation = 0;
    std::string avionType;
    float avionVitesse = 0, avionAltitude = 0;

    for (int i = 0; i < nbAvions; ++i) {
        ifsAvion >> avionCapacite >> avionConsommation >> avionType >> avionVitesse >> avionAltitude;
        if (ifsAvion.fail()) { throw std::runtime_error("Probleme de lecture des parametres de l'avions."); }

        m_avions.push_back(new Avion(avionConsommation, avionVitesse, avionAltitude, avionType,
                                     avionCapacite)); //permet de créer directement des avions
    }
    ifsAvion.close();
}

Graphe::~Graphe() { //destruction de tous les elements du graphe
    std::cout << "Destruction d'un graphe." << std::endl;

    std::cout << "Destruction des avions." << std::endl;
    for (auto s: m_avions) {
        delete s;
    }
    std::cout << "Destruction des arcs." << std::endl;
    for (auto s: m_arcs) {
        delete s;
    }
    std::cout << "Destruction des aeroports." << std::endl;
    for (auto s: m_aeroports) {
        delete s;
    }
}

void Graphe::dessinerGraphe(sf::RenderWindow &window) {
    for (auto s: m_aeroports) { // on dessine tout le graphe
        s->dessiner(window);
    }
    for (auto s: m_arcs) {
        s->dessiner(window);
        //On récupère les 2 sommets (extrémités)
        float x1 = s->getPremier()->getMx(), x2 = s->getSecond()->getMx();
        float y1 = s->getPremier()->getMy(), y2 = s->getSecond()->getMy();
        float x = x2 - x1, y = y2 - y1;
        float longueur = std::sqrt(x * x + y * y);
        x /= longueur;
        y /= longueur;
        float produitScalaire = x * 1 + y * 0, determinant = x * 0 - y * 1;
        // Orientation de l'arc
        float angle =std::atan2(determinant, produitScalaire) * 180 /
                     3.14159;//arctan projette les vecteurs, pour avoir en degrés
        if (angle < 45 && angle > -45) {//arc horizontal
            infoArc.setPosition((x1 + x2) / 2.f, (y1 + y2) / 2.f - 20.f);
        } else {
            infoArc.setPosition((x1 + x2) / 2.f + 20.f, (y1 + y2) / 2.f);
        }

        infoArc.setString(std::to_string(s->getMPoids()));
        window.draw(infoArc);
    }
    for (auto s: m_avions) {
        s->drawAvion(window);
    }
    //Dessin des infomations
    if (aeroportSelect != nullptr) {
        infoAeroport.setPosition(aeroportSelect->getMx() + 5, aeroportSelect->getMy() + 5);
        window.draw(infoAeroport);
        infoTAeroport.setString(
                aeroportSelect->getMNom() + "\n" + "Pistes:" + std::to_string(aeroportSelect->getMNbPistes()) + "\n" +
                "Places au sol:" + std::to_string((aeroportSelect->getMNbPlaces())) + "\n" + "Attente au sol:" +
                std::to_string(aeroportSelect->getMBoucleAttente()) + "\n" + "Acces aux pistes:" +
                std::to_string(aeroportSelect->getMAccesPistes()) + "\n" + "Duree atter/decol:" +
                std::to_string(aeroportSelect->getMTdecollage()) + "\n" + "Anti-collision" +
                std::to_string(aeroportSelect->getMAnticollision()) + "\n" + "Boucle d'attente:" +
                std::to_string(aeroportSelect->getMBoucleAttente()));
        infoTAeroport.setPosition(aeroportSelect->getMx() + 20, aeroportSelect->getMy() + 20);
        window.draw(infoTAeroport);
    }
    if (avionSelect != nullptr) {
        //dessin des informations
        infoAvion.setPosition(avionSelect->getMPositionX() + 2, avionSelect->getMPositionY() + 2);
        window.draw(infoAvion);
        infoTAvion.setPosition(avionSelect->getMPositionX() + 20, avionSelect->getMPositionY() + 20);
        infoTAvion.setString("Type de l'avion: " + avionSelect->getMType() + "\n" + "Consommation: " +
                             std::to_string(avionSelect->getMConsommation()) + "\n" + "Carburant: " +
                             std::to_string(avionSelect->getMCapacite()) + "\n " + "Vitesse: " +
                             std::to_string(avionSelect->getMVitesseAvion()) + "\n" + "Altitude: " +
                             std::to_string(avionSelect->getMAltitude()));
        window.draw(infoTAvion);
    }

}

void Graphe::attribuerAeroport() { //permet d'attribuer un aeroport de depart et d'arrivee a tous les avions
    size_t total = m_aeroports.size();
    std::cout << "Nbr d'aeroports : " << total << std::endl;//test affichage
    for (auto &m_avion: m_avions) {
        int j;
        int k;
        do {
            do {
                j = rand() % total;
                k = rand() % total;
            } while (!m_aeroports[j]->isMIsAccessible() && !m_aeroports[j]->isMIsAccessible());
        } while (j == k); //boucle tant que les numeros sont pas differents

        //std::cout<<"Depart : "<<j<<" "<<"Arrivee : "<<k<<std::endl;// test affichage
        m_avion->setMPositionX(m_aeroports[j]->getMx());//positions de l'avion
        m_avion->setMPositionY(m_aeroports[j]->getMy());//positions de l'avion
        m_avion->setDepart(m_aeroports[j]);//attribution des aeroports
        m_avion->setArrivee(m_aeroports[k]);
    }
}

void Graphe::AeroportBloque() { // afin de determiner l'aeroport qui sera bloque a chaque simulation (contrainte sujet)
    size_t total = m_aeroports.size();
    int i = rand() % total;
    m_aeroports[i]->setMIsAccessible(false); // set l'aeroport comme étant inacessible
    std::cout << "L'aeroport " << m_aeroports[i]->getMNom() << " n'est pas accessible pour cause d'intemperies"
              << std::endl;
    m_aeroports[i]->marquerAeroportBloque(); // change la couleur de l'aeroport
}

void Graphe::nouvelleDestination() { //lorsqu'un avion a pu effectuer un premier vol on lui attribue un nouveau plan de vol
    size_t total = m_aeroports.size();
    for (auto &m_avion: m_avions) {
        if (m_avion->getMPositionX() == m_avion->getArrivee()->getMx() &&
            m_avion->getMPositionY() == m_avion->getArrivee()->getMy()) {
            ///Une fois l'avion bien arrivee la consommation,l'altitude est remis a 0 et une nouvelle heure de dpeart est prévue
            int k = rand() % 15;
            m_avion->setMConsommation(0);
            m_avion->setMAltitude(0);
            m_avion->setMHeureRestanteAvantDepart(k);

            m_avion->setDepart(m_avion->getArrivee());// l'aeroport d'arrivee inital devient l'aeroport de depart

            m_avion->setMPositionX(
                    m_avion->getArrivee()->getMx());//securite permettant de mettre les positions de l'avion a celle de l'aeroport actuel (pas forcement necessaire)
            m_avion->setMPositionY(m_avion->getArrivee()->getMy());//positions de l'avion
            int j;
            do{
                j= rand() % total;
            }while(!m_aeroports[j]->isMIsAccessible());

            m_avion->setArrivee(
                    m_aeroports[j]); /// set un nouvel aeroport d'arrivee forcement different sinon la fonction se relancera automatiquement
            PCCAvionUnique(m_avion); // on recalcul le PCC pour ce nouveau trajet
            calculEscales(); // afin de tester la possibilité de faire une escale
        }
    }
}

void Graphe::testerCollision() {
    for (int i = 0; i < m_avions.size(); ++i) {
        for (int j = 0; j < m_avions.size(); ++j) {
            if (m_avions[i]->getMHeureRestanteAvantDepart() == 0 && m_avions[j]->getMHeureRestanteAvantDepart() ==
                                                                    0) { // il faut que les avions soient en vol pour pouvoir se crash
                if (i != j && m_avions[i]->getMPositionX() == m_avions[j]->getMPositionX() &&
                    m_avions[i]->getMPositionY() == m_avions[j]->getMPositionY() &&
                    m_avions[i]->getMAltitude() ==
                    m_avions[j]->getMAltitude() && !m_avions[i]->isMEstdansAeroport() &&
                    !m_avions[j]->isMEstdansAeroport()) { // test si les avions se crash en ayant la meme position et la meme altitude
                    m_avions[i]->setMCrash(true);
                    m_avions[j]->setMCrash(true);
                    std::cout << "L'avion partant de: " << m_avions[i]->getDepart()->getMNom()
                              << " en direction de: "
                              << m_avions[j]->getArrivee()->getMNom() << " a crash"
                              << std::endl; //affichage console
                }
            }
        }
    }
}

void Graphe::initCases() {
    int num = 0;
    float x, y = 0;
    for (int i = 0; i < 57; i++) {
        y = 0;
        for (int j = 0; j < 30; j++) {
            m_cases.push_back(new Case(std::pair<int, int>(i, j), (std::pair<float, float>(x, y)), num));
            num++;
            y += 31;
        }
        x+=31;
    }
    std::cout << "les cases sont bien initialisees" << std::endl;
    std::cout << "Taille : " << m_cases.size() << std::endl;
}

void Graphe::initPredecesseurs() {
    for(auto i:m_cases){
        for (auto j: m_cases){
            if(i->getPosition().first == j->getPosition().first && i->getPosition().second+1 == j->getPosition().second){///la case à droite
                i->addSuccesseur(j,1);
            }
            if(i->getPosition().first == j->getPosition().first && i->getPosition().second-1 == j->getPosition().second){///la case à gauche
                i->addSuccesseur(j,1);
            }
            if(i->getPosition().first+1 == j->getPosition().first && i->getPosition().second == j->getPosition().second){///la case en dessous
                i->addSuccesseur(j,1);
            }
            if(i->getPosition().first-1 == j->getPosition().first && i->getPosition().second == j->getPosition().second){///la case au dessus
                i->addSuccesseur(j,1);
            }
            if(i->getPosition().first+1 == j->getPosition().first && i->getPosition().second-1 == j->getPosition().second){///la diagonale haute droite
                i->addSuccesseur(j,2);
            }
            if(i->getPosition().first+1 == j->getPosition().first && i->getPosition().second+1 == j->getPosition().second){///la diagonale basse droite
                i->addSuccesseur(j, 2);
            }
            if(i->getPosition().first-1 == j->getPosition().first && i->getPosition().second-1 == j->getPosition().second){///la diagonale haute gauche
                i->addSuccesseur(j,2);
            }
            if(i->getPosition().first-1 == j->getPosition().first && i->getPosition().second+1 == j->getPosition().second){///la diagonale basse gauche
                i->addSuccesseur(j,2);
            }
        }
    }
    //std::cout<<"les predecesseurs sont bien initialises"<<std::endl;
}


Case *Graphe::selectionnerCase(int x, int y) {
    for (auto i: m_cases) {
        if (i->getPosition().first == x && i->getPosition().second == y) {
            return i;
        }
    }
    return nullptr;
}


void Graphe::PCCTotal() {
    for (auto a: m_avions) {
        a->calculPCC(m_cases);
    }
}

void Graphe::PCCAvionUnique(Avion* avion) { // utile pour faire a partir d'un seul avion
    avion->calculPCC(m_cases);
}

void Graphe::calculEscales() {
    for(auto &a : m_avions){
        a->testEscale();
        if(a->isMEscale()) {
            std::vector<Case*> cheminInitial = a->getChemin();
            Aeroport* arriveeInitiale = a->getArrivee();
            for (size_t aer = 0; aer < m_aeroports.size(); aer++) {
                if(m_aeroports[aer]!=a->getDepart()){
                    a->setArrivee(m_aeroports[aer]);
                    PCCAvionUnique(a);
                    if (a->getChemin().size() < a->getLimiteCases()) {
                        std::cout << "Nous avons trouve une escale ! Prochain arret : "
                                  << a->getArrivee()->getMNom()
                                  << std::endl;
                        aer=m_aeroports.size();
                    }
                }
            }
            if(a->getChemin().size()>a->getLimiteCases()){
                std::cout<<"Il n'y a malheureusement pas d'escale possible pour cet avion"<<std::endl;
                a->setArrivee(arriveeInitiale);
                a->setChemin(cheminInitial);
            }
        }
    }
}

void Graphe::initCasesAeroports() {
    for (auto i: m_aeroports) {
        Case *temp = selectionnerCase(i->getMXCase(), i->getMYCase());
        i->setPositionCase(temp);
    }
}

void Graphe::trouverAeroport(float x, float y) {
    for (auto s: m_aeroports) {
        if (s->contient(x, y)) {
            aeroportSelect = s;// sélectionner l'aéroport
            return;
        }
    }
    aeroportSelect = nullptr;//déselectionner l'aéroport
}

void Graphe::trouverAvion(float x, float y) {
    for (auto s: m_avions) {
        if (s->contient(x, y)) {
            avionSelect = s;// sélectionner l'avion
            return;
        }
    }
    avionSelect = nullptr;//déselectionner l'avion
}

void Graphe::sauvF_CA(int compteur) {
    std::ofstream f_CA{"../F_CA.txt"};
    if (!f_CA) { throw std::runtime_error("Impossible d'ouvrir le fichier F_CA"); }

    f_CA <<"Bienvenue dans le fichier text de sauvegarde du Projet \"Contrôle Aérien\""<<std::endl;
    f_CA <<"**********************************Les Aéroports**********************************"<<std::endl;
    ///Sauvegarde Aeroports
    f_CA <<std::endl<<"Il y a "<<m_aeroports.size()<<" aéroports dans ce monde !"<< std::endl<<std::endl;
    for (auto s: m_aeroports) {
        f_CA <<"\t\t\t"<<s->getMNom() << std::endl;
        f_CA << s->getMId() << " ";
        f_CA << s->getMNbPistes() << " ";
        f_CA << s->getMNbPlaces() << " ";
        f_CA << s->getMChargement() << " ";
        f_CA << s->getMDechargement() << " ";
        f_CA << s->getMAccesPistes() << " ";
        f_CA << s->getMAnticollision() << " ";
        f_CA << s->getMTdecollage() << " ";
        f_CA << s->getMTatterissage() << " ";
        f_CA << s->getMBoucleAttente() << " ";
        f_CA << s->getMx() << " ";
        f_CA << s->getMy() << " ";
        f_CA << s->getMXCase() << " ";
        f_CA << s->getMYCase() << " ";
        for(auto & t : s->getFile()){
            for(size_t p=0;p<m_avions.size();p++){
                if(m_avions[p]==t){
                    f_CA<<p<<" ";
                }
            }
        }
        f_CA<<std::endl<<std::endl;
    }
    f_CA <<"**********************************Les Arcs***************************************"<<std::endl<<std::endl;
    ///Sauvegarde Arcs
    f_CA <<"Il y a "<<m_aeroports.size()<<" \"sommets\" et "<<m_arcs.size()<<" arcs."<<std::endl<<std::endl;

    for (auto s: m_arcs) {
        f_CA << s->getPremier()->getMId() << " " <<
             s->getSecond()->getMId() << " " <<
             s->getMPoids() << std::endl;
    }
    f_CA<<std::endl;

    f_CA <<"**********************************Les Avions************************************"<<std::endl;
    ///Sauvegarde Avions
    int integer=1;
    f_CA <<std::endl<<"Il y a "<<m_avions.size()<<" avions."<<std::endl<<std::endl;
    for (auto s: m_avions) {
        f_CA <<"Avion n°"<<integer<<" :"<<std::endl;
        f_CA << s->getMCapacite() << " ";
        f_CA << s->getMConsommation() << " ";
        f_CA << s->getMType() << " ";
        f_CA << s->getMVitesseAvion() << " ";
        f_CA << s->getMAltitude() << " ";

        f_CA << s->getMPositionX() << " ";
        f_CA << s->getMPositionY() << " ";
        f_CA << s->getDepart()->getMId() << " " << s->getArrivee()->getMId()<<std::endl;
        f_CA <<s->getMHeureRestanteAvantDepart()<<std::endl;
        f_CA <<s->isMCrash()<<" "<<s->isMEscale()<<" "<<s->isMFuite()<<" "<<s->isMEstdansAeroport()<<std::endl;
        f_CA <<s->getDepart()->getMId()<<" "<<s->getArrivee()->getMId()<<std::endl;
        f_CA <<s->getMPositionX()<<" "<<s->getMPositionY()<<std::endl<<std::endl;
        integer++;
    }
    f_CA<<"Le simulateur a pu réaliser "<<compteur<<" tours de boucle avant de se terminer !"<<std::endl;
    f_CA.close();
}

void Graphe::gererQueue() {
    for (auto s: m_avions) {
/*********************************L'avion n'a pas les positions d'un aéroport de départ ET d'arrivée ***********************/
        if (s->getMPositionX() != s->getDepart()->getMx() && s->getMPositionY() != s->getDepart()->getMy() &&
            s->getMPositionX() != s->getArrivee()->getMx() && s->getMPositionY() != s->getArrivee()->getMy()) {
            ///Est-ce que l'avion est parti et est tjrs considéré dans une file ???
            if (s->isMEstdansAeroport()) { s->getDepart()->getFile().pop_front(); }
            s->setMEstdansAeroport(false);

        }
/*********************************L'avion a les positions d'un aéroport de départ OU d'arrivée *****************************/
        if (s->getMPositionX() == s->getDepart()->getMx() && s->getMPositionY() == s->getDepart()->getMy() ||
            s->getMPositionX() == s->getArrivee()->getMx() && s->getMPositionY() == s->getArrivee()->getMy()) {

            ///Est-ce que l'avion est dans une file ???
            if (!s->isMEstdansAeroport()) {
                if (s->getMPositionX() == s->getDepart()->getMx() && s->getMPositionY() == s->getDepart()->getMy() &&
                    s->getMPositionX() != s->getArrivee()->getMx() && s->getMPositionX() != s->getArrivee()->getMy()) {
                    s->getDepart()->getFile().push_back(s);
                    std::sort(s->getDepart()->getFile().begin(), s->getDepart()->getFile().end(),
                              [](Avion *s1, Avion *s2) {
                                  return s1->getMHeureRestanteAvantDepart() < s2->getMHeureRestanteAvantDepart();
                              });
                }
                if (s->getMPositionX() == s->getArrivee()->getMx() && s->getMPositionY() == s->getArrivee()->getMy() &&
                    s->getMPositionX() != s->getDepart()->getMx() && s->getMPositionY() != s->getDepart()->getMy()) {
                    s->getArrivee()->getFile().push_back(s);
                    std::sort(s->getArrivee()->getFile().begin(), s->getArrivee()->getFile().end(),
                              [](Avion *s1, Avion *s2) {
                                  return s1->getMHeureRestanteAvantDepart() < s2->getMHeureRestanteAvantDepart();
                              });
                }
            }
            s->setMEstdansAeroport(true);

        }
    }
}

const std::vector<Aeroport *> &Graphe::getMAeroports() const {
    return m_aeroports;
}

const std::vector<Avion *> &Graphe::getMAvions() const {
    return m_avions;
}


///Fonctions non finalisées ou de vérification
/*
bool Graphe::tousSommetsMarques() const {
    bool retour;
    for (auto i: m_cases) {
        if (i->getMarque()) {
            retour = true;
        } else return false;
    }
    return retour;
}
Case *Graphe::selectionnerCasePixel(float x, float y) {
    for (auto i: m_cases) {
        if (i->getMPositionPixel().first == x && i->getMPositionPixel().second == y) {
            return i;
        }
    }
    return nullptr;
}
Aeroport *Graphe::selectionnerAeroport(const std::string &nom) {
    for (auto a: m_aeroports) {
        if (nom == a->getMNom()) {
            return a;
        }
    }
    return nullptr;
}

Avion *Graphe::selectionnerAvion(int nb) {
    return m_avions[nb];
}

void Graphe::affichagePCC(std::vector<Case *> &chemin) {
    auto i = chemin.size();
    while (i != 0) {
        chemin[i - 1]->afficherPosition();
        std::cout << "--->";
        i--;
    }
    std::cout << "\n" << std::endl;
}

void Graphe::AStar() {
    for (auto a: m_avions) {
        a->calculAStar(m_cases);
    }
}

void Graphe::lectF_CA() {
    std::ifstream f_CA{"../F_CA.txt"};
    if (!f_CA) { throw std::runtime_error("Impossible d'ouvrir le fichier F_CA"); }


    ///Lecture Aeroports
    int nbAeroports = 0;
    f_CA >> nbAeroports;
    if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de l'ordre du graphe."); }

    for (size_t i = 0; i < nbAeroports; ++i) {
        char retourAlaligne;
        f_CA >> retourAlaligne;
        std::string mNom;
        std::string Nom;
        std::getline(f_CA, Nom);
        mNom = retourAlaligne + Nom;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mNom de l'aeroport."); }
        int id;
        f_CA >> id;
        int mNbPistes = 0;
        f_CA >> mNbPistes;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mNbPistes de l'aeroport."); }
        int mNbPlaces = 0;
        f_CA >> mNbPlaces;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mNbPlaces de l'aeroport."); }
        float mChargement = 0;
        f_CA >> mChargement;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mChargement de l'aeroport."); }
        float mDechargement = 0;
        f_CA >> mDechargement;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mDechargement de l'aeroport."); }
        float mAccesPistes = 0;
        f_CA >> mAccesPistes;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mAccesPistes de l'aeroport."); }
        float mAnticollision = 0;
        f_CA >> mAnticollision;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de nbAeroports de l'aeroport."); }
        float mTdecollage = 0;
        f_CA >> mTdecollage;
        if (f_CA.fail()) { throw std::runtime_error("Problème de lecture de mTdecollage de l'aeroport."); }
        float mTatterissage = 0;
        f_CA >> mTatterissage;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mTatterissage de l'aeroport."); }
        float mBoucleAttente = 0;
        f_CA >> mBoucleAttente;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mBoucleAttente de l'aeroport."); }
        float mX = 0;
        f_CA >> mX;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mX de l'aeroport."); }
        float mY = 0;
        f_CA >> mY;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de mY de l'aeroport."); }
        int xCase, yCase;
        f_CA >> xCase;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de xCase de l'aeroport."); }
        f_CA >> yCase;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de yCase de l'aeroport."); }
        m_aeroports.push_back(new Aeroport(id, mNbPistes, mNbPlaces, mNom, mChargement, mDechargement,
                                           mAccesPistes, mAnticollision, mTdecollage, mTatterissage, mBoucleAttente, mX,
                                           mY, xCase, yCase));
    }

    ///LECTURE DES ARCS
    int ordre;
    f_CA >> ordre;
    if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de l'ordre du graphe."); }

    int taille;
    f_CA >> taille;
    if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture de la taille du graphe."); }

    int num1 = 0, num2 = 0, poids = 0;
    for (size_t i = 0; i < taille; ++i) {
        f_CA >> num1 >> num2 >> poids;
        if (f_CA.fail()) { throw std::runtime_error("Problème de lecture d'un arc."); }

        m_arcs.push_back(new Arc(m_aeroports[num1], m_aeroports[num2], poids));
    }

    ///Lecture des avions
    int nbAvions = 0;
    f_CA >> nbAvions;
    if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture du nbr d'avions."); }

    float avionCapacite = 0, avionConsommation = 0;
    std::string avionType;
    float avionVitesse = 0, avionAltitude = 0;
    float positionX, positionY;
    int iD_AeroportDep, iD_AeroportArr;

    for (size_t i = 0; i < nbAvions; ++i) {
        f_CA >> avionCapacite >> avionConsommation >> avionType >> avionVitesse >> avionAltitude >>
             positionX >> positionY >> iD_AeroportDep >> iD_AeroportArr;
        if (f_CA.fail()) { throw std::runtime_error("Probleme de lecture des parametres de l'avions."); }
        m_avions.push_back(new Avion(avionConsommation, avionVitesse, avionAltitude, avionType, avionCapacite,
                                     positionX, positionY, iD_AeroportDep, iD_AeroportArr));
    }

    std::cout << "Lecture realisee avec succes !" << std::endl;
    f_CA.close();
}

float Graphe::heuristique(int S0, Case *S1) {
    if (m_cases[S0]->getPosition().first != S1->getPosition().first &&
        m_cases[S0]->getPosition().second != S1->getPosition().second) {
        return (float) sqrt(2);
    } else {
        return 1;
    }
}

void Graphe::AstarTotal() {
    for(auto a : m_avions){
        a->getChemin() = Astar(
                selectionnerCasePixel(a->getMPositionX(),a->getMPositionY())->getMId(),
                selectionnerCase(m_avions[0]->getArrivee()->getMXCase(),m_avions[0]->getArrivee()->getMYCase())->getMId());
    }
}

std::vector<Case *> Graphe::Astar(int s0, int sArrivee) {
    std::cout << std::endl << std::endl << "LANCEMENT DE A* :) :" << std::endl;

    // INITIALISATION
    int nbMarques = 0;
    //tous les sommets sont non marqués
    std::vector<int> couleurs(m_cases.size(), 0);
    // tous les sommets sont supposés à une distance infinie de s0;
    std::vector<float> distances(m_cases.size(), std::numeric_limits<float>::max());


    distances[s0] = 0; // s0 est à une distance de 0 de lui même.

    ///définition « à la volée »de la fonction de comparaison cmp
    //Attention, dans l'aide il y a des double, mais dans le Sommet.h ce sont des int
    auto cmp = [](std::pair<const Case *, int> p1, std::pair<const Case *, int> p2) {
        return p2.second < p1.second;
    };
    /// déclaration de la file de priorité
    std::priority_queue<std::pair<const Case *, int>, std::vector<std::pair<const Case *, int>>, decltype(cmp)> file(
            cmp);

    //Insérer le sommet initial dans la file
    file.push({m_cases[s0], 0});
    std::vector<int> predecesseurs(m_cases.size(), -1); // nous ne connaissons pas encore les prédécesseurs
    predecesseurs[s0] = 0; // on pourrait laisser -1, s0 n'a pas vraiment de prédécesseur car il s'agit du sommet initial

    bool verif = false;
    do {
        ///On prend le sommet en tête de file
        std::pair<const Case *, int> p = file.top();
        file.pop();
        //si le sommet a deja ete marque, on l'ignore et on passe au suivant
        while (!file.empty() && couleurs[p.first->getMId()]) {
            p = file.top();
            file.pop();
        }

        //num du sommet
        int s = p.first->getMId();

        if (s == sArrivee) {
            verif = true;
        } else {
            couleurs[s] = 2;
            nbMarques++;

            for (auto successeur: m_cases[s]->getSuccesseurs()) {
                if (couleurs[successeur.first->getMId()] == 0) {
                    distances[successeur.first->getMId()] =
                            distances[s] + heuristique(s, successeur.first);//successeur.second;
                    predecesseurs[successeur.first->getMId()] = s;
                    couleurs[s] = 1;
                    file.push(std::pair<const Case *, int>
                                      (m_cases[successeur.first->getMId()], distances[successeur.first->getMId()]));
                } else {
                    if (couleurs[successeur.first->getMId()] == 1) {
                        if (distances[s] + heuristique(s, successeur.first) < distances[successeur.first->getMId()]) {
                            distances[successeur.first->getMId()] = distances[s] + heuristique(s, successeur.first);
                            predecesseurs[successeur.first->getMId()] = s;
                            file.push(std::pair<const Case *, int>
                                              (m_cases[successeur.first->getMId()],
                                               distances[successeur.first->getMId()]));
                        }
                    }
                    if (couleurs[successeur.first->getMId()] == 2) {
                        if (distances[s] + heuristique(s, successeur.first) < distances[successeur.first->getMId()]) {
                            distances[successeur.first->getMId()] = distances[s] + heuristique(s, successeur.first);
                            file.push(std::pair<const Case *, int>
                                              (m_cases[successeur.first->getMId()],
                                               distances[successeur.first->getMId()]));
                            couleurs[successeur.first->getMId()] = 1;
                        }
                    }
                }
            }
        }
    } while (!verif && nbMarques < m_cases.size());

    std::vector<Case *> tab;
    int t = sArrivee;
    do {
        tab.push_back(m_cases[predecesseurs[t]]);
        t = predecesseurs[t];
    } while (t != s0);
    tab.pop_back();
    std::reverse(tab.begin(), tab.end());
    for (auto s: tab) {
        std::cout << "L'ID EST " << s->getMId() << std::endl;
    }
    return tab;
}
 */


