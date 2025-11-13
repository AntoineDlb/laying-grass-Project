//
// Created by antoi on 02/11/2025.
//

#include "../../include/utils/Random.h"
#include <random>

namespace Utils {
    int Random::getInt(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
} // Utils