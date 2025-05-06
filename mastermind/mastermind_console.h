#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class Mastermind {
protected:
    vector<int> CC;    // combinaison cachée
    vector<int> CJ;    // combinaison jouée
    int compt;
    bool victoire;

public:
    const int NC = 8;  // nombre de couleurs
    const int NT = 12; // nombre d'essais maximal
    const int LC = 4;  // longueur de la combinaison
    Mastermind();
    vector<int> creeCombinaison();
    vector<int> getCombinaisonCachee() const;
    vector<int> getCombinaisonJouee() const;
    void setCombinaisonJouee(const vector<int>& combi);
    pair<int, int> calculReponse() const;
    int getNbCoups() const;
    void incrementeCoup();
    bool estVictoire() const;
    void setVictoire(bool v);
    void afficheDebug() const;

};

ostream& operator<<(ostream& os, const Mastermind& jeu);


