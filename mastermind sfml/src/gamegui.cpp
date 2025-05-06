using namespace std;
#include "mastermind.h"
#include "gamegui.h"


GameGUI::GameGUI(Mastermind &jeua){
    jeudebut = false;
    color = 0;
    capacity["taillePion"] = 40;
    capacity["marge"] = 10;
    jeu = jeua;
    init_colors();
    init_font();
}
void GameGUI::init_colors(){
    my_colors.push_back(sf::Color::Red);
    my_colors.push_back(sf::Color::Green);
    my_colors.push_back(sf::Color::Blue);
    my_colors.push_back(sf::Color::Yellow);
    my_colors.push_back(sf::Color::Magenta);
    my_colors.push_back(sf::Color::Cyan);
    my_colors.push_back(sf::Color::Black);
    my_colors.push_back(sf::Color::White);
}
void GameGUI::init_font(){
    font.loadFromFile("rsc/pixela.ttf");
}
void GameGUI::run_my_game(){
    //Chargement des ressources
    sf::Texture text1;
    sf::Texture text2;
    sf::Texture text3;
    sf::Texture text4;
    sf::Texture text5;
    sf::Texture text6;
    sf::Texture text7;
    //pallete de couleures
    sf::Texture tpal1;
    sf::Texture tpal2;
    sf::Texture tpal3;
    sf::Texture tpal4;
    sf::Texture tpal5;
    sf::Texture tpal6;
    sf::Texture tpal7;
    sf::Texture tpal8;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;
    sf::Sprite sprite6;
    sf::Sprite sprite7;
    //sf::SoundBuffer buffer_01;
    //sf::SoundBuffer buffer_02;
    //sf::SoundBuffer buffer_03;
    //sf::Sound sound1;
    //sf::Sound sound2;
    //sf::Sound sound3;
    text1.loadFromFile("rsc/home logo.png");
    text2.loadFromFile("rsc/loop logo.png");
    text3.loadFromFile("rsc/background.png");
    text4.loadFromFile("rsc/empty.png");
    text5.loadFromFile("rsc/cadre.png");
    text6.loadFromFile("rsc/selected.png");
    text7.loadFromFile("rsc/cadre2.png");
    tpal1.loadFromFile("rsc/Pallette rouge.png");
    tpal2.loadFromFile("rsc/Pallette verte.png");
    tpal3.loadFromFile("rsc/Pallette bleue.png");
    tpal4.loadFromFile("rsc/Pallette jaune.png");
    tpal5.loadFromFile("rsc/Pallette rose.png");
    tpal6.loadFromFile("rsc/Pallette cyan.png");
    tpal7.loadFromFile("rsc/Pallette noire.png");
    tpal8.loadFromFile("rsc/Pallette blanche.png");
    sprite1.setTexture(text1);
    sprite2.setTexture(text2);
    sprite3.setTexture(text3);
    sprite4.setTexture(text4);
    sprite5.setTexture(text5);
    sprite6.setTexture(text6);
    sprite7.setTexture(text7);
    //buffer_01.loadFromFile("rsc/sound1.wav");
    //buffer_02.loadFromFile("rsc/sound1.wav");
    //buffer_03.loadFromFile("rsc/sound1.wav");
    //sound1.setBuffer(buffer_01);
    //sound2.setBuffer(buffer_02);
    //sound3.setBuffer(buffer_03);
    sprite1.setPosition(550, 640);     // en haut à droite
    sprite1.setScale(0.05f, 0.05f);
    sprite2.setPosition(550, 10);  // en bas à droite
    sprite2.setScale(0.05f, 0.05f); // redimensionner l'image de base pour que les boutons ne soient pas trop gros
    // création de la fenetre
    window.create(sf::VideoMode(600, 700), "Mastermind SFML");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                // Clic sur bouton "Maison"
                if (sprite1.getGlobalBounds().contains(x, y)) { //getGlobalBounds() retourne un rectangle représentant la zone occupée du bouton
                    //sound1.play();
                    jeudebut = false; // on veut revenir à la page d'accueil
                    jeu = Mastermind(); // nouvelle partie
                    tentatives = vector<vector<int>> {};
                    responses = vector<pair<int, int>> {};
                }

                // Clic sur bouton "Restart" -> nouvelle partie sans revenir à la case accueil
                if (sprite2.getGlobalBounds().contains(x, y)) {
                    //sound1.play();
                    jeu = Mastermind();
                    tentatives = vector<vector<int>> {};
                    responses = vector<pair<int, int>> {};
                    jeudebut = false;
                    jeudebut = true;
                }
                // on se situe en page d'accueil
                if (!jeudebut){
                    if (x >= 150 && x <= 350 && y >= 550 && y <= 600) { // c'est le bouton jouer qui a été cliqué
                        //sound1.play();
                        jeudebut = true;
                        //sound3.play();
                    }
                }
                // gestion des clics souris tant que jeu pas fini
                if (!jeu.isEnd()){
                    // on est certainement dans la palette de couleurs
                    int tour = jeu.getcompt();
                    if (y > 650) {
                        int index = x / (capacity["taillePion"] + capacity["marge"]); // indice de la couleur cliquée
                        if (index >= 0 && index < jeu.getCapacity()["Nb coul"]){
                            //sound2.play();
                            color = index;
                        }
                    }
                    // on est certainement en train d'essayer de poser sur la grille
                    else if (((50 + tour * (capacity["taillePion"] + capacity["marge"])) <= y) && ((50 + (tour+1) * (capacity["taillePion"] + capacity["marge"])) >= y)){
                        // pour chaque pion de la ligne en cours de remplissage
                        for (int coll = 0; coll < 4; coll++){
                            if (((50 + coll * (capacity["taillePion"] + capacity["marge"])) <= x) && ((50 + (coll+1) * (capacity["taillePion"] + capacity["marge"])) >= x)){ // c'est l'endroit cliqué
                                //sound2.play();
                                if (jeu.setcolor(coll, color)){// placer la couleur sélectionnée
                                }
                                else{
                                }
                            }
                        }

                    }

                }
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter) && (jeudebut) && !(jeu.isEnd())){ //passer au prochain tour
                pair<bool,string> result;
                result = jeu.one_try();
                if (result.first){
                    tentatives.push_back(jeu.last_tentative());
                    responses.push_back(jeu.calculReponse());
                }
                continue;
            }

        }
        //menu
        if (!jeudebut) {
            sf::Text titre("Bienvenue dans Mastermind !", font, 30);
            titre.setPosition(90, 50);
            titre.setFillColor(sf::Color(81, 60, 63));
            sf::Text regles(
                "But : Trouver la bonne combinaison de 4 couleurs.\n"
                "Chaque couleur peut apparaitre plusieurs fois.\n"
                "Rouge = bien place, Blanc = bonne couleur mal placee.\n"
                "12 tentatives maximum !\n"
                "Remplir les lignes une par une en commencant par le haut, \n"
                "Cliquer sur entree une fois la ligne remplie pour valider \n"
                "votre tentative.",
                font, 15
            );
            regles.setPosition(50, 120);
            regles.setFillColor(sf::Color(231, 239, 241)); // afficher les règles en blanc
            sf::RectangleShape bouton(sf::Vector2f(200, 50));
            bouton.setPosition(200, 550);
            bouton.setFillColor(sf::Color(81, 60, 63));
            sf::Text texteBouton("Jouer", font, 24);
            texteBouton.setPosition(260, 560);
            texteBouton.setFillColor(sf::Color::Black); // créer un bouton vert avec écriture noire jouer
            window.clear();
            bganimation();
            window.draw(sprite5);
            window.draw(titre);
            window.draw(regles);
            window.draw(bouton);
            window.draw(texteBouton);
            window.display();
            continue; // on poursuit cette boucle tant que le jeu n'a pas commencé
        }
        // Jeu en cours
        else if (jeudebut && !(jeu.isEnd())){
            window.clear();
            //window.draw(sprite3);
            bganimation();
            window.draw(sprite1);
            window.draw(sprite2); // affichage des boutons reset du jeu et retour à l'accueil
            // dessin des slots du jeu vides
            for (int i = 0; i < jeu.getCapacity()["nb tenta"]; ++i){
                for (int j = 0; j < jeu.getCapacity()["nb col"]; ++j){
                    sf::Sprite emptyboxsprite;
                    emptyboxsprite.setTexture(text4); //boite vide
                    emptyboxsprite.setPosition(50 + j * (capacity["taillePion"] + capacity["marge"]), 50 + i * (capacity["taillePion"] + capacity["marge"]));
                    window.draw(emptyboxsprite);
                }
            }
            // dessin des choix des tours precedents
            for (int l=0; l<tentatives.size();l++){
                pair<int, int> res = responses[l];
                for (int k=0; k< 4; k++){
                    sf::Sprite emplacement_box;
                    if (tentatives[l][k]==0){
                        emplacement_box.setTexture(tpal1);
                    }
                    else if (tentatives[l][k]==1){
                        emplacement_box.setTexture(tpal2);
                    }
                    else if (tentatives[l][k]==2){
                        emplacement_box.setTexture(tpal3);
                    }
                    else if (tentatives[l][k]==3){
                        emplacement_box.setTexture(tpal4);
                    }
                    else if (tentatives[l][k]==4){
                        emplacement_box.setTexture(tpal5);
                    }
                    else if (tentatives[l][k]==5){
                        emplacement_box.setTexture(tpal6);
                    }
                    else if (tentatives[l][k]==6){
                        emplacement_box.setTexture(tpal7);
                    }
                    else if (tentatives[l][k]==7){
                        emplacement_box.setTexture(tpal8);
                    }
                    emplacement_box.setPosition(50 + k * (capacity["taillePion"] + capacity["marge"]), 50 + l * (capacity["taillePion"] + capacity["marge"]));
                    window.draw(emplacement_box);
                }
                for (int b = 0; b < res.first; ++b) {
                    sf::Sprite resultatBP; // pions rouges, pour les bonnes couleurs
                    resultatBP.setTexture(tpal1);
                    resultatBP.setPosition(300 + b * (capacity["taillePion"] + capacity["marge"]), 50 + l * (capacity["taillePion"] + capacity["marge"]));
                    window.draw(resultatBP); // on affiche autant de pions rouges que de pions bien placés
                }
                for (int g = 0; g < res.second; ++g) {
                    sf::Sprite resultatBC; // pions blancs, pour les couleurs dont la position est mauvaise
                    resultatBC.setTexture(tpal8);
                    resultatBC.setPosition(300 + (res.first + g) * (capacity["taillePion"] + capacity["marge"]), 50 + l * (capacity["taillePion"] + capacity["marge"])); // res.first pour dessiner correctement les pions avec leurs marge
                    window.draw(resultatBC); // on affiche autant de pions blancs que de bonnes couleurs
                }
            }
            //dessin des choix actuels
            vector<int> atm;
            atm = jeu.getAtmTry();
            for (int h=0; h<atm.size();h++){
                sf::Sprite vemplacement_box;
                if (atm[h]==0){
                    vemplacement_box.setTexture(tpal1);
                }
                else if (atm[h]==1){
                    vemplacement_box.setTexture(tpal2);
                }
                else if (atm[h]==2){
                    vemplacement_box.setTexture(tpal3);
                }
                else if (atm[h]==3){
                    vemplacement_box.setTexture(tpal4);
                }
                else if (atm[h]==4){
                    vemplacement_box.setTexture(tpal5);
                }
                else if (atm[h]==5){
                    vemplacement_box.setTexture(tpal6);
                }
                else if (atm[h]==6){
                    vemplacement_box.setTexture(tpal7);
                }
                else if (atm[h]==7){
                    vemplacement_box.setTexture(tpal8);
                }
                else{
                    vemplacement_box.setTexture(text4);
                }
                vemplacement_box.setPosition(50 + h * (capacity["taillePion"] + capacity["marge"]), 50 + jeu.getcompt() * (capacity["taillePion"] + capacity["marge"]));
                window.draw(vemplacement_box);
            }
            // dessin de la palette
            sf::Sprite spal1;
            sf::Sprite spal2;
            sf::Sprite spal3;
            sf::Sprite spal4;
            sf::Sprite spal5;
            sf::Sprite spal6;
            sf::Sprite spal7;
            sf::Sprite spal8;
            spal1.setTexture(tpal1);
            spal2.setTexture(tpal2);
            spal3.setTexture(tpal3);
            spal4.setTexture(tpal4);
            spal5.setTexture(tpal5);
            spal6.setTexture(tpal6);
            spal7.setTexture(tpal7);
            spal8.setTexture(tpal8);
            spal1.setPosition(0 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal2.setPosition(1 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal3.setPosition(2 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal4.setPosition(3 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal5.setPosition(4 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal6.setPosition(5 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal7.setPosition(6 * (capacity["taillePion"] + capacity["marge"]), 650);
            spal8.setPosition(7 * (capacity["taillePion"] + capacity["marge"]), 650);
            sprite6.setPosition(color * (capacity["taillePion"] + capacity["marge"]) - 2, 648);
            window.draw(sprite6);
            window.draw(spal1);
            window.draw(spal2);
            window.draw(spal3);
            window.draw(spal4);
            window.draw(spal5);
            window.draw(spal6);
            window.draw(spal7);
            window.draw(spal8);
            window.display();
            continue;
        }
        else if (jeu.isEnd()){
            window.clear();
            sf::Text finText("", font, 32);
            finText.setPosition(50, 100);
            finText.setFillColor(sf::Color::Black);
            if (jeu.isVictory()) {
                finText.setString(" Bravo ! Vous avez gagne !");
            }
            else {
                finText.setString(" Dommage ! Vous avez perdu !");
            }
            bganimation();
            window.draw(sprite7);
            window.draw(finText);
            sf::Text combiText("La combinaison etait :", font, 24);
            combiText.setPosition(50, 200);
            combiText.setFillColor(sf::Color(231, 239, 241));
            window.draw(combiText); // affichage de texte
            const vector<int> codeSecret = jeu.getRealComp();
            for (int h=0; h<codeSecret.size();h++){
                sf::Sprite vemplacement_box;
                if (codeSecret[h]==0){
                    vemplacement_box.setTexture(tpal1);
                }
                else if (codeSecret[h]==1){
                    vemplacement_box.setTexture(tpal2);
                }
                else if (codeSecret[h]==2){
                    vemplacement_box.setTexture(tpal3);
                }
                else if (codeSecret[h]==3){
                    vemplacement_box.setTexture(tpal4);
                }
                else if (codeSecret[h]==4){
                    vemplacement_box.setTexture(tpal5);
                }
                else if (codeSecret[h]==5){
                    vemplacement_box.setTexture(tpal6);
                }
                else if (codeSecret[h]==6){
                    vemplacement_box.setTexture(tpal7);
                }
                else if (codeSecret[h]==7){
                    vemplacement_box.setTexture(tpal8);
                }
                else{
                    vemplacement_box.setTexture(text4);
                }
                vemplacement_box.setPosition(50 + h * (capacity["taillePion"] + capacity["marge"]), 250);
                window.draw(vemplacement_box);
            }
            window.draw(sprite1);
            window.draw(sprite2); // affichage des boutons reset du jeu et retour à l'accueil
            window.display();
            continue;
        }
    }
}
void GameGUI::bganimation(){
    sf::Texture bgtexture;
    sf::Sprite bgsprite;
    // temps actuel
    time_t currentTime = time(nullptr);
    tm* localTime = localtime(&currentTime);
    int seconds = localTime->tm_sec;
    // deuxieme chiffre de la seconde actuelle
    int va = seconds % 10;
    // position de l'animation(1 image par secondes) en fonction de la valeur de va
    if (va==0){
        bgtexture.loadFromFile("rsc/anim/sp0.png");
    }
    else if (va==1){
        bgtexture.loadFromFile("rsc/anim/sp1.png");
    }
    else if (va==2){
        bgtexture.loadFromFile("rsc/anim/sp2.png");
    }
    else if (va==3){
        bgtexture.loadFromFile("rsc/anim/sp3.png");
    }
    else if (va==4){
        bgtexture.loadFromFile("rsc/anim/sp4.png");
    }
    else if (va==5){
        bgtexture.loadFromFile("rsc/anim/sp5.png");
    }
    else if (va==6){
        bgtexture.loadFromFile("rsc/anim/sp6.png");
    }
    else if (va==7){
        bgtexture.loadFromFile("rsc/anim/sp7.png");
    }
    else if (va==8){
        bgtexture.loadFromFile("rsc/anim/sp8.png");
    }
    else{
        bgtexture.loadFromFile("rsc/anim/sp9.png");
    }
    bgsprite.setTexture(bgtexture);
    window.draw(bgsprite);
}
