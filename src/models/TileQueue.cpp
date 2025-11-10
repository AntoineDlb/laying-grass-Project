//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/TileQueue.h"
#include "../../include/utils/Random.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace Models {
    TileQueue::TileQueue() : currentIndex(0) {
        loadTiles();
    }

    void TileQueue::loadTiles() {
        int tileId = 1;
        while (true) {
            try {
                Tile t = Tile::createTile(tileId);
                addTile(t);
                tileId++;
            } catch (const std::out_of_range& e) {
                break;
            } catch (const std::runtime_error& e) {
                std::cerr << "Error loading tiles: " << e.what() << std::endl;
                break;
            }
        }
        shuffleTiles();
    }

    void TileQueue::shuffleTiles() {
        for (size_t i = tiles.size() - 1; i > 0; --i) {
            int j = Utils::Random::getInt(0, i);
            std::swap(tiles[i], tiles[j]);
        }
    }

    void TileQueue::addTile(Tile t) {
        tiles.push_back(t);
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

    void TileQueue::removeUsedTile(Tile t) {
        for (auto it = usedTiles.begin(); it != usedTiles.end(); ++it) {
            if (it->getId() == t.getId()) {
                usedTiles.erase(it);
                break;
            }
        }
    }

    Tile* TileQueue::getCurrentTile() {
        if (tiles.empty()) {
            recycleTiles();
            if (tiles.empty()) {
                return nullptr;
            }
        }
        return &tiles.front();
    }

    Tile* TileQueue::getTileAt(int index) {
        if (index < 0 || index >= tiles.size()) {
            return nullptr;
        }
        return &tiles[index];
    }

    std::vector<Tile> TileQueue::getNextTiles(int count) {
        std::vector<Tile> nextTiles;
        int available = std::min(count, static_cast<int>(tiles.size()));

        for (int i = 0; i < available; ++i) {
            nextTiles.push_back(tiles[i]);
        }

        return nextTiles;
    }

    void TileQueue::selectTileFromMarket(int marketIndex) {
        if (marketIndex < 0 || marketIndex >= tiles.size()) {
            return;
        }

        Tile selectedTile = tiles[marketIndex];
        tiles.erase(tiles.begin() + marketIndex);
        tiles.push_front(selectedTile);
    }

    void TileQueue::recycleTiles() {
        if (!usedTiles.empty()) {
            for (auto& tile : usedTiles) {
                tiles.push_back(tile);
            }
            usedTiles.clear();
            shuffleTiles();
        }
    }

    bool TileQueue::isEmpty() const {
        return tiles.empty() && usedTiles.empty();
    }

} // Models