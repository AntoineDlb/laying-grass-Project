#ifndef LAYING_GRASS_PROJECT_SQUARECALCULATOR_H
#define LAYING_GRASS_PROJECT_SQUARECALCULATOR_H

#include <cstdint>

namespace Models {
    class Board;
}

namespace Utils {
    class SquareCalculator {
    private:
        const Models::Board &board;

    public:
        explicit SquareCalculator(const Models::Board &board) noexcept;
        int calculateSquare(int x, int y, int playerId) const;
    };
} // namespace Utils

#endif // LAYING_GRASS_PROJECT_SQUARECALCULATOR_H
