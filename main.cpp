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
        if (colonne < 0 || colonne >= LC || couleur < 0 || couleur >= NC) return false; // souci de couleur ou colonne de jeu invalide
        tentatives[compt][colonne] = couleur;
        return true;
    }

    bool tentativeComplete() const {
        for (int i = 0; i < LC; ++i) {
            if (tentatives[compt][i] == -1) return false; // au moins un pion n'a pas été placé
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
};

// Palette de couleurs SFML
const vector<sf::Color> couleurs = {
    sf::Color::Red,
    sf::Color::Blue,
    sf::Color::Green,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Cyan,
    sf::Color(255, 165, 0), // Orange
    sf::Color(128, 0, 128)  // Violet
};

int main() {
    Mastermind jeu;
    const int taillePion = 40; // taille du pion
    const int marge = 10; // marge entre deux pions

    sf::RenderWindow window(sf::VideoMode(500, 700), "Mastermind SFML"); // création fenêtre

    int couleur = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) { // Gérer évènements venant de l'utilisateur
            if (event.type == sf::Event::Closed)
                window.close(); // Cliquer sur la croix -> fermer
            else if (event.type == sf::Event::MouseButtonPressed && !jeu.estFini()) { // clic de souris et jeu non fini
                int x = event.mouseButton.x;
                int y = event.mouseButton.y; // récup des cooroonnées


                if (y > 650) { // clic dans la zone de sélection couleur en bas (par défaut 0,0 dans l'angle en haut à gauche
                    int index = x / (taillePion + marge);
                    if (index >= 0 && index < jeu.NC){
                            couleur = index; // c'est bien une couleur
                    }
                }

                else { // vérifier si le joueur tente de placer dans la grille sa tentative
                    int tour = jeu.getcompt();
                    for (int col = 0; col < jeu.LC; ++col) {
                        int cx = 50 + col * (taillePion + marge);
                        int cy = 50 + tour * (taillePion + marge);
                        sf::FloatRect rect(cx, cy, taillePion, taillePion);
                        if (rect.contains(x, y)) {
                            jeu.setCouleur(col, couleur);
                        }
                    }
                }
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) { // Entrer pour valider une tentative
                if (jeu.tentativeComplete() && !jeu.estFini()) { // si la tentative a été valide et que le jeu n'est pas fini on passe au coup suivant
                    jeu.prochainCoup();
                }
            }
        }

        window.clear(sf::Color(50, 50, 50));// efface écran et met un fond gris / noir

        // Dessiner la grille
        const vector<vector<int>> tentatives = jeu.getTentatives(); // récupérer les combinaisons déjà jouées
        for (int i = 0; i < jeu.NT; ++i) {
            for (int j = 0; j < jeu.LC; ++j) {
                sf::CircleShape pion(taillePion / 2); // créer chaque cercle de la grille (potentiellement vide)
                pion.setPosition(50 + j * (taillePion + marge), 50 + i * (taillePion + marge)); // les positionner
                int coul = tentatives[i][j];
                if (coul >= 0 && coul < couleurs.size()) // il y a vraiment une couleur qui a été jouée ici
                    pion.setFillColor(couleurs[coul]); // on colorie = remplissage du cercle de cette couleur
                else
                    pion.setFillColor(sf::Color(100, 100, 100)); // sinon on n'a pas encore joué on laisse une nuance de gris pour indiquer vide
                window.draw(pion); // Après avoir défini toutes les caractéristiques on le dessine
            }

            // Affichage du résultat de la combinaison jouée
            if (i < jeu.getcompt()) {
                pair<int,int> res = jeu.calculReponse(i);
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
                    window.draw(resultatBC); // on affiche autant de pions blancs que de pions de bonne couleur mais mal placés
                }
            }
        }

        // Affiche la palette de couleurs en bas de la fenêtre
        for (int i = 0; i < jeu.NC; ++i) {
            sf::CircleShape colorPick(taillePion / 2);
            colorPick.setPosition(i * (taillePion + marge), 650);
            colorPick.setFillColor(couleurs[i]); // on affiche toutes les couleurs possibles définies plus haut
            if (i == couleur) // c'est ce pion là qui est sélectionné
                colorPick.setOutlineColor(sf::Color::White), colorPick.setOutlineThickness(3); // ajouter un contour blanc pour dire que c'est sélectionné : effet de surbrillance
            window.draw(colorPick);
        }

        window.display();
    }

    return 0;
}
