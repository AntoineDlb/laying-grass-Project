//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_GAME_H
#define LAYING_GRASS_PROJECT_GAME_H

#include <vector>
#include <memory>
#include "../models/Board.h"
#include "../models/Player.h"
#include "../models/Tile.h"
#include "../models/TileQueue.h"
#include "../models/Position.h"
#include "../views/UI_Cli.h"

namespace Controllers {
    class Game {
    private:
        std::vector<Models::Player> players;
        Models::Board* board;
        Models::TileQueue* tileQueue;
        Views::UI_Cli* ui;
        int currentRound;
        int maxRounds;
        std::vector<int> turnOrder;

        void initializePlayers();
        void initializeBoard();
        void initializeTileQueue();
        void generateTurnOrder();

        void placeStartingTiles();
        void playRound();
        void handlePlayerTurn(Models::Player& player);
        bool tryPlaceTile(Models::Player& player, Models::Tile* tile);

        void applyExchangeBonus(Models::Player& player);
        void applyStoneBonus(Models::Player& player);
        void applyRobberyBonus(Models::Player& player);

        void finalPurchasePhase();
        void calculateScores();
        Models::Player* determineWinner();

    public:
        Game();
        ~Game();

        void start();
        void run();
        void end();

        std::vector<Models::Player> const getPlayers() { return players; }
        Models::Board* getBoard() { return board; }
        Models::TileQueue* getTileQueue() { return tileQueue; }
        int getCurrentRound() const { return currentRound; }

        void setCurrentRound(int round) { currentRound = round; }

        bool isGameOver() const;
        int getPlayerCount() const { return players.size(); }
        Models::Player* getPlayerById(int id);
    };
} // Controllers

#endif //LAYING_GRASS_PROJECT_GAME_H