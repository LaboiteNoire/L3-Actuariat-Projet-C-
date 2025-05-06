#include "mastermind_console.h"


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
        cout << "\nBRAVO ! Vous avez gagne en " << jeu.getNbCoups() << " coups." << endl;
    } else {
        cout << "\nPERDU... la combinaison etait : ";
        for (int val : jeu.getCombinaisonCachee()) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}

