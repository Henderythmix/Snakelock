#ifndef TITLESCREEN
#define TITLESCREEN

#include <draygui.hpp>

namespace title {
    inline draygui::Button PlayButton((char*)"Play Game", 10, 74, 200, 34);
    //inline draygui::Button PuzzlesButton((char*)"Puzzle Mode", 10, 116, 220, 32);

    inline int* ScenePtr;
    inline bool Completed = false;

    void draw();
    void update();

    void LoadLevels();
}

#endif