#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class Mastermind {
private:
    vector<int> CC;
    vector<vector<int>> tentatives;  // ensemble des combinaisons jouées
    int compt;
    bool victoire;

public:
    const int NC = 8;
    const int NT = 12;
    const int LC = 4;

    Mastermind(){
        srand(time(0));
        compt=0;
        victoire=false;
        CC = creeCombinaison(); // Création de la combinaison cachée
        tentatives.resize(NT, vector<int>(LC, -1)); // -1 pour dire que ce n'est pas encore joué
    }
    vector<int> creeCombinaison() {
        vector<int> Cc(LC);
        for (int i = 0; i < LC; ++i) {
            Cc[i] = rand() % NC;
        }
        return Cc;
    }

    bool setCouleur(int colonne, int couleur) {
        if (colonne < 0 || colonne >= LC || couleur < 0 || couleur >= NC){
            return false; // souci de couleur ou colonne de jeu invalide
        }
        else {
            tentatives[compt][colonne] = couleur;
            return true;
        }
    }

    bool tentativeComplete() const {
        for (int i = 0; i < LC; ++i) {
            if (tentatives[compt][i] == -1) {
                return false; // au moins un pion n'a pas été placé
            }
        }
        return true;
    }

    pair<int, int> calculReponse(int colonne) const {
        vector<int> Cc2 = CC;
        vector<int> Cj2 = tentatives[colonne];

        int nbP = 0;
        for (int i = 0; i < LC; ++i) {
            if (Cj2[i] == Cc2[i]) {
                nbP++;
                Cj2[i] = Cc2[i] = NC; // une fois qu'un pion est comptabilisé on remplace par NC valeur impossible pour ne pas le recompter
            }
        }
        int nbC = 0; // compter les bonnes couleurs mal placés
        for (int i = 0; i < LC; ++i) {
            if (Cj2[i] != NC) {
                for (int j = 0; j < LC; ++j) {
                    if (Cc2[j] == Cj2[i]) {
                        nbC++;
                        Cc2[j] = NC;
                        break;//inutile de poursuivre
                    }
                }
            }
        }
        return make_pair(nbP, nbC);
    }


    void prochainCoup() {
        if (calculReponse(compt).first == LC){
                victoire = true; // il y a eu victoire sur le dernier coup joué
        }
        compt++; // on inclémente le compteur
    }

    bool estVictoire() const {
        return victoire;
    }

    bool estFini() const {
        return compt >= NT || victoire; // un jeu est fini lorsque il y a eu trop d'essais ou une victoire
    }

    int getcompt() const {
        return compt;
    }

    const vector<vector<int>> getTentatives() const {
        return tentatives;
    }

    const vector<int> getCombinaisonCachee() const {
        return CC;
    }

    void reset() {
        compt = 0;
        victoire = false;
        CC = creeCombinaison();
        for (int i = 0; i < NT; ++i) {               // Parcourt chaque ligne du tableau
            for (int j = 0; j < LC; ++j) {        // Parcourt chaque colonne de la ligne
                tentatives[i][j] = -1;
            }
        }
    }

};




