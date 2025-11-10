#include <iostream>
#include "controllers/Game.h"

int main() {
    Controllers::Game game;
    game.start();
    game.run();
    game.end();

    return 0;
}