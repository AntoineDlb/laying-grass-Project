#include "../../include/utils/KeyboardInput.h"
#include <iostream>
#include <windows.h>

namespace Utils {
    KeyCode KeyboardInput::getKeyPressed() {
        int firstByte = _getch();
        if (firstByte == 224) {
            int secondByte = _getch();
            return mapSpecialKey(firstByte, secondByte);
        }
        switch (firstByte) {
            case 'R':
            case 'r':
                return KeyCode::ROTATE;
            case ' ':
                return KeyCode::CONFIRM;
            default:
                return KeyCode::UNKNOWN;
        }
    }

    KeyCode KeyboardInput::checkKeyPressed() {
        if (!_kbhit()) {
            return KeyCode::UNKNOWN;
        }
        return getKeyPressed();
    }

    KeyCode KeyboardInput::mapSpecialKey(int firstByte, int secondByte) {
        if (firstByte == 224) {
            switch (secondByte) {
                case 72: // UP arrow
                    return KeyCode::UP;
                case 80: // DOWN arrow
                    return KeyCode::DOWN;
                case 75: // LEFT arrow
                    return KeyCode::LEFT;
                case 77: // RIGHT arrow
                    return KeyCode::RIGHT;
                default:
                    return KeyCode::UNKNOWN;
            }
        }
    }
} // Utils
