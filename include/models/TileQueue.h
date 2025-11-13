//
// Created by antoi on 02/11/2025.
//

#include "Tile.h"
#include <vector>
#include <iostream>
#include <deque>

#ifndef LAYING_GRASS_PROJECT_TILEQUEUE_H
#define LAYING_GRASS_PROJECT_TILEQUEUE_H

namespace Models {
    class TileQueue {
    private:
        std::deque<Tile> tiles;
        std::vector<Tile> usedTiles;
        int currentIndex;
    public:
        TileQueue();

        std::deque<Tile>& getTiles() { return tiles; }
        std::vector<Tile>& getUsedTiles() { return usedTiles; }

        void loadTiles();
        void shuffleTiles();
        void addTile(Tile t);
        void addUsedTile(Tile t);

        void removeTile(Tile t);
        void removeUsedTile(Tile t);

        Tile* getCurrentTile();
        Tile* getTileAt(int index);
        std::vector<Tile> getNextTiles(int count);

        void selectTileFromMarket(int marketIndex);
        void recycleTiles();
        bool isEmpty() const;
    };
} // Models

#endif //LAYING_GRASS_PROJECT_TILEQUEUE_H