//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Tile.h"

namespace Models {
    Tile::Tile(int id, std::vector<std::vector<Cell>>& pattern) : id(id), pattern(pattern) {}

    int const Tile::getSize() {
        for (const auto& row : pattern) {
            for (const auto& cell : row) {
                if (cell.getState() == State::GRASS) {
                    size++;
                }

            }
        }
        return size;
    }

    Tile Tile::convertJsonToTile(const nlohmann::json &j) {
        int id = j["id"];

        std::vector<std::vector<Cell>> pattern;
        for (auto& row : j["pattern"]) {
            std::vector<Cell> cellRow;
            for (int value : row) {
                Cell cell;
                if (value == 1) {
                    cell.setState(State::GRASS);
                }
                cellRow.push_back(cell);
            }
            pattern.push_back(cellRow);
        }

        return Tile(id, pattern);
        }

} // Models