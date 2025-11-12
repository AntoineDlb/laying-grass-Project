//
// Created by antoi on 02/11/2025.
//

#include "../../include/utils/SquareCalculator.h"
#include "../../include/models/Board.h"

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
        if (grid.empty() || grid[0].empty()) return 0;

        int height = static_cast<int>(grid.size());
        int width = static_cast<int>(grid[0].size());

        std::vector<std::vector<int>> dp(height, std::vector<int>(width, 0));
        int maxSide = 0;

        for (int r = 0; r < height; ++r) {
            for (int c = 0; c < width; ++c) {
                if (grid[r][c].getPlayerId() == playerID) {
                    if (r == 0 || c == 0) {
                        dp[r][c] = 1;
                    } else {
                        dp[r][c] = 1 + std::min({dp[r-1][c], dp[r][c-1], dp[r-1][c-1]});
                    }
                    if (dp[r][c] > maxSide) maxSide = dp[r][c];
                } else {
                    dp[r][c] = 0;
                }
            }
        }

        return maxSide;
    }

    int SquareCalculator::calculateGrass(Models::Board& board, int playerID) {
        std::vector<std::vector<Models::Cell>> grid = board.getGrid();

        int height = static_cast<int>(grid.size());
        int width = static_cast<int>(grid[0].size());
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
