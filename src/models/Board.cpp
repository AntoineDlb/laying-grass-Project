//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Board.h"
#include "../../include/utils/Random.h"
#include <cmath>

namespace Models {
    Board::Board(int playersNumber) {
        this->playersNumber = playersNumber;
        this->exchangeCount = std::ceil(1.5 * playersNumber);
        this->stoneCount = std::ceil(0.5 * playersNumber);
        this->stealCount = playersNumber;
        if (playersNumber >= 2 && playersNumber <= 4) {
            this->width = 20;
            this->height = 20;
        } else if (playersNumber >= 5 && playersNumber <= 9) {
            this->width = 30;
            this->height = 30;
        }
        grid.resize(height, std::vector<Cell>(width, Cell()));
        placeBonus();
    };

    void Board::placeBonus() {
        while (exchangeCount != 0 || stoneCount != 0 || stealCount != 0) {
            int x = Utils::Random::getInt(0, width - 1);
            int y = Utils::Random::getInt(0, height - 1);
            Position pos(x, y);

            if (grid[y][x].getState() == State::EMPTY && !isTouchingWall(pos) && !isCellTouchingSomething(pos, State::BONUS, -1)) {
                if (exchangeCount > 0) {
                    grid[y][x].setState(State::BONUS);
                    grid[y][x].setBonusType(BonusType::EXCHANGE);
                    exchangeCount--;
                } else if (stoneCount > 0) {
                    grid[y][x].setState(State::BONUS);
                    grid[y][x].setBonusType(BonusType::STONE);
                    stoneCount--;
                } else if (stealCount > 0) {
                    grid[y][x].setState(State::BONUS);
                    grid[y][x].setBonusType(BonusType::STEAL);
                    stealCount--;
                }
            }
        }
    }

    bool Board::isCellTouchingSomething(Position& pos, State state, int playerId = -1) {
        int x = pos.getX();
        int y = pos.getY();

        int directions[4][2] = {
            {0, -1},
            {0, 1},
            {-1, 0},
            {1, 0}
        };

        for (auto& dir : directions) {
            int checkX = x + dir[0];
            int checkY = y + dir[1];

            if (checkX >= 0 && checkX < width && checkY >= 0 && checkY < height) {
                if (state == State::GRASS) {
                    if (grid[checkY][checkX].getState() == State::GRASS &&
                        grid[checkY][checkX].getPlayerId() != playerId &&
                        grid[checkY][checkX].getPlayerId() != -1) {
                        return true;
                    }
                } else {
                    if (grid[checkY][checkX].getState() == state) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    bool Board::isTileTouchingGrass(Tile* tile, Position& pos, int playerId) {
        const auto& pattern = tile->getPattern();
        int tileHeight = tile->getHeight();
        int tileWidth = tile->getWidth();
        int tileSize = tile->getSize();
        int x = pos.getX();
        int y = pos.getY();

        while (tileSize > 0) {
            for (int ty = 0; ty < tileHeight; ++ty) {
                for (int tx = 0; tx < tileWidth; ++tx) {
                    if (pattern[ty][tx].getState() == State::GRASS) {
                        int boardX = x + tx;
                        int boardY = y + ty;
                        Position cellPos(boardX, boardY);
                        if (isCellTouchingSomething(cellPos,State::GRASS, playerId)) {
                            return true;
                        }
                        tileSize--;
                    }
                }
            }
        }
        return false;
    }

    bool Board::isTouchingWall(Position& pos) {
        int x = pos.getX();
        int y = pos.getY();

        return (x == 0 || x == width - 1 || y == 0 || y == height - 1);
    }

    bool Board::isInsideBoard(Position& pos){
        int x = pos.getX();
        int y = pos.getY();
        return (x >= 0 && x < width && y >= 0 && y < height);

    }

    bool Board::canPlaceTile(Tile* tile, Position& pos, int playerId) {
        const auto& pattern = tile->getPattern();
        int tileHeight = tile->getHeight();
        int tileWidth = tile->getWidth();

        bool touchingOwnGrass = false;

        for (int ty = 0; ty < tileHeight; ++ty) {
            for (int tx = 0; tx < tileWidth; ++tx) {
                if (pattern[ty][tx].getState() == State::GRASS) {
                    int boardX = pos.getX() + tx;
                    int boardY = pos.getY() + ty;
                    Position cellPos(boardX, boardY);

                    if (isTouchingWall(cellPos)) {
                        return false;
                    }

                    if (grid[boardY][boardX].getState() != State::EMPTY) {
                        return false;
                    }

                    if (isTouchingWall(cellPos)) {
                        return false;
                    }

                    if (isCellTouchingSomething(cellPos , State::BONUS)) {
                        return false;
                    }

                    if (isCellTouchingSomething(cellPos,State::GRASS, !playerId)) {
                        return false;
                    }

                    if (isCellTouchingSomething(cellPos, State::GRASS, playerId)) {
                        touchingOwnGrass = true;
                    }
                }
            }
        }
        bool isFirstPlacement = true;
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (grid[y][x].getState() == State::GRASS &&
                    grid[y][x].getPlayerId() == playerId) {
                    isFirstPlacement = false;
                    break;
                }
            }
            if (!isFirstPlacement) break;
        }
        return isFirstPlacement || touchingOwnGrass;
    }

    void Board::placeTile(Tile* tile, Position& pos, int playerId) {
        const auto& pattern = tile->getPattern();
        int tileHeight = tile->getHeight();
        int tileWidth = tile->getWidth();

        for (int ty = 0; ty < tileHeight; ++ty) {
            for (int tx = 0; tx < tileWidth; ++tx) {
                if (pattern[ty][tx].getState() == State::GRASS) {
                    int boardX = pos.getX() + tx;
                    int boardY = pos.getY() + ty;

                    grid[boardY][boardX].setState(State::GRASS);
                    grid[boardY][boardX].setPlayerId(playerId);
                }
            }
        }
    }

}// Models
