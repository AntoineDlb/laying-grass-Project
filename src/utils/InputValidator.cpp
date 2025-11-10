//
// Created by antoi on 02/11/2025.
//

#include "../../include/utils/InputValidator.h"
#include <vector>

namespace Utils {
    bool InputValidator::isValidNumberOfPlayers(int numPlayers) {
        return numPlayers >= 2 && numPlayers <= 9;
    }

    bool InputValidator::isValidPlayerName(const std::string &name) {
        return !name.empty() && name.length() <= 20;
    }

    bool InputValidator::isValidPlayerColor(const std::string &color) {
        for (int i = 0; i < color.length(); ++i) {
            if (!isalpha(color[i])) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> InputValidator::getAvailableColors() {
        return colors;
    }

    std::string InputValidator::selectColor(int colorIndex) {
        if (colorIndex < 0 || colorIndex >= colors.size()) {
            return "";
        }

        std::string selectedColor = colors[colorIndex];
        colors.erase(colors.begin() + colorIndex);
        takenColors.push_back(selectedColor);

        return selectedColor;
    }
} // Utils