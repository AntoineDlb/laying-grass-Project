//
// Created by antoi on 02/11/2025.
//

#include "../../include/models/Tile.h"
#include <stdexcept>
#include <algorithm>

namespace Models {
    Tile::Tile(int id, std::vector<std::vector<Cell>>& pattern) : id(id), pattern(pattern) {
        this->height = pattern.size();
        this->width = pattern.empty() ? 0 : pattern[0].size();
    }

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

    Tile Tile::createTile(int id) {
        std::ifstream file("Tiles.json");
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open Tiles.json file");
        }

        nlohmann::json data = nlohmann::json::parse(file);
        file.close();

        if (data.is_null() || !data.contains("tiles")) {
            throw std::runtime_error("Invalid JSON format: missing 'tiles' key");
        }

        for (const auto& tileJson : data["tiles"]) {
            if (tileJson["id"] == id) {
                return convertJsonToTile(tileJson);
            }
        }

        throw std::out_of_range("Tile with id " + std::to_string(id) + " not found");
    }

    void Tile::rotate() {
        int oldHeight = height;
        int oldWidth = width;

        std::vector<std::vector<Cell>> rotatedPattern(oldWidth, std::vector<Cell>(oldHeight));

        for (int y = 0; y < oldHeight; ++y) {
            for (int x = 0; x < oldWidth; ++x) {
                rotatedPattern[x][oldHeight - 1 - y] = pattern[y][x];
            }
        }

        pattern = rotatedPattern;
        width = oldHeight;
        height = oldWidth;
    }

    void Tile::flipHorizontal() {
        for (int y = 0; y < height; ++y) {
            std::reverse(pattern[y].begin(), pattern[y].end());
        }
    }

} // Models