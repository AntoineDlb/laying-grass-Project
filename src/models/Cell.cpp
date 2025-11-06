//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Cell.h"

namespace Models {

    Cell::Cell() {}


    bool Cell::isEmpty() {
        return this->state == State::EMPTY;
    }

    bool Cell::isGrass() {
        return this->state == State::GRASS;
    }

    bool Cell::isBonus() {
        return this->state == State::BONUS;
    }

} // Models