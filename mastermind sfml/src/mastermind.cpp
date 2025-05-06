using namespace std;
#include "mastermind.h"


Mastermind::Mastermind(){
    srand(time(0));
    capacity = {{"Nb coul", 8},{"nb tenta",12},{"nb col",4}}; // propriétés du jeu
    real_comb.resize(capacity["nb col"],(-1)); //-1 pour dire que ce n'est pas encore joué
    atm_try.resize(capacity["nb col"], -1); //-1 pour dire que ce n'est pas encore joué
    victory=false;
    end_of_the_game=false;
    // Création de la combinaison cachée
    for (int i=0;i<capacity["nb col"];i++){
        real_comb[i] = rand() % 8;;
    }
}
pair<bool,string> Mastermind::one_try(){
    // permet de faire un éssais
    pair<bool,string> result;
    auto it = find(atm_try.begin(), atm_try.end(), -1);
    if (!(it == atm_try.end())){
        result = {false, "il manque des couleurs"};
    }
    else{
        tentatives.push(atm_try); // notre tentative est envoyée dans la pile des tentatives
        result = {true, ""};
        // on réinitialise le vecteur de combinaisons en cours
        for (int i=0;i<capacity["nb col"];i++){
            atm_try[i] = -1;
        }
    }
    isVictory_01();
    return result;
}
void Mastermind::isVictory_01(){
    if (tentatives.top() == real_comb){
        victory = true;
        end_of_the_game = true;
    }
    else if (tentatives.size() == 12){
        end_of_the_game = true;
    }
}
bool Mastermind::isVictory(){ // nous informe sur la victoire ou non de la partie
    return victory;
}
bool Mastermind::isEnd(){ // renvoie si la partie est finie
    return end_of_the_game;
}
int Mastermind::getcompt() const { //rdonne le tour du jeu
    return tentatives.size();
}
bool Mastermind::setcolor(int col, int coul){
    if (col < 0 || col >= 4 || coul < 0 || coul >= 8){
        return false; // souci de couleur ou colonne de jeu invalide
    }
    else{
        atm_try[col] = coul;
        return true;
    }
}
pair<int, int> Mastermind::calculReponse(){
    vector<int> compo = tentatives.top();
    int mal_placee = 0;
    int bonne_couleur = 0;
    vector<int> pc; //indice des pionts comptabilisés pour ne pas les recomptés en j
    vector<int> pci; //indice des pionts comptabilisés pour ne pas les recomptés en i
    for (int i=0; i<real_comb.size();i++){
        for (int j=0; j<compo.size();j++){
            if ((real_comb[i]==compo[j]) && (i==j) && (find(pc.begin(), pc.end(), j) == pc.end()) && (find(pci.begin(), pci.end(), i) == pci.end())){ // comptabilisation des bonnes couleurs
                bonne_couleur++;
                pc.push_back(j); // on enregistre l'indice pour ne pas a avoir a le recompté
                pci.push_back(i);
            }
            else if ((real_comb[i]==compo[j]) && (find(pc.begin(), pc.end(), j) == pc.end()) && (find(pci.begin(), pci.end(), i) == pci.end())){ // comptabilisation des couleurs dont la position est mauvaise
                mal_placee++;
                pc.push_back(j); // on enregistre l'indice pour ne pas a avoir a le recompté
                pci.push_back(i);
            }
        }
    }
    return make_pair(bonne_couleur, mal_placee);
}
map<string, int> Mastermind::getCapacity(){
    return capacity;
}
vector<int> Mastermind::last_tentative(){
    return tentatives.top();
}
vector<int> Mastermind::getRealComp(){
    return real_comb;
}
vector<int> Mastermind::getAtmTry(){ // renvoie l'état du tour actuel
    return atm_try;
}
