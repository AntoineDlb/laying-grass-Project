//
// Created by antoi on 03/11/2025.
//

#include "../../include/views/UI_Cli.h"

namespace Views {

    // display

    void UI_Cli::displayWelcome() {
        std::cout << "=====================================" << std::endl;
        std::cout << "     Welcome to the Lying Grass      " << std::endl;
        std::cout << "=====================================" << std::endl;
    }

    void UI_Cli::displayBoard(Models::Board& board) {

        int width = board.getWidth();
        int height = board.getHeight();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Models::Cell cell = board.getGrid()[y][x];
                switch (cell.getState()) {
                    case Models::State::EMPTY:
                        std::cout << " . ";
                        break;
                    case Models::State::GRASS:
                        std::cout << " # ";
                        break;
                    case Models::State::BONUS:
                        switch (cell.getBonusType()) {
                        case Models::BonusType::EXCHANGE:
                                std::cout << " E ";
                                break;
                        case Models::BonusType::STONE:
                                std::cout << " S ";
                                break;
                        case Models::BonusType::STEAL:
                                std::cout << " V ";
                                break;
                        default:
                                std::cout << " B ";
                                break;
                        }
                        break;
                }
            }
            std::cout << std::endl;
        }
    }

    void UI_Cli::displayTile(Models::Tile& tile) {
        int height = tile.getHeight();
        int width = tile.getWidth();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                switch (tile.getPattern()[y][x].getState()) {
                    case Models::State::EMPTY:
                        std::cout << " . ";
                        break;
                    case Models::State::GRASS:
                        std::cout << " # ";
                        break;
                    case Models::State::BONUS:
                        std::cout << " B ";
                        break;
                }
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

    std::string UI_Cli::askPlayerColor(std::string playerColor) {
        std::cout << "Enter color for " << playerColor << ": ";
        std::string color;
        std::cin >> color;
        return color;
    }
} // Views