//
// Created by antoi on 02/11/2025.
//

#include "Types.h"

#ifndef LAYING_GRASS_PROJECT_CELL_H
#define LAYING_GRASS_PROJECT_CELL_H

namespace Models {
    class Cell {
    private:
        State state = State::EMPTY;
        BonusType bonusType = BonusType::NONE;
        int playerId = -1;


    public:
        Cell();

        State const getState() const { return state ;}
        void setState(State s){ state = s; }

        BonusType const getBonusType() const { return bonusType; }
        void setBonusType(BonusType b) { bonusType = b; }

        int const getPlayerId() const { return playerId; }
        void setPlayerId(int id) { playerId = id; }

        bool isEmpty();
        bool isGrass();
        bool isBonus();


    };
} // Models

#endif //LAYING_GRASS_PROJECT_CELL_H