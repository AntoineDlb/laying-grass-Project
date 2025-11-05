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
        int width;
        int height;
        int playersNumber;


    public:
        Board(int playersNumber);

        int  const getWidth(){ return width; }
        void setWidth(int w){ width = w; }

        int const getHeight(){ return height; }
        void setHeight(int h){ height = h; }

        std::vector<std::vector<Cell>> const getGrid(){ return grid; }
        void setGrid(std::vector<std::vector<Cell>> g){ grid = g; }

        bool const isTouchingOther();
        bool const isTouchingBonus();

        bool const isTouchingWall();

        void placeBonus();

        bool const canPlaceTile();
        void placeTile(Position p);
    };
}// Models

#endif //LAYING_GRASS_PROJECT_BOARD_H