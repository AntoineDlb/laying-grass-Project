//
// Created by antoi on 03/11/2025.
//

#include "../../include/views/UI_Cli.h"
#include "../../include/utils/KeyboardInput.h"
#include "../../include/controllers/TilePlacer.h"
#include <iostream>

namespace Views {

    // display
    void UI_Cli::clearScreen() {
        std::cout << "\033[H\033[J";
        std::cout << std::endl;
    }

    void UI_Cli::displayWelcome() {
        std::cout << "=====================================" << std::endl;
        std::cout << "     Welcome to the Lying Grass      " << std::endl;
        std::cout << "=====================================" << std::endl;
    }

    std::string UI_Cli::renderCell(Models::Cell& cell, bool isTempTile) {
        switch (cell.getState()) {
            case Models::State::EMPTY:
                return " . ";
            case Models::State::GRASS:
                if (isTempTile) {
                    return "[#]";
                } else {
                    return " # ";
                }
            case Models::State::BONUS:
                switch (cell.getBonusType()) {
                    case Models::BonusType::EXCHANGE:
                        return " E ";
                    case Models::BonusType::STONE:
                        return " S ";
                    case Models::BonusType::STEAL:
                        return " V ";
                    default:
                        return " B ";
                }
            default:
                return " ? ";
        }
    }

