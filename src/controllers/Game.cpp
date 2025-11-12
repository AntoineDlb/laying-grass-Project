//
// Created by antoi on 02/11/2025.
//

#include "../../include/controllers/Game.h"
#include "../../include/utils/Random.h"
#include "../../include/utils/InputValidator.h"
#include "../../include/utils/SquareCalculator.h"
#include <iostream>
#include <algorithm>

namespace Controllers {

    Game::Game() : board(nullptr), tileQueue(nullptr), ui(nullptr), currentRound(0), maxRounds(9) {
    }

    Game::~Game() {
        delete board;
        delete tileQueue;
        delete ui;
    }

    void Game::start() {

        ui = new Views::UI_Cli();
        initializePlayers();
        initializeBoard();
        initializeTileQueue();
        generateTurnOrder();
        placeStartingTiles();
    }

    void Game::run() {

        while (!isGameOver()) {
            playRound();
            currentRound++;
        }

        finalPurchasePhase();
        end();
    }

    void Game::end() {

        calculateScores();
        Models::Player* winner = determineWinner();

        if (winner != nullptr) {
            std::cout << "=== WINNER ===" << std::endl;
            std::cout << "Player: " << winner->getName() << " (ID: " << winner->getId() << ")" << std::endl;
            std::cout << "Score: " << winner->getScore() << std::endl;
        }
    }

    void Game::initializePlayers() {

        int playerCount = ui->askNumberOfPlayers();

        Utils::InputValidator validator;
        std::vector<std::string> availableColors = validator.getAvailableColors();

        for (int i = 0; i < playerCount; i++) {
            std::string name = ui->askPlayerName("Player " + std::to_string(i + 1));
            std::string color = ui->askPlayerColor(availableColors);

            Models::Player player(i, name, color);
            players.push_back(player);
        }
    }

    void Game::initializeBoard() {

        int playerCount = players.size();
        board = new Models::Board(playerCount);

    }

    void Game::initializeTileQueue() {

        tileQueue = new Models::TileQueue();
        tileQueue->loadTiles();

    }

    void Game::generateTurnOrder() {

        turnOrder.clear();
        for (size_t i = 0; i < players.size(); i++) {
            turnOrder.push_back(static_cast<int>(i));
        }

        for (int i = turnOrder.size() - 1; i > 0; --i) {
            int j = Utils::Random::getInt(0, i);
            std::swap(turnOrder[i], turnOrder[j]);
        }

        std::cout << "Turn order: ";
        for (int id : turnOrder) {
            std::cout << id << " ";
        }
        std::cout << std::endl;
    }

    void Game::placeStartingTiles() {

        for (auto& player : players) {

            std::vector<std::vector<Models::Cell>> pattern(1, std::vector<Models::Cell>(1));
            pattern[0][0].setState(Models::State::GRASS);
            pattern[0][0].setPlayerId(player.getId());

            Models::Tile startTile(0, pattern);
            startTile.setPlayerId(player.getId());

            ui->tilePlacement(startTile, *board, player.getId(), players);

        }
    }

    void Game::playRound() {
        std::cout << "\n=== ROUND " << (currentRound + 1) << " / " << maxRounds << " ===" << std::endl;

        for (int playerId : turnOrder) {
            Models::Player& player = players[playerId];
            handlePlayerTurn(player);
        }
    }

    void Game::handlePlayerTurn(Models::Player& player) {
        std::cout << "\n--- Turn of " << player.getName() << " ---" << std::endl;
        std::cout << "Exchange coupons: " << player.getExchange() << std::endl;

        Models::Tile* currentTile = tileQueue->getCurrentTile();
        if (currentTile == nullptr) {
            std::cout << "No more tiles available!" << std::endl;
            return;
        }

        std::cout << "Current tile:" << std::endl;
        ui->displayTile(*currentTile);

        std::cout << "Use exchange coupon to choose from market? (y/n): ";
        char choice;
        std::cin >> choice;

        if ((choice == 'y' || choice == 'Y') && player.getExchange() > 0) {
            std::vector<Models::Tile> marketTiles = tileQueue->getNextTiles(5);
            if (!marketTiles.empty()) {
                int selectedIndex = ui->displayMarket(marketTiles);
                tileQueue->selectTileFromMarket(selectedIndex);
                currentTile = tileQueue->getCurrentTile();
                player.setExchange(player.getExchange() - 1);
            }
        }

        bool placed = tryPlaceTile(player, currentTile);

        if (placed) {
            Models::Position lastPos(0, 0);
            std::vector<Models::Position> acquiredBonuses = board->checkBonusAcquisition(currentTile, lastPos, player.getId());

            for (auto& bonusPos : acquiredBonuses) {
                Models::Cell* bonusCell = board->getCell(bonusPos);
                if (bonusCell != nullptr) {
                    Models::BonusType bonusType = bonusCell->getBonusType();
                    board->removeBonus(bonusPos, player.getId());

                    switch (bonusType) {
                        case Models::BonusType::EXCHANGE:
                            applyExchangeBonus(player);
                            break;
                        case Models::BonusType::STONE:
                            applyStoneBonus(player);
                            break;
                        case Models::BonusType::STEAL:
                            applyRobberyBonus(player);
                            break;
                        default:
                            break;
                    }
                }
            }

            tileQueue->addUsedTile(*currentTile);
            tileQueue->removeTile(*currentTile);
        } else {
            std::cout << "Cannot place tile! Turn lost." << std::endl;
            tileQueue->addUsedTile(*currentTile);
            tileQueue->removeTile(*currentTile);
        }
    }

