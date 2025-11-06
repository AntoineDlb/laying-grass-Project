//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/TileQueue.h"

namespace Models {
    TileQueue::TileQueue() {
        loadTiles();
    }

    void TileQueue::loadTiles() {
        int tileId = 1;
        while (true) {
            try {
                Tile t = Tile::createTile(tileId);
                addTile(t);
                tileId++;
            } catch (std::out_of_range& e) {
                break;
            }

        }
    }

    void TileQueue::addTile(Tile t) {
        tiles.push_back(t);
    }

    void TileQueue::addMarketTile(Tile t) {
        market.push_back(t);
    }

    void TileQueue::addUsedTile(Tile t) {
        usedTiles.push_back(t);
    }

    void TileQueue::removeTile(Tile t) {
        for (size_t i = 0; i < tiles.size(); ++i) {
            if (tiles[i].getId() == t.getId()) {
                tiles.erase(tiles.begin() + i);
                break;
            }
        }
    }

    void TileQueue::removeMarketTile(Tile t) {
        for (size_t i = 0; i < market.size(); ++i) {
            if (market[i].getId() == t.getId()) {
                market.erase(market.begin() + i);
                break;
                }
            }
        }

    void TileQueue::removeUsedTile(Tile t) {
        for (auto it = usedTiles.begin(); it != usedTiles.end(); ++it) {
            if (it->getId() == t.getId()) {
                usedTiles.erase(it);
                break;
            }
        }
    }

} // Models