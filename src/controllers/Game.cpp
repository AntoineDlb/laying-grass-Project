//
// Created by antoi on 02/11/2025.
//

#include "../../include/controllers/Game.h"
#include <iostream>
#include <limits>

namespace Controllers {

    void Game::initGame() {
        std::cout << "Bienvenue dans Laying grass\n";

        int nb = 0;
        while (true) {
            std::cout << "Nombre de joueurs (2-9) : ";
            if ((std::cin >> nb) && nb > 0) break;
            std::cout << "Veuillez entrer un nombre de joueurs valide.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        players.clear();
        for (int i = 0; i < nb; ++i) {
            std::string name;
            std::cout << "Pseudo du joueur " << (i + 1) << " : ";
            std::getline(std::cin, name);
            if (name.empty()) name = "Joueur" + std::to_string(i + 1);
            players.emplace_back(i + 1, name, "");
        }

        std::cout << nb << " joueur(s) créé(s) :\n";
        for (const auto &p : players) {
            std::cout << " - [" << p.getId() << "] " << p.getName() << '\n';
        }
    }

} // Controllers