//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_PLAYER_H
#define LAYING_GRASS_PROJECT_PLAYER_H
#include <string>

namespace Models {
    class Board;
    class Player {
    private :
        int id;
        std::string name;
        int score=0;
        int exchange = 1;
        std::string color;


    public:
        Player(int id,std::string name, std::string color);

        int getId() const noexcept { return id; }
        void setId(int newId) noexcept { id = newId; }

        const std::string &getName() const noexcept { return name; }
        void setName(const std::string &newName) { name = newName; }

        int getScore() const noexcept { return score; }
        void setScore(int newScore) noexcept { score = newScore; }

        int getExchange() const noexcept { return exchange; }
        void setExchange(int newExchange) noexcept { exchange = newExchange; }

        const std::string &getColor() const noexcept { return color; }
        void setColor(const std::string &newColor) { color = newColor; }



        //destructer !!!!
    };
} // Models
#endif //LAYING_GRASS_PROJECT_PLAYER_H