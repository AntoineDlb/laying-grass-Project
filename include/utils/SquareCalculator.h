//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_SQUARECALCULATOR_H
#define LAYING_GRASS_PROJECT_SQUARECALCULATOR_H

#include <optional>
#include <vector>

namespace Models {
    class Board;
}

namespace Utils {

    struct PlayerResult {
        int playerID;
        int playerScore;
        int playerGrass;
    };


    class SquareCalculator {

    public:
        SquareCalculator() = default;

        static std::vector<PlayerResult> rankingPlayersByScore(Models::Board& board);
        // on va get playerNuber depuis board et l utiliser pour classer les joueurs

        static int calculateSquare(Models::Board& board, int playerID);
        // on va get playerNuber depuis board effectuer cette methode pour chaque player

        static int calculateGrass(Models::Board& board, int playerID);
        // si score egal on compare le nombre de grass


    };

} // namespace Utils

#endif //LAYING_GRASS_PROJECT_SQUARECALCULATOR_H