    void UI_Cli::displayBoard(Models::Board& board) {

        int width = board.getWidth();
        int height = board.getHeight();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Models::Cell cell = board.getGrid()[y][x];
                std::cout << renderCell(cell);
            }
            std::cout << std::endl;
        }
    }

    void UI_Cli::displayTile(Models::Tile& tile) {
        int height = tile.getHeight();
        int width = tile.getWidth();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Models::Cell cell = tile.getPattern()[y][x];
                std::cout << renderCell(cell);
            }
            std::cout << std::endl;
        }
    }

    void UI_Cli::displayBoardWithTile(Models::Board& board, Models::Tile& tile, Models::Position& pos, int playerId) {
        int boardWidth = board.getWidth();
        int boardHeight = board.getHeight();
        int tileWidth = tile.getWidth();
        int tileHeight = tile.getHeight();
        int tileX = pos.getX();
        int tileY = pos.getY();

        std::vector<std::vector<Models::Cell>> tempGrid = board.getGrid();

        for (int ty = 0; ty < tileHeight; ++ty) {
            for (int tx = 0; tx < tileWidth; ++tx) {
                int boardX = tileX + tx;
                int boardY = tileY + ty;

                if (boardX >= 0 && boardX < boardWidth && boardY >= 0 && boardY < boardHeight) {
                    if (tile.getPattern()[ty][tx].getState() == Models::State::GRASS) {
                        tempGrid[boardY][boardX] = tile.getPattern()[ty][tx];
                        tempGrid[boardY][boardX].setPlayerId(playerId);
                    }
                }
            }
        }

        for (int y = 0; y < boardHeight; ++y) {
            for (int x = 0; x < boardWidth; ++x) {
                Models::Cell cell = tempGrid[y][x];

                bool isTempTile = false;
                if (x >= tileX && x < tileX + tileWidth && y >= tileY && y < tileY + tileHeight) {
                    int tx = x - tileX;
                    int ty = y - tileY;
                    if (tile.getPattern()[ty][tx].getState() == Models::State::GRASS) {
                        isTempTile = true;
                    }
                }

                std::cout << renderCell(cell, isTempTile);
            }
            std::cout << std::endl;
        }
    }

    void UI_Cli::displayPlayer(Models::Player& player) {
        std::cout << "Player " << player.getId() << ": " << player.getName()
                  << " | Color: " << player.getColor()
                  << " | Score: " << player.getScore()
                  << " | Exchanges: " << player.getExchange()
                  << std::endl;
    }

    void UI_Cli::displayMarket(std::vector<Models::Tile>& marketTiles) {
        int selectedIndex = 0;

        while (true) {
            clearScreen();
            std::cout << "=== TILE MARKET ===" << std::endl;
            std::cout << "Choose a tile (UP/DOWN to navigate, SPACE to select)" << std::endl;
            std::cout << std::endl;

            for (size_t i = 0; i < marketTiles.size(); ++i) {
                if (i == selectedIndex) {
                    std::cout << ">>> [" << (i + 1) << "]" << std::endl;
                } else {
                    std::cout << "    [" << (i + 1) << "]" << std::endl;
                }
                displayTile(marketTiles[i]);
                std::cout << std::endl;
            }

            Utils::KeyCode key = Utils::KeyboardInput::getKeyPressed();

            switch (key) {
                case Utils::KeyCode::UP:
                    if (selectedIndex > 0) selectedIndex--;
                    break;
                case Utils::KeyCode::DOWN:
                    if (selectedIndex < marketTiles.size() - 1) selectedIndex++;
                    break;
                case Utils::KeyCode::CONFIRM:
                    return selectedIndex;
                default:
                    break;
            }
        }
    }


    void UI_Cli::displayMessage(std::string& message) {
        std::cout << message << std::endl;
    }

    void UI_Cli::displayWinner(std::vector<Models::Player>& players, int winnerId) {
        for (auto& player : players) {
            if (player.getId() == winnerId) {
                std::cout << "Congratulations " << player.getName() << "! You are the winner with a score of " << player.getScore() << "!" << std::endl;
                return;
            }
        }
    }

    //inputs
    int UI_Cli::askNumberOfPlayers() {
        int playerNumber = 0;
        while (playerNumber < 2 || playerNumber > 9) {
            std::cout << "Enter number of players (2-9): ";
            std::cin >> playerNumber;
            if (playerNumber < 2 || playerNumber > 9) {
                std::cout << "Invalid number of players. Please enter a number between 2 and 9." << std::endl;
            }
        }
        return playerNumber;
    }

    std::string UI_Cli::askPlayerName(std::string playerName) {
        std::cout << "Enter name for " << playerName << ": ";
        std::string name;
        std::cin >> name;
        return name;
    }

    std::string UI_Cli::askPlayerColor(std::vector<std::string>& availableColors) {
        int choice = -1;

        while (choice < 1 || choice > availableColors.size()) {
            std::cout << "\nAvailable colors:" << std::endl;
            for (size_t i = 0; i < availableColors.size(); ++i) {
                std::cout << (i + 1) << ". " << availableColors[i] << std::endl;
            }

            std::cout << "Choose a color (1-" << availableColors.size() << "): ";
            std::cin >> choice;

            if (choice < 1 || choice > availableColors.size()) {
                std::cout << "Invalid choice. Please enter a number between 1 and " << availableColors.size() << "." << std::endl;
            }
        }

        std::string selectedColor = availableColors[choice - 1];
        availableColors.erase(availableColors.begin() + choice - 1);
        return selectedColor;
    }

    void UI_Cli::tilePlacement(Models::Tile& tile, Models::Board& board, int playerId) {

        Controllers::TilePlacer placer(&tile, &board, playerId);
        bool placementConfirmed = false;

        while (!placementConfirmed) {
            clearScreen();
            std::cout << std::endl;

            Models::Position pos = placer.getPosition();
            bool isValid = placer.isValidPlacement();

            // Display status
            if (isValid) {
                std::cout << "=== PLACEMENT VALID ===" << std::endl;
            } else {
                std::cout << "=== PLACEMENT INVALID ===" << std::endl;
            }
            std::cout << "Position: (" << pos.getX() << ", " << pos.getY() << ")" << std::endl;
            std::cout << std::endl;

            displayBoardWithTile(board, tile, pos, playerId);

            std::cout << std::endl;
            std::cout << "Controls:" << std::endl;
            std::cout << "  Arrow Keys: Move tile" << std::endl;
            std::cout << "  R: Rotate" << std::endl;
            std::cout << "  SPACE: Confirm" << std::endl;
            std::cout << std::endl;
            std::cout << "Press a key..." << std::endl;

            Utils::KeyCode key = Utils::KeyboardInput::getKeyPressed();

            switch (key) {
                case Utils::KeyCode::UP:
                    placer.moveUp();
                    break;
                case Utils::KeyCode::DOWN:
                    placer.moveDown();
                    break;
                case Utils::KeyCode::LEFT:
                    placer.moveLeft();
                    break;
                case Utils::KeyCode::RIGHT:
                    placer.moveRight();
                    break;
                case Utils::KeyCode::ROTATE:
                    placer.rotateTile();
                    break;
                case Utils::KeyCode::CONFIRM:
                    if (placer.isValidPlacement()) {
                        placer.confirmPlacement();
                        placementConfirmed = true;
                        clearScreen();
                        std::cout << "Tile placed successfully!" << std::endl;
                    } else {
                        clearScreen();
                        std::cout << "[ERROR] Cannot place tile at this position!" << std::endl;
                        std::cout << "Press any key to continue..." << std::endl;
                        _getch();
                    }
                    break;
                default:
                    break;
            }
        }
    }
} // Views
