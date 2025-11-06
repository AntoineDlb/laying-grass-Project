//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_POSITION_H
#define LAYING_GRASS_PROJECT_POSITION_H

namespace Models {
    class Position {
    private:
        int x = 0;
        int y = 0;
    public:
        Position();
        Position(int x, int y);

        int const getX(){ return x; }
        void setX(int x){ this->x = x; }

        int const getY(){ return y; }
        void setY(int y){ this->y = y; }

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;
        bool operator<(const Position& other) const;
    };
} // Models

#endif //LAYING_GRASS_PROJECT_POSITION_H