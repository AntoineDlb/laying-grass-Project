//
// Created by antoi 09/11/2025.
//

#include "../../include/controllers/TilePlacer.h"

namespace Controllers {

    TilePlacer::TilePlacer(Models::Tile* tile, Models::Board* board, int playerId)
        : currentTile(tile), board(board), playerId(playerId), placementValid(false) {
        setInitialPosition();
        updateValidity();
    }

    void TilePlacer::setInitialPosition() {
        int centerX = board->getWidth() / 2;
        int centerY = board->getHeight() / 2;
        currentPos.setX(centerX);
        currentPos.setY(centerY);
    }

    void TilePlacer::updateValidity() {
        if (currentTile == nullptr || board == nullptr) {
            placementValid = false;
            return;
        }
        placementValid = board->canPlaceTile(currentTile, currentPos, playerId);
    }

    void TilePlacer::moveUp() {
        if (currentPos.getY() > 0) {
            currentPos.setY(currentPos.getY() - 1);
            updateValidity();
        }
    }

    void TilePlacer::moveDown() {
        if (currentTile != nullptr && currentPos.getY() + currentTile->getHeight() < board->getHeight()) {
            currentPos.setY(currentPos.getY() + 1);
            updateValidity();
        }
    }

    void TilePlacer::moveLeft() {
        if (currentPos.getX() > 0) {
            currentPos.setX(currentPos.getX() - 1);
            updateValidity();
        }
    }

    void TilePlacer::moveRight() {
        if (currentTile != nullptr && currentPos.getX() + currentTile->getWidth() < board->getWidth()) {
            currentPos.setX(currentPos.getX() + 1);
            updateValidity();
        }
    }

    void TilePlacer::rotateTile() {
        if (currentTile != nullptr) {
            currentTile->rotate();
            updateValidity();
        }
    }

    bool TilePlacer::confirmPlacement() {
        if (!placementValid) {
            return false;
        }

        if (board == nullptr || currentTile == nullptr) {
            return false;
        }

        board->placeTile(currentTile, currentPos, playerId);
        currentTile->setPlaced(true);
        currentTile->setPlayerId(playerId);

        return true;
    }

} // Controllers

