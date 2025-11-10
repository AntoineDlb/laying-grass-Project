//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_BOARD_H
#define LAYING_GRASS_PROJECT_BOARD_H
#include <vector>
#include <cmath>
#include "Cell.h"
#include "Position.h"
#include "Tile.h"

namespace Models {
    class Board {
    private:
        std::vector<std::vector<Cell>> grid;
        int width;
        int height;
        int playersNumber;

        int exchangeCount;
        int stoneCount;
        int stealCount;

    public:
        Board(int playersNumber);
        int const getPlayersNumber(){ return playersNumber; }

        int  const getWidth(){ return width; }
        void setWidth(int w){ width = w; }

        int const getHeight(){ return height; }
        void setHeight(int h){ height = h; }

        std::vector<std::vector<Cell>> const getGrid(){ return grid; }
        void setGrid(std::vector<std::vector<Cell>> g){ grid = g; }

        Cell* getCell(Position& pos) {
            if (!isInsideBoard(pos)) {
                return nullptr;
            }
            return &grid[pos.getY()][pos.getX()];
        };

        void placeBonus();
        void removeBonus(Position& pos);
        void placeStone(Position& pos);
        bool hasStoneAt(Position& pos) const;

        bool isCellTouchingSomething(Position& pos, State state, int playerId);
        bool isTileTouchingGrass(Tile* tile, Position& pos, int playerId);
        bool isTouchingWall(Position& pos);
        bool isInsideBoard(Position& pos);

        bool canPlaceTile(Tile* tile, Position& pos, int playerId);
        void placeTile(Tile* tile, Position& pos, int playerId);

        std::vector<Position> checkBonusAcquisition(Tile* tile, Position& pos, int playerId);

    };
}// Models

#endif //LAYING_GRASS_PROJECT_BOARD_H