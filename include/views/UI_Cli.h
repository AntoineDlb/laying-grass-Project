//
// Created by antoi on 03/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_UI_CLI_H
#define LAYING_GRASS_PROJECT_UI_CLI_H
#include <iostream>
#include <vector>
#include "models/Board.h"
#include "models/Player.h"
#include "models/Position.h"
#include <conio.h>

#include "models/TileQueue.h"

namespace Views {
    class UI_Cli {
    public:
        //display
        void clearScreen();
        void displayWelcome();
        void displayBoard(Models::Board& board);
        void displayTile(Models::Tile& tile);
        void displayMarket(std::vector<Models::Tile>& marketTiles);
        void displayPlayer(Models::Player& player);
        void displayMessage(std::string& message);
        void displayBoardWithTile(Models::Board& board, Models::Tile& tile, Models::Position& pos, int playerId);
        void displayWinner(std::vector<Models::Player>& players, int winnerId);

        //inputs
        int askNumberOfPlayers();
        std::string askPlayerName(std::string playerName);
        std::string askPlayerColor(std::vector<std::string>& availableColors);
        void tilePlacement(Models::Tile& tile, Models::Board& board, int playerId);

    private:
        std::string renderCell(Models::Cell& cell, bool isTempTile = false);
    };
} // Views

#endif //LAYING_GRASS_PROJECT_UI_CLI_H
