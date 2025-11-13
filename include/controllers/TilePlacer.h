//
// Created by antoi 09/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_TILEPLACER_H
#define LAYING_GRASS_PROJECT_TILEPLACER_H

#include "../models/Tile.h"
#include "../models/Board.h"
#include "../models/Position.h"

namespace Controllers {
    class TilePlacer {
    private:
        Models::Tile* currentTile;
        Models::Board* board;
        Models::Position currentPos;
        int playerId;
        bool placementValid;
        void updateValidity();

    public:
        TilePlacer(Models::Tile* tile, Models::Board* board, int playerId);
        void setInitialPosition();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();

        void rotateTile();
        void flipTile();

        bool isValidPlacement() const { return placementValid; }

        Models::Position getPosition() const { return currentPos; }

        Models::Tile* getTile() const { return currentTile; }

        bool confirmPlacement();
    };
} // Controllers

#endif //LAYING_GRASS_PROJECT_TILEPLACER_H
