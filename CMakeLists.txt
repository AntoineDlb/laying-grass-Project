cmake_minimum_required(VERSION 4.0)
project(laying_grass_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(laying_grass_Project src/main.cpp
        src/models/Cell.cpp
        include/models/Cell.h
        src/models/Player.cpp
        include/models/Player.h
        src/models/Board.cpp
        include/models/Board.h
        src/models/Tile.cpp
        include/models/Tile.h
        src/models/TileQueue.cpp
        include/models/TileQueue.h
        src/models/BonusSquare.cpp
        include/models/BonusSquare.h
        src/models/Position.cpp
        include/models/Position.h
        src/controllers/Game.cpp
        include/controllers/Game.h
        src/utils/SquareCalculator.cpp
        include/utils/SquareCalculator.h
        src/utils/InputValidator.cpp
        include/utils/InputValidator.h
        src/utils/Random.cpp
        include/utils/Random.h
        tests/test_tile.cpp
        tests/test_board.cpp
        tests/test_square_calculator.cpp
        src/views/UI_Cli.cpp
        include/views/UI_Cli.h
        src/views/UI_Qt.cpp
        include/views/UI_Qt.h)
