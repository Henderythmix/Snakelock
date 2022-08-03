#include <raylib.h>

#include "title.hpp"

void title::draw() {
    DrawText("Snakelock", 12, 12, 64, GRAY);
    DrawText("Snakelock", 10, 10, 64, WHITE);
    title::PlayButton.Draw();

    DrawText("WASD - move\nTAB - restart\nSPACE - START", 10, 120, 16, WHITE);

    if (title::Completed) DrawText("Thank you for playing", 10, 600-32, 16, YELLOW);
    DrawText("By Henderythmix for Untitled Game Jam #65", 10, 600-16, 16, WHITE);
}

void title::update() {
    title::PlayButton.Update(&title::LoadLevels);
}

void title::LoadLevels() {
    *title::ScenePtr = 1;
}