//
// Created by antoi on 02/11/2025.
//

#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

#include "Position.h"
#include "Cell.h"

#ifndef LAYING_GRASS_PROJECT_TILE_H
#define LAYING_GRASS_PROJECT_TILE_H

namespace Models {
    class Tile {
    private:
        int id;
        std::vector<std::vector<Cell>> pattern;
        int width;
        int height;
        int size = 0;
        bool placed;
    public:
        Tile();
        Tile(int id, std::vector<std::vector<Cell>>& pattern);

        int const getId(){ return id; }
        void setId(int id){ this->id = id;}

        int const getWidth(){ return width;}
        void setWidth(int w){ width = w; }

        int const getHeight(){ return height; }
        void setHeight(int h){ height = h; }

        int const getSize();


        bool isPlaced(){ return placed; }

        static Tile convertJsonToTile(const nlohmann::json& j);

        std::vector<std::vector<Cell>> getPattern(){return pattern;};











    };
} // Models

#endif //LAYING_GRASS_PROJECT_TILE_H