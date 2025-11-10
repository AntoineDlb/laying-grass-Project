//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Player.h"
#include "../../include/models/Board.h"
#include <vector>

namespace Models {
    Player::Player(int newId, std::string newName, std::string newColor) {
        id = newId;
        name = newName;
        color = newColor;
        exchange = 1;
        score = 0;
    }


} // Models