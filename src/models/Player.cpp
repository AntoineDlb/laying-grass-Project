//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Player.h"
#include "../../include/models/Board.h"
#include <vector>

namespace Models {
    Player::Player(int newId, std::string name, std::string color) {
        id = newId;
    }

    int Player::calculateScore() {
        return score;
    }

    int Player::calculateCellsPlaced() {

        return 0;
    }

} // Models