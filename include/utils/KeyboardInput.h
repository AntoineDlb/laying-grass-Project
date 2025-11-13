//
// Created by antoi on 09/11/2025.
//

#ifndef LAYING_GRASS_PROJECT_KEYBOARDINPUT_H
#define LAYING_GRASS_PROJECT_KEYBOARDINPUT_H

#include <conio.h>

namespace Utils {
    enum class KeyCode {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ROTATE,
        FLIP,
        CONFIRM,
        UNKNOWN
    };

    class KeyboardInput {
    public:
        static KeyCode getKeyPressed();
        static KeyCode checkKeyPressed();

    private:
        static KeyCode mapSpecialKey(int firstByte, int secondByte);
    };
} // Utils

#endif //LAYING_GRASS_PROJECT_KEYBOARDINPUT_H


