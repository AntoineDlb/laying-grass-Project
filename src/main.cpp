#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "models/Tile.h"

int main() {
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

    return 0;
}