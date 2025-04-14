#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;

class Mastermind {
private:
    vector<int> CC;    // combinaison cachée
    vector<int> CJ;    // combinaison jouée
    int compt;
    bool victoire;

public:
    const int NC = 8;  // nombre de couleurs
    const int NT = 12; // nombre d'essais maximal
    const int LC = 4;  // longueur de la combinaison

    Mastermind() : compt(0), victoire(false) {
        srand(time(0));
        CC = creeCombinaison();  // Création de la combinaison cachée
        CJ = vector<int>(LC, NC); // Init combinaison jouée avec combinaison invalide
    }

    vector<int> creeCombinaison() {
        vector<int> Cc(LC);
        for (int i = 0; i < LC; ++i) {
            Cc[i] = rand() % NC;
        }
        return Cc;
    }

    vector<int> getCombinaisonCachee() const {
        return CC;
    }

    vector<int> getCombinaisonJouee() const {
        return CJ;
    }

    void setCombinaisonJouee(const vector<int>& combi) {
        assert(combi.size() == LC);
        CJ = combi;
    }

// Compare les combinaisons et retourne bien placés et bonnes couleurs
    pair<int, int> calculReponse() const{
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

    int getNbCoups() const {
        return compt;
    }
    void incrementeCoup() {
        compt++;
    }
    bool estVictoire() const {
        return victoire;
    }
    void setVictoire(bool v) {
        victoire = v;
    }

    // afficher la combinaison cachée : pour le debogage
    void afficheDebug() const {
        cout << "DEBUG - Combinaison cachée : ";
        for (int i=0;i<LC;i++) {
        cout << CC[i] << " ";
        }

    cout << endl;
    }
};

ostream& operator<<(ostream& os, const Mastermind& jeu) {
    os << "Combinaison jouée  : ";
    vector<int> cj = jeu.getCombinaisonJouee();
    for (int i=0;i<jeu.LC;i++) {
        os << cj[i] << " ";
    }
    os << "\n";

    pair<int,int> res = jeu.calculReponse();  // car non-const
    os << res.first << " bien placé(s), " << res.second << " bonne(s) couleur(s).\n";

    return os;
}



int main() {
    Mastermind jeu;

    // Affichage debug de la combinaison cachée
    jeu.afficheDebug();

    while (jeu.getNbCoups() < jeu.NT && !jeu.estVictoire()) {
        jeu.incrementeCoup();

        vector<int> tentative(jeu.LC);
        cout << "\nTentative " << jeu.getNbCoups() << " : Entrez " << jeu.LC << " valeurs entre 0 et " << jeu.NC - 1 << " :\n";

        for (int i = 0; i < jeu.LC; ++i) {
            int x;
            cin >> x;
            assert(x >= 0 && x < jeu.NC);
            tentative[i] = x;
        }

        jeu.setCombinaisonJouee(tentative);

        // Affichage de la tentative et du résultat
        cout << jeu;

        if (jeu.calculReponse().first == jeu.LC) {
            jeu.setVictoire(true);
        }
    }

    if (jeu.estVictoire()) {
        cout << "\nBRAVO ! Vous avez gagné en " << jeu.getNbCoups() << " coups." << endl;
    } else {
        cout << "\nPERDU... la combinaison était : ";
        for (int val : jeu.getCombinaisonCachee()) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
