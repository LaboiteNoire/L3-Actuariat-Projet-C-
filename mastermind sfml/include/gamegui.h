#ifndef GAMEGUI_H
#define GAMEGUI_H
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


class GameGUI {
private:
    vector<sf::Color> my_colors;
    Mastermind jeu;
    map<string, int> capacity;
    sf::RenderWindow window; // création fenêtre
    sf::Font font;
    bool jeudebut;
    int color;
    vector<vector<int>> tentatives;
    vector<pair<int, int>> responses;
    sf::Clock clock;
public:
    GameGUI(Mastermind &jeua);
    void init_colors();
    void init_font();
    void run_my_game();
    void bganimation();
};

#endif // GAMEGUI_H
