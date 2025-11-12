#include <iostream>
#include "controllers/Game.h"

int main() {
    Controllers::Game game;
    game.start();
    game.run();
    game.end();
    std::cout << std::endl;
    std::cout << "Appuyez sur Entree pour quitter..." << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}