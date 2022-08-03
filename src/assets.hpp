#ifndef ASSETS
#define ASSETS

#define WORLDBLUE (Color){148, 171, 194}

namespace Assets {
    namespace Images {
        inline Texture2D Tileset;
        inline Texture2D Snake;
        inline Texture2D Blocks;
        inline Image Icon;
    }

    namespace Audio {
        inline Sound Blip;
    }

    inline void Load();
}

void Assets::Load() {
    Assets::Images::Tileset = LoadTexture("assets/tileset.png");
    Assets::Images::Snake = LoadTexture("assets/snake.png");
    Assets::Images::Blocks = LoadTexture("assets/boxes.png");
    Assets::Images::Icon = LoadImage("assets/icon.png");

    Assets::Audio::Blip = LoadSound("assets/Blip.ogg");
}

#endif