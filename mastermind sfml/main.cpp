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
random_device rd;
mt19937 gen(rd());


#include "mastermind.h"
#include "gamegui.h"


int main() {
    Mastermind jeu;
    GameGUI my_game(jeu);
    my_game.run_my_game();
    return 0;
}

