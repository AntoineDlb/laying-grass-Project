//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_GAME_H
#define LAYING_GRASS_PROJECT_GAME_H

#include <vector>
#include <string>
#include "../models/Player.h"

namespace Controllers {
    class Game {
    public:
        Game() = default;
        void initGame();

    private:
        std::vector<Models::Player> players;
    };
} // Controllers

#endif //LAYING_GRASS_PROJECT_GAME_H