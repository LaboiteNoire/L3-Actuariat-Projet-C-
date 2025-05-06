#ifndef MASTERMIND_H
#define MASTERMIND_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <stack>
#include <random>
#include <algorithm>
using namespace std;


#pragma once


class Mastermind {
private:
    map<string, int> capacity; // propriétés du jeu
    vector<int> real_comb; //combinaison secrete
    vector<int> atm_try; //combinaison en cours
    stack<vector<int>> tentatives;  // ensemble des combinaisons jouées
    bool victory;
    bool end_of_the_game;
    uniform_int_distribution<> distrib;
public:
    Mastermind();
    pair<bool,string> one_try();
    void isVictory_01();
    bool isVictory(); // nous informe sur la victoire ou non de la partie
    bool isEnd(); // renvoie si la partie est finie
    int getcompt() const;
    bool setcolor(int col, int coul);
    pair<int, int> calculReponse();
    map<string, int> getCapacity();
    vector<int> last_tentative();
    vector<int> getRealComp();
    vector<int> getAtmTry();// renvoie l'état du tour actuel

};

#endif // MASTERMIND_H
