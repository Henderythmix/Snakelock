#include <iostream>
using namespace std;

#include <raylib.h>

#include "assets.hpp"
#include "title.hpp"
#include "game.hpp"

// Gameplay Variables
int SceneNumber = 0;

int GameBlockData[5][40] = {
    {2, 2, 6, 2},
    {2, 4, 7, 7},
    {2, 6, 2, 7, 6, 6, 6, 7},
    {2, 1, 2, 4, 6, 1, 6, 4}
};
int BlockCounts[] = {1, 1, 2, 2};

Game::Level GameLevels[] = {
    Game::Level(8, 5, (char*)"1100001111111111111111111111111111000011", Game::Snake(3, 0, 2, 0)),
    Game::Level(9, 9, (char*)"111110000111110000111110000111110000111110000111110000111111111111111111111111111", Game::Snake(4, 2, 1, 1)),
    Game::Level(8, 8, (char*)"0011111100111111111100001111000011111111111111110011001100110011", Game::Snake(6, 7, 0, 2)),
    Game::Level(8, 5, (char*)"1111111011111111001000110010001100100011", Game::Snake(6, 0, 1, 0))

};
string LevelNames[] = {
    "The First Block",
    "Just Around the Corner",
    "Sus but ok ¯\\_(ツ)_/¯",
    "Wise Movement",
};

int levelnumber = 0;
Game::Level CurrentLevel = GameLevels[0];

// Level Loading //

void ResetLevel() {
    CurrentLevel = GameLevels[levelnumber];
    CurrentLevel.InitBlockData(GameBlockData[levelnumber], BlockCounts[levelnumber]);
}
void UpdateLevel() {
    levelnumber++;
    if (levelnumber > (sizeof(BlockCounts)/sizeof(int))-1) {
        SceneNumber = 0;
        levelnumber = 0;
        title::Completed = true;
    }
    CurrentLevel = GameLevels[levelnumber];
    CurrentLevel.InitBlockData(GameBlockData[levelnumber], BlockCounts[levelnumber]);
}
void MainMenu() {
    SceneNumber = 0;
    ResetLevel();
}

// Simplifying the GameLevel Functions
void DrawGameLevel() {
    CurrentLevel.Draw(to_string(levelnumber+1) + " - " + LevelNames[levelnumber]);
}

void UpdateGameLevel() {
    CurrentLevel.Update(&MainMenu, &ResetLevel, &UpdateLevel);
}

int main() {
    CurrentLevel.InitBlockData(GameBlockData[0], BlockCounts[0]);
    
    // Scene Management Arrays
    void* UpdateFunctions[] = {&title::update, &UpdateGameLevel};
    void* DrawFunctions[] = {&title::draw, &DrawGameLevel};

    title::ScenePtr = &SceneNumber;

    // Window Setup
    InitWindow(800, 600, "Snakelock");
    SetTargetFPS(60);
    InitAudioDevice();

    bool Running = true;

    Assets::Load();

    //SetWindowIcon(Assets::Images::Icon);

    // Honestly, main.cpp is really just a glue script to put everything together here
    // I wish I made it more organized tho, but oh well. too bad
    while (Running) {
        ((void(*)())UpdateFunctions[SceneNumber])();
        BeginDrawing();
        // Is Usually BLACK, but to simplify window filling, it's my own WORLDBLUE
        ClearBackground(WORLDBLUE);
        ((void(*)())DrawFunctions[SceneNumber])();
        EndDrawing();

        // Created my own Window Closing System
        if (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE)) {
            Running = false;
        }
    }

    StopSoundMulti();
    CloseWindow();

    return 0;
}
