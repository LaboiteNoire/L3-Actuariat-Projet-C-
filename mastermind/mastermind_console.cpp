#include "mastermind_console.h"

Mastermind::Mastermind() {
    srand(time(0));
    compt=0;
    victoire=false;
    CC = creeCombinaison();  // Création de la combinaison cachée
    CJ = vector<int>(LC, NC); // Init combinaison jouée avec combinaison invalide
}

vector<int> Mastermind::creeCombinaison() {
    vector<int> Cc(LC);
    for (int i = 0; i < LC; ++i) {
        Cc[i] = rand() % NC;
    }
    return Cc;
}

vector<int> Mastermind::getCombinaisonCachee() const {
    return CC;
}

vector<int> Mastermind::getCombinaisonJouee() const {
    return CJ;
}

void Mastermind::setCombinaisonJouee(const vector<int>& combi) {
    assert(combi.size() == LC);
    CJ = combi;
}

// Compare les combinaisons et retourne bien placés et bonnes couleurs
pair<int, int>  Mastermind::calculReponse() const{
    assert(CC.size() == CJ.size());
    int N = CC.size();
    vector<int> Cc2 = CC;
    vector<int> Cj2 = CJ; //travail sur une copie

    int nbP = 0; // compter les bien placés
    for (int i = 0; i < N; ++i) {
        if (Cc2[i] == Cj2[i]) {
            nbP++;
            Cc2[i] = NC;
            Cj2[i] = NC; // une fois qu'un pion est comptabilisé on remplace par NC valeur impossible pour ne pas le recompter
        }
    }

    int nbC = 0; // compter les bonnes couleurs mal placés
    for (int i = 0; i < N; ++i) {
        if (Cj2[i] != NC) {
            for (int j = 0; j < N; ++j) {
                if (Cc2[j] == Cj2[i]) {
                    nbC++;
                    Cc2[j] = NC;
                    Cj2[i] = NC;
                    break; //inutile de poursuivre
                }
            }
        }
    }

    return make_pair(nbP, nbC);
}

int Mastermind::getNbCoups() const {
    return compt;
}
void Mastermind::incrementeCoup() {
    compt++;
}
bool Mastermind::estVictoire() const {
    return victoire;
}
void Mastermind::setVictoire(bool v) {
    victoire = v;
}

// afficher la combinaison cachée : pour le debogage
void Mastermind::afficheDebug() const {
    cout << "DEBUG - Combinaison cachee : ";
    for (int i=0;i<LC;i++) {
    cout << CC[i] << " ";
    }

cout << endl;
}

ostream& operator<<(ostream& os, const Mastermind& jeu) {
    os << "Combinaison jouee  : ";
    vector<int> cj = jeu.getCombinaisonJouee();
    for (int i=0;i<jeu.LC;i++) {
        os << cj[i] << " ";
    }
    os << "\n";

    pair<int,int> res = jeu.calculReponse();  // car non-const
    os << res.first << " bien place(s), " << res.second << " bonne(s) couleur(s).\n";

    return os;
}
