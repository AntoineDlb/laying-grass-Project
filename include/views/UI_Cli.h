//
// Created by antoi on 03/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_UI_CLI_H
#define LAYING_GRASS_PROJECT_UI_CLI_H
#include "models/Board.h"
#include "models/Player.h"
#include <iostream>

namespace Views {
    class UI_Cli {
        //displauy
        void displayWelcome();
        void displayBoard(Models::Board& board);
        void displayTile(Models::Tile& tile);
        void displayPlayer(Models::Player& player);
        void displayMessage(std::string& message);
        void displayWinner(std::vector<Models::Player>& players, int winnerId);

        //inputs
        int askNumberOfPlayers();
        std::string askPlayerName(std::string playerName);
        std::string askPlayerColor(std::string playerColor);
    };
} // Views

#endif //LAYING_GRASS_PROJECT_UI_CLI_H