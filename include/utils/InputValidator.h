//
// Created by antoi on 02/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_INPUTVALIDATOR_H
#define LAYING_GRASS_PROJECT_INPUTVALIDATOR_H

#include <iostream>
#include <vector>

namespace Utils {
    class InputValidator {
    private:
        std::vector<std::string> colors = {"white", "light_blue", "dark_blue", "yellow", "orange", "purple", "pink", "brown", "black" };
        std::vector<std::string> takenColors;
    public:
        static bool isValidNumberOfPlayers(int numPlayers);
        static bool isValidPlayerName(const std::string& name);
        static bool isValidPlayerColor(const std::string& color);

        std::vector<std::string> getAvailableColors();
        std::string selectColor(int colorIndex);
    };
} // Utils

#endif //LAYING_GRASS_PROJECT_INPUTVALIDATOR_H