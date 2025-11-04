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
        BonusType bonusType;
        int id;
    public:
        Cell();

        State const getState() const { return state ;}
        void setState(State s){ state = s; }

        bool isEmpty();
        bool isGrass();
        bool isBonus();


    };
} // Models

#endif //LAYING_GRASS_PROJECT_CELL_H