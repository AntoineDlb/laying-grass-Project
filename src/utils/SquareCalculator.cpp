//
// Created by antoi on 02/11/2025.
//

#include "../../include/utils/SquareCalculator.h"
#include "../../include/models/Board.h"
#include "../../include/models/Cell.h"

#include <algorithm>


namespace Utils {

    std::vector<PlayerResult> SquareCalculator::rankingPlayersByScore(Models::Board& board) {
        std::vector<PlayerResult> results;

        int playerCount = board.getPlayersNumber();

        for (int playerID = 0; playerID < playerCount; playerID++) {
            PlayerResult result{};
            result.playerID = playerID;
            result.playerScore = calculateSquare(board, playerID);
            result.playerGrass = calculateGrass(board, playerID);

            results.push_back(result);
        }

        std::sort(results.begin(), results.end(),
            [](const PlayerResult& a, const PlayerResult& b) {
                if (a.playerScore != b.playerScore) {
                    return a.playerScore > b.playerScore;
                }
                return a.playerGrass > b.playerGrass;
            });

        return results;
    }

    int SquareCalculator::calculateSquare(Models::Board& board, int playerID) {
        std::vector<std::vector<Models::Cell>> grid = board.getGrid();

        int height = grid.size();
        int width = grid[0].size();
        int score = 0;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                Models::Cell cell = grid[row][col];

                if (cell.getPlayerId() == playerID) {
                    int maxSquareSize = 1;

                    for (int size = 2; row + size <= height && col + size <= width; size++) {
                        bool isSquare = true;

                        for (int i = 0; i < size && isSquare; i++) {
                            for (int j = 0; j < size && isSquare; j++) {
                                if (grid[row + i][col + j].getPlayerId() != playerID) {
                                    isSquare = false;
                                }
                            }
                        }

                        if (isSquare) {
                            maxSquareSize = size;
                        } else {
                            break;
                        }
                    }

                    score += maxSquareSize;
                }
            }
        }

        return score;
    }

    int SquareCalculator::calculateGrass(Models::Board& board, int playerID) {
        std::vector<std::vector<Models::Cell>> grid = board.getGrid();

        int height = grid.size();
        int width = grid[0].size();
        int grassCount = 0;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                Models::Cell cell = grid[row][col];

                if (cell.getPlayerId() == playerID) {
                    grassCount++;
                }
            }
        }

        return grassCount;
    }

} // Utils