int main() {
    // Palette de couleurs SFML
    const std::vector<sf::Color> couleurs = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan,
        sf::Color::Black,
        sf::Color::White
    };
    Mastermind jeu;
    const int taillePion = 40; // taille du pion
    const int marge = 10; // marge entre deux pions

    sf::RenderWindow window(sf::VideoMode(600, 700), "Mastermind SFML"); // création fenêtre

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) { // charge une police
        cerr << "Erreur de chargement de la police\n";
        return 1; // message d'erreur de chargement
    }

    sf::Texture textureHome;
    sf::Texture textureRestart;
    sf::Sprite retour_accueil;
    sf::Sprite recommencer_partie; // sprite : objet qui peut gérer l'affichage de texture i.e. d'images en l'occurence

    if (!textureHome.loadFromFile("fleche_retour_menu.jpg") || !textureRestart.loadFromFile("fleche_recommencer.jpg")) { // chargement des images
        cerr << "Erreur de chargement des images des boutons.\n";
        return 1;
    }
    retour_accueil.setTexture(textureHome);
    recommencer_partie.setTexture(textureRestart); // association texture et sprite
    retour_accueil.setPosition(550, 640);     // en haut à droite
    recommencer_partie.setPosition(550, 10);  // en bas à droite
    retour_accueil.setScale(0.05f, 0.05f);
    recommencer_partie.setScale(0.05f, 0.05f); // redimensionner l'image de base pour que les boutons ne soient pas trop gros





    bool jeudebut = false; // tant que le joueur n'a pas cliqué sur jouer
    int couleur = 0; // couleur sélectionnée par le joueur

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // permet de gérer les évènements ie les clics, actions de l'utilisateur
            if (event.type == sf::Event::Closed){
                window.close(); // croix cliquée = fermer la fenêtre
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                // Clic sur bouton "Maison"
                if (retour_accueil.getGlobalBounds().contains(x, y)) { //getGlobalBounds() retourne un rectangle représentant la zone occupée du bouton
                    jeudebut = false; // on veut revenir à la page d'accueil
                    jeu.reset(); // nouvelle partie
                    continue;
                }

                // Clic sur bouton "Restart" -> nouvelle partie sans revenir à la case accueil
                if (recommencer_partie.getGlobalBounds().contains(x, y)) {
                    jeu.reset();
                    continue;
                }
            }


            if (!jeudebut) { // on se situe en page d'accueil
                if (event.type == sf::Event::MouseButtonPressed) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
                    if (x >= 150 && x <= 350 && y >= 550 && y <= 600) { // c'est le bouton jouer qui a été cliqué
                        jeudebut = true;
                    }
                }
                continue;
            }

            if (event.type == sf::Event::MouseButtonPressed && !jeu.estFini()) { // gestion des clics souris tant que jeu pas fini
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if (y > 650) { // on est certainement dans la palette de couleurs
                    int index = x / (taillePion + marge); // indice de la couleur cliquée
                    if (index >= 0 && index < jeu.NC){
                        couleur = index;
                    }
                } else { // on est certainement en train d'essayer de poser sur la grille
                    int tour = jeu.getcompt();
                    for (int col = 0; col < jeu.LC; ++col) { // pour chaque pion de la ligne en cours de remplissage
                        int cx = 50 + col * (taillePion + marge);
                        int cy = 50 + tour * (taillePion + marge);
                        sf::FloatRect rect(cx, cy, taillePion, taillePion);
                        if (rect.contains(x, y)) { // c'est l'endroit cliqué
                            jeu.setCouleur(col, couleur); // placer la couleur sélectionnée
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                if (jeu.tentativeComplete() && !jeu.estFini()) {
                    jeu.prochainCoup(); // touche entrée permet de valider la tentative de jeu
                }
            }
        }

        window.clear(sf::Color(50, 50, 50)); // effacer fenêtre : fond gris foncé

        if (!jeudebut) {
            // Affichage page d'accueil
            sf::Text titre("Bienvenue dans Mastermind !", font, 30);
            titre.setPosition(50, 50);
            titre.setFillColor(sf::Color::White);

            sf::Text regles(
                "But : Trouver la bonne combinaison de 4 couleurs.\n"
                "Chaque couleur peut apparaître plusieurs fois.\n"
                "Rouge = bien placé, Blanc = bonne couleur mal placée.\n"
                "12 tentatives maximum !\n"
                "Remplir les lignes une par une en commençant par le haut, \n"
                "Cliquer sur entrée une fois la ligne remplie pour valider \n"
                "votre tentative.",
                font, 20
            );
            regles.setPosition(50, 120);
            regles.setFillColor(sf::Color::White); // afficher les règles en blanc

            sf::RectangleShape bouton(sf::Vector2f(200, 50));
            bouton.setPosition(150, 550);
            bouton.setFillColor(sf::Color::Green);

            sf::Text texteBouton("Jouer", font, 24);
            texteBouton.setPosition(215, 560);
            texteBouton.setFillColor(sf::Color::Black); // créer un bouton vert avec écriture noire jouer

            window.draw(titre);
            window.draw(regles);
            window.draw(bouton);
            window.draw(texteBouton);

            window.display(); // affichage de tous les éléments définis
            continue; // on poursuit cette boucle tant que le jeu n'a pas commencé
        }

        // Jeu en cours
        const vector<vector<int>> tentatives = jeu.getTentatives();
        for (int i = 0; i < jeu.NT; ++i) {
            for (int j = 0; j < jeu.LC; ++j) {
                sf::CircleShape pion(taillePion / 2);  // créer chaque cercle de la grille (potentiellement vide)
                pion.setPosition(50 + j * (taillePion + marge), 50 + i * (taillePion + marge)); // les positionner
                unsigned int coul = tentatives[i][j]; // couleur jouée ici
                if (coul >= 0 && coul < couleurs.size()) // il y a vraiment une couleur qui a été jouée ici
                    pion.setFillColor(couleurs[coul]); // on colorie = remplissage du cercle de cette couleur
                else
                    pion.setFillColor(sf::Color(100, 100, 100)); // sinon on n'a pas encore joué on laisse une nuance de gris pour indiquer vide
                window.draw(pion); // Après avoir défini toutes les caractéristiques on le dessine
            }

            if (i < jeu.getcompt()) {
                pair<int, int> res = jeu.calculReponse(i);
                for (int k = 0; k < res.first; ++k) {
                    sf::CircleShape resultatBP(8);
                    resultatBP.setFillColor(sf::Color::Red);
                    resultatBP.setPosition(300 + k * 20, 50 + i * (taillePion + marge));
                    window.draw(resultatBP); // on affiche autant de pions rouges que de pions bien placés
                }
                for (int k = 0; k < res.second; ++k) {
                    sf::CircleShape resultatBC(8);
                    resultatBC.setFillColor(sf::Color::White);
                    resultatBC.setPosition(300 + (res.first + k) * 20, 50 + i * (taillePion + marge));
                    window.draw(resultatBC); // on affiche autant de pions blancs que de bonnes couleurs
                }
            }
        }

        // Afficher la palette
        for (int i = 0; i < jeu.NC; ++i) {
            sf::CircleShape colorPick(taillePion / 2);
            colorPick.setPosition(i * (taillePion + marge), 650);
            colorPick.setFillColor(couleurs[i]); // on affiche toutes les couleurs possibles définies plus haut
            if (i == couleur){
                colorPick.setOutlineColor(sf::Color::White), colorPick.setOutlineThickness(3); // contour blanc du pion = créer un effet de surbrillance pour la couleur sélectionnée
            }
            window.draw(colorPick);

        }

        window.draw(retour_accueil);
        window.draw(recommencer_partie); // affichage des boutons reset du jeu et retour à l'accueil


        if (jeu.estFini()) {
            // Nettoie la fenêtre = affiche un fond gris
            window.clear(sf::Color(30, 30, 30));

            // Affiche message de victoire ou défaite
            sf::Text finText("", font, 32);
            finText.setPosition(50, 100);
            finText.setFillColor(sf::Color::White);

            if (jeu.estVictoire()) {
                finText.setString(" Bravo ! Vous avez gagné !");
            } else {
                finText.setString(" Dommage ! Vous avez perdu !");
            }
            window.draw(finText);

            sf::Text combiText("La combinaison était :", font, 24);
            combiText.setPosition(50, 200);
            combiText.setFillColor(sf::Color::White);
            window.draw(combiText); // affichage de texte

            const vector<int> codeSecret = jeu.getCombinaisonCachee();
            for (unsigned int i = 0; i < codeSecret.size(); ++i) {
                sf::CircleShape pion(taillePion / 2);
                pion.setFillColor(couleurs[codeSecret[i]]);
                pion.setPosition(50 + i * (taillePion + marge), 260);
                pion.setOutlineColor(sf::Color::White);
                pion.setOutlineThickness(2);
                window.draw(pion); // affichage des pions de la bonne combinaison
            }
            window.draw(retour_accueil);
            window.draw(recommencer_partie);

            window.display();
            continue; // ne pas revenir sur l'affichage de palette de couleurs etc mais rester sur cette page de fin de jeu
        }


        window.display();
    }

    return 0;
}

