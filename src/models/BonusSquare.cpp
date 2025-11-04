//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/BonusSquare.h"

namespace Models {
    bool BonusSquare::isExchange() {
        return this->bonusType == BonusType::EXCHANGE;
    }

    bool BonusSquare::isStone() {
        return this->bonusType == BonusType::STONE;
    }

    bool BonusSquare::isSteal() {
        return this->bonusType == BonusType::STEAL;
    }
} // Models