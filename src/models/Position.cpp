//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Position.h"

namespace Models {
    Position::Position() : x(0), y(0) {}

    Position::Position(int x, int y) : x(x), y(y) {}

    bool Position::operator==(const Position &other) const {
        return (this->x == other.x) && (this->y == other.y);
    }

    bool Position::operator!=(const Position &other) const {
        return !(*this == other);
    }

    bool Position::operator<(const Position &other) const {
        if (this->x != other.x) {
            return this->x < other.x;
        }
        return this->y < other.y;
    }


} // Models