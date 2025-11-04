//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_BOARD_H
#define LAYING_GRASS_PROJECT_BOARD_H
#include <vector>
#include "Cell.h"
#include "Position.h"

namespace Models {
    class Board {
    private:
        std::vector<std::vector<Cell>> grid;
        std::vector<Position> position;
        int width;
        int height;


    public:
        Board();

        int  const getWidth(){ return width; }
        void setWidth(int w){ width = w; }

        int const getHeight(){ return height; }
        void setHeight(int h){ height = h; }

        bool const isTouchingOther();
        void placeBonus();

        bool const canPlaceTile();
        void placeTile();

        void placeBonusSquares();
        void placeBonusSquare(Position p);

    };
} // Models

#endif //LAYING_GRASS_PROJECT_BOARD_H