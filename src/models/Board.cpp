//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Board.h"

namespace Models {
    Board::Board(int playersNumber) {
        this->playersNumber = playersNumber;
        if (playersNumber >= 2 && playersNumber <= 4) {
            this->width = 20;
            this->height = 20;
        } else if (playersNumber >= 5 && playersNumber <= 9) {
            this->width = 30;
            this->height = 30;
        }
        grid.resize(height, std::vector<Cell>(width, Cell()));
    };

    bool const Board::isTouchingOther() {

    }

    void Board::placeBonus() {

    }
    bool const Board::canPlaceTile() {

    }

    void Board::placeTile(Position p) {
    }
} // Models