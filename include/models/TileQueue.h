//
// Created by antoi on 02/11/2025.
//

#include "Tile.h"
#include <vector>
#include <iostream>

#ifndef LAYING_GRASS_PROJECT_TILEQUEUE_H
#define LAYING_GRASS_PROJECT_TILEQUEUE_H

namespace Models {
    class TileQueue {
    private:
        std::vector<Tile> tiles;
        std::vector<Tile> market;
        std::vector<Tile> usedTiles;
    public:
        TileQueue();

        std::vector<Tile> const getTiles(){ return tiles; }
        std::vector<Tile> const getMarket(){ return market; }

        void loadTiles();
        void addTile(Tile t);
        void addMarketTile(Tile t);
        void addUsedTile(Tile t);

        void removeTile(Tile t);
        void removeMarketTile(Tile t);
        void removeUsedTile(Tile t);

    };
} // Models

#endif //LAYING_GRASS_PROJECT_TILEQUEUE_H