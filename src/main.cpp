#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "models/Tile.h"
#include "models/Board.h"

void displayBoard();
void displayTile();
void testJson();

int main() {

    displayTile();

    return 0;
}

void displayBoard() {
    Models::Board board(2);
    int width = board.getWidth();
    int height = board.getHeight();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (board.getGrid()[y][x].getState()) {
                case Models::State::EMPTY:
                    std::cout << " . ";
                    break;
                case Models::State::GRASS:
                    std::cout << " # ";
                    break;
                case Models::State::BONUS:
                    std::cout << " B ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void displayTile() {
    Models::Tile tile = Models::Tile::createTile(44);
    int height = tile.getHeight();
    int width = tile.getWidth();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (tile.getPattern()[y][x].getState()) {
                case Models::State::EMPTY:
                    std::cout << " . ";
                    break;
                case Models::State::GRASS:
                    std::cout << " # ";
                    break;
                case Models::State::BONUS:
                    std::cout << " B ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

void testJson() {
    // Charger le fichier JSON
    std::ifstream file("Tiles.json");
    nlohmann::json data = nlohmann::json::parse(file);

    // Tester avec la première tuile
    nlohmann::json firstTile = data["tiles"][10];
    Models::Tile tile = Models::Tile::convertJsonToTile(firstTile);

    // Afficher pour vérifier
    std::cout << "ID: " << tile.getId() << std::endl;
    std::cout << "Pattern size: " << tile.getPattern().size() << "x"
              << tile.getPattern()[0].size() << std::endl;
    std::cout << "tile size : " << tile.getSize() << std::endl;
}