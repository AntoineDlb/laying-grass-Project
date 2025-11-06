//
// Created by antoi on 02/11/2025.
//
#include "Types.h"
#ifndef LAYING_GRASS_PROJECT_BONUSSQUARE_H
#define LAYING_GRASS_PROJECT_BONUSSQUARE_H

namespace Models {
    class BonusSquare {
    private:
        BonusType bonusType;
    public:
        BonusSquare();

        BonusType const getBonusType(){ return bonusType;}
        void setBonusType(BonusType b){ bonusType = b; }

        bool isExchange();
        bool isStone();
        bool isSteal();

    };
} // Models

#endif //LAYING_GRASS_PROJECT_BONUSSQUARE_H