    bool Game::tryPlaceTile(Models::Player& player, Models::Tile* tile) {

        if (tile == nullptr || board == nullptr) {
            return false;
        }
    ui->displayBoard(*board, players);
    ui->tilePlacement(*tile, *board, player.getId(), players);
        return tile->isPlaced();
    }


    void Game::applyExchangeBonus(Models::Player& player) {
        player.setExchange(player.getExchange() + 1);
        std::cout << "Player " << player.getName() << " received 1 exchange coupon!" << std::endl;
    }

    void Game::applyStoneBonus(Models::Player& player) {
        std::cout << "Player " << player.getName() << " can place a stone tile!" << std::endl;
        std::cout << "Enter stone position (x y): ";
        int x, y;
        std::cin >> x >> y;

        Models::Position stonePos(x, y);

        if (board->isInsideBoard(stonePos) && !board->isTouchingWall(stonePos)) {
            Models::Cell* cell = board->getCell(stonePos);
            if (cell != nullptr && cell->getState() == Models::State::EMPTY) {
                board->placeStone(stonePos);
                std::cout << "Stone placed at (" << x << ", " << y << ")!" << std::endl;
            } else {
                std::cout << "Invalid position for stone placement!" << std::endl;
            }
        } else {
            std::cout << "Cannot place stone at that position!" << std::endl;
        }
    }

    void Game::applyRobberyBonus(Models::Player& player) {
        std::cout << "Player " << player.getName() << " can steal a tile from another player!" << std::endl;
        std::cout << "Available players to steal from:" << std::endl;
        for (auto& p : players) {
            if (p.getId() != player.getId()) {
                std::cout << "  Player " << p.getId() << ": " << p.getName() << std::endl;
            }
        }

        std::cout << "Choose player ID to steal from: ";
        int targetPlayerId;
        std::cin >> targetPlayerId;

        if (targetPlayerId == player.getId()) {
            std::cout << "Cannot steal from yourself!" << std::endl;
            return;
        }

        Models::Player* targetPlayer = getPlayerById(targetPlayerId);
        if (targetPlayer == nullptr) {
            std::cout << "Invalid player ID!" << std::endl;
            return;
        }
    ui->displayBoard(*board, players);
        std::cout << "Enter position of tile to steal (x y): ";
        int x, y;
        std::cin >> x >> y;

        Models::Position targetPos(x, y);
        Models::Cell* cell = board->getCell(targetPos);

        if (cell != nullptr && cell->getState() == Models::State::GRASS &&
            cell->getPlayerId() == targetPlayerId) {
            cell->setPlayerId(player.getId());
            std::cout << "Tile stolen successfully!" << std::endl;
        } else {
            std::cout << "Invalid position or tile doesn't belong to target player!" << std::endl;
        }
    }
    
    void Game::finalPurchasePhase() {
        std::cout << "\n=== FINAL PURCHASE PHASE ===" << std::endl;

        for (auto& player : players) {
            std::cout << "\nPlayer " << player.getName() << " has " << player.getExchange() << " coupons." << std::endl;

            while (player.getExchange() > 0) {
                std::cout << "Buy a 1x1 tile? (y/n): ";
                char choice;
                std::cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    std::vector<std::vector<Models::Cell>> pattern(1, std::vector<Models::Cell>(1));
                    pattern[0][0].setState(Models::State::GRASS);
                    pattern[0][0].setPlayerId(player.getId());

                    Models::Tile purchasedTile(-1, pattern); // ID -1 for purchased tiles
                    purchasedTile.setPlayerId(player.getId());
                    ui->tilePlacement(purchasedTile, *board, player.getId(), players);

                    player.setExchange(player.getExchange() - 1);
                    std::cout << "1x1 tile purchased and placed!" << std::endl;
                } else {
                    break;
                }
            }
        }
    }

    void Game::calculateScores() {

        std::vector<Utils::PlayerResult> results = Utils::SquareCalculator::rankingPlayersByScore(*board);

        for (auto& result : results) {
            Models::Player* player = getPlayerById(result.playerID);
            if (player != nullptr) {
                player->setScore(result.playerScore);
                std::cout << "Player " << player->getName()
                         << " - Largest square: " << result.playerScore
                         << " - Grass count: " << result.playerGrass << std::endl;
            }
        }
    }

    Models::Player* Game::determineWinner() {

        if (players.empty()) {
            return nullptr;
        }

        Models::Player* winner = &players[0];

        for (auto& player : players) {
            if (player.getScore() > winner->getScore()) {
                winner = &player;
            }
        }

        return winner;
    }

    // Utility methods
    bool Game::isGameOver() const {
        return currentRound >= maxRounds;
    }

    Models::Player* Game::getPlayerById(int id) {
        for (auto& player : players) {
            if (player.getId() == id) {
                return &player;
            }
        }
        return nullptr;
    }

} // Controllers