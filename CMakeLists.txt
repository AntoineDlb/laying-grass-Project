cmake_minimum_required(VERSION 4.0)
project(laying_grass_Project)

set(CMAKE_CXX_STANDARD 20)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(COMMON_SOURCES
        src/models/Cell.cpp
        src/models/Player.cpp
        src/models/Board.cpp
        src/models/Tile.cpp
        src/models/TileQueue.cpp
        src/models/BonusSquare.cpp
        src/models/Position.cpp
        src/controllers/Game.cpp
        src/controllers/TilePlacer.cpp
        src/utils/SquareCalculator.cpp
        src/utils/InputValidator.cpp
        src/utils/Random.cpp
        src/utils/KeyboardInput.cpp
        src/views/UI_Cli.cpp
        src/views/UI_Qt.cpp
)

add_executable(laying_grass_Project src/main.cpp
       ${COMMON_SOURCES})

configure_file(${CMAKE_SOURCE_DIR}/asserts/Tiles.json
        ${CMAKE_BINARY_DIR}/Tiles.json COPYONLY)

target_include_directories(laying_grass_Project PRIVATE include)

target_link_libraries(laying_grass_Project PRIVATE nlohmann_json::nlohmann_json)

file(GLOB TEST_FILES "tests/test_*.cpp")

if(TEST_FILES)
    add_executable(tests
            ${TEST_FILES}
            ${COMMON_SOURCES})
    target_include_directories(tests PRIVATE include)

    enable_testing()
    add_test(NAME all_tests COMMAND tests)
endif()
