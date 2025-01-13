#include "menu.h"


///CONSTRUCTEUR-DESTRUCTEUR///

Menu::Menu() {
    m_choix={};
}
Menu::~Menu()=default;


///GETTERS-SETTERS///

int Menu::getMChoix() const {
    return m_choix;
}


///METHODES///

void Menu::lancer(bool &end){
    afficher();
    do {
        std::cout << "Saisissez votre choix : ";
        std::cin >> m_choix;
    }while(m_choix<0 || m_choix>3);
    if(m_choix==3){
        end=true;
    }
}
void Menu::afficher() {
    Table menu_affichage;
    menu_affichage.add_row({"________________________________________"});
    menu_affichage.add_row({"|    __  _                                 |"});
    menu_affichage.add_row({"|    \\ `/ |                                |"});
    menu_affichage.add_row({"|     \\__`!                                |"});
    menu_affichage.add_row({"|     / ,' `-.__________________           |"});
    menu_affichage.add_row({"|    '-'\\_____                LI`-.        |"});
    menu_affichage.add_row({"|       <____()-=O=O=O=O=O=[]====--)       |"});
    menu_affichage.add_row({"|         `.___ ,-----,_______...-'        |"});
    menu_affichage.add_row({"|              /    .'                     |"});
    menu_affichage.add_row({"|             /   .'                       |"});
    menu_affichage.add_row({"|            /  .'                         |"});
    menu_affichage.add_row({"|            `-'                           |"});
    menu_affichage.add_row({"________________________________________"});
    menu_affichage.add_row({" SIMULATEUR DE CONTROLE AERIEN "});
    menu_affichage.add_row({"_____ Veuillez choisir une action _____"});
    menu_affichage.add_row({"                                        "});
    menu_affichage.add_row({"0.Lancer simulation"});
    menu_affichage.add_row({"1.Programmer la simulation"});
    menu_affichage.add_row({"2.Afficher la liste des avions et aeroports"});
    menu_affichage.add_row({"3.Quitter le simulateur "});
    menu_affichage.add_row({"                                        "});
    menu_affichage.add_row({"________________________________________"});

    menu_affichage.format()
            .border(" ")
            .corner(" ")
            .border_left("||")
            .border_right("||")
            .border_color(Color::red)
            .font_color(Color::blue)
            .font_align(FontAlign::center);
    menu_affichage[0][0].format()
            .padding_top(0)
            .padding_bottom(0)
            .font_style({FontStyle::bold});
    menu_affichage[13][0].format()
            .padding_top(1)
            .padding_bottom(1)
            .font_color(Color::white);

    for(int i=1;i<12;i++){
        menu_affichage[i][0].format()
                .font_align(FontAlign::left)
                .font_color(Color::white);
    }
    for(int i=0;i<21;i++) {
        menu_affichage[i][0].format().hide_border_bottom();
    }
    for(int i=1;i<22;i++) {
        menu_affichage[i][0].format().hide_border_top();
    }
    std::cout<<menu_affichage<<std::endl;
}
void Menu::afficherListes(){

    ///LECTURE AEROPORTS///

    std::string filename_Aeroport = "../aeroport.txt";
    std::ifstream ifs {filename_Aeroport};
    if (!ifs) {throw std::runtime_error("Impossible d'ouvrir " + filename_Aeroport);}

    int nbAeroports = 0;
    ifs >> nbAeroports;
    if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de l'ordre du graphe.");}

    for (int i = 0; i < nbAeroports; ++i) {
        char retourAlaligne;
        ifs>>retourAlaligne;
        std::string mNom;
        std::string Nom;
        std::getline(ifs,Nom);
        mNom=retourAlaligne+Nom;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mNom de l'aeroport.");}
        int mNbPistes = 0;
        ifs >> mNbPistes;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mNbPistes de l'aeroport.");}
        int mNbPlaces = 0;
        ifs >> mNbPlaces;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mNbPlaces de l'aeroport.");}
        float mChargement = 0;
        ifs >> mChargement;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mChargement de l'aeroport.");}
        float mDechargement = 0;
        ifs >> mDechargement;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mDechargement de l'aeroport.");}
        float mAccesPistes = 0;
        ifs >> mAccesPistes;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mAccesPistes de l'aeroport.");}
        float mAnticollision = 0;
        ifs >> mAnticollision;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de nbAeroports de l'aeroport.");}
        float mTdecollage = 0;
        ifs >> mTdecollage;
        if (ifs.fail()) {throw std::runtime_error("Problème de lecture de mTdecollage de l'aeroport.");}
        float mTatterissage = 0;
        ifs >> mTatterissage;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mTatterissage de l'aeroport.");}
        float mBoucleAttente = 0;
        ifs >> mBoucleAttente;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mBoucleAttente de l'aeroport.");}
        float mX = 0;
        ifs >> mX;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mX de l'aeroport.");}
        float mY = 0;
        ifs >> mY;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de mY de l'aeroport.");}
        int xCase,yCase;
        ifs >> xCase;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de xCase de l'aeroport.");}
        ifs >> yCase;
        if (ifs.fail()) {throw std::runtime_error("Probleme de lecture de yCase de l'aeroport.");}
        aeroports.push_back(new Aeroport((int) i,mNbPistes,  mNbPlaces, mNom,mChargement,mDechargement,
                                           mAccesPistes, mAnticollision, mTdecollage,mTatterissage,mBoucleAttente,mX,mY,xCase,yCase));
    }
    ifs.close();

    ///AFFICHAGE AEROPORTS///

    Table listeAeroports;
    std::cout<<std::endl
             <<"LISTE DES AEROPORTS :"<<std::endl;
    listeAeroports.add_row(
            {"Nom", "Coordonnees", "Nombre de Pistes"});
    for (auto &i:aeroports) {
        std::string position = std::to_string(i->getMXCase())+", "+ std::to_string(i->getMYCase());
        std::string nbPistes = {std::to_string(i->getMNbPistes())};
        listeAeroports.add_row({i->getMNom(), position, nbPistes});
    }
    listeAeroports.format().font_align(FontAlign::center);
    listeAeroports[0][0].format().font_color(Color::blue);
    listeAeroports[0][1].format().font_color(Color::yellow);
    listeAeroports[0][2].format().font_color(Color::green);
    std::cout<<listeAeroports<<std::endl;

    ///LECTURE AVIONS///

    std::string filename_Avion = "../avion.txt";
    std::ifstream ifsAvion{filename_Avion}; // lecture du fichier avion
    if (!ifsAvion) {throw std::runtime_error("Impossible d'ouvrir " + filename_Avion);}

    int nbAvions = 0;
    ifsAvion >> nbAvions;
    if (ifsAvion.fail()) {throw std::runtime_error("Probleme de lecture du nbr d'avions.");}

    float avionCapacite = 0, avionConsommation= 0;
    std::string avionType;
    float avionVitesse = 0,avionAltitude = 0;

    for (int i = 0; i < nbAvions; ++i) {
        ifsAvion >> avionCapacite>>avionConsommation>>avionType>>avionVitesse>>avionAltitude;
        if (ifsAvion.fail()) {throw std::runtime_error("Probleme de lecture des parametres de l'avions.");}

        avions.push_back(new Avion(avionConsommation,avionVitesse,avionAltitude,avionType,avionCapacite)); //permet de créer directement des avions
    }
    ifsAvion.close();

    /// AFFICHAGE AVIONS ///

    Table listeAvions;
    std::cout<<std::endl
             <<"LISTE DES AVIONS :"<<std::endl;
    listeAvions.add_row(
            {"ID", "Type", "Capacite"});
    for (size_t i = 0; i < avions.size(); i++) {
        std::string capacite = std::to_string(avions[i]->getMCapacite());
        listeAvions.add_row({std::to_string(i),avions[i]->getMType(), capacite});
    }
    for(size_t i=1;i<avions.size()+1;i++){
        if(avions[i-1]->getMType()=="court") {
            listeAvions[i][1].format().font_color(Color::green);
        }
        if(avions[i-1]->getMType()=="moyen") {
            listeAvions[i][1].format().font_color(Color::yellow);
        }
        if(avions[i-1]->getMType()=="long") {
            listeAvions[i][1].format().font_color(Color::red);
        }
    }
    listeAvions.format().font_align(FontAlign::center);
    std::cout<<listeAvions<<std::endl;
}
void Menu::parametrerSimulation(int choixAvion, std::string choixDepart, std::string choixArrivee) {

    ///PROGRAMMER UN VOL///

    std::cout<<"Programmez un vol : "<<std::endl;
    do{
        std::cout<<"Choisissez un avion grace a son ID"<<std::endl;
        std::cin>>choixAvion;
    }while(choixAvion>avions.size() && choixAvion<0);
    do{
        std::cout<<"Choisissez un aeroport de depart"<<std::endl;
        std::cin>>choixDepart;
    }while(!verif(choixDepart));
    for(auto a:aeroports){
        if(a->getMNom()==choixDepart){
            std::cout<<"Depart : "<<choixDepart<<std::endl;
        }
    }
    do{
        std::cout<<"Choisissez un aeroport d'arrivee"<<std::endl;
        std::cin>>choixArrivee;
    }while(!verif(choixArrivee));
    for(auto a:aeroports){
        if(a->getMNom()==choixArrivee){
            std::cout<<"Arrivee : "<<choixArrivee<<std::endl;
        }
    }
    std::cout << "Lancez la simulation pouyr visualiser votre vol"<<std::endl;
}
bool Menu::verif(std::string choix){
    bool retour=false;
    for(auto a:aeroports){
        if(a->getMNom()==choix){
            retour = true;
        }
    }
    return retour;
}

