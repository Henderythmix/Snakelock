#include <raylib.h>
#include <iostream>

#include "game.hpp"
#include "assets.hpp"

#define MOVEFREQ 0.4

//-------------//
// SNAKE STUFF //
//-------------//

// Just some constant Rectangles to point to
Rectangle SnakeHead[] = {
    (Rectangle){64, 0, 16, 16}, // Right
    (Rectangle){48, 0, 16, 16}, // Down
    (Rectangle){48, 16, 16, 16}, // Left
    (Rectangle){64, 16, 16, 16} // Up
};

Rectangle SnakeCorner[] = {
    (Rectangle){0, 0, 16, 16}, // 0deg
    (Rectangle){16, 0, 16, 16}, // 90deg
    (Rectangle){0, 16, 16, 16}, // 180deg
    (Rectangle){16, 16, 16, 16} // 270deg
};

Rectangle SnakeLine[] = {
    (Rectangle){32, 0, 16, 16}, // Horizontal
    (Rectangle){32, 16, 16, 16} // Vertical
};

Rectangle SnakeTail[] = {
    (Rectangle){80, 16, 16, 16}, // Right
    (Rectangle){80, 0, 16, 16}, // Down
    (Rectangle){96, 0, 16, 16}, // Left
    (Rectangle){96, 16, 16, 16} // Up
};

// THE CONSTRUCTOR IS RIGHT HERE GAME::LEVEL::LEVEL!!!! WHAT DO YOU WANT FROM ME?!??!?!
// (╯°□°)╯︵ ┻━┻
// Nvm I just had to be a bit fancy about how I made my constructor for Game::Level lol
Game::Snake::Snake(int l, int startx, int starty, int dir) {
    length = l;
    HeadDirection = dir;
    crash = false;
    movetime = 0;

    for (int i=0; i < length; i++) {
        X[i] = startx;
        Y[i] = starty;
    }
}

void Game::Snake::Move() {
    // Move Body
    for (int i=length; i > 0; i--) {
        X[i] = X[i-1];
        Y[i] = Y[i-1];
    }

    // Move Head
    int velx = 0;
    int vely = 0;

    if (HeadDirection == 0) velx = 1;
    if (HeadDirection == 3) vely = -1;
    if (HeadDirection == 2) velx = -1;
    if (HeadDirection == 1) vely = 1;

    X[0] += velx;
    Y[0] += vely;

    // Adjust movement timer
    movetime -= MOVEFREQ;
}

void Game::Snake::Draw(int rx, int ry) {
    // Draw the snake of the body
    for (int i=1; i < length; i++) {
        Rectangle* BodyPiece = &SnakeLine[0]; // Default to Vertical Lines

        if (i == length - 1) { // Check if it is a tail
            if (Y[i] > Y[i-1]) BodyPiece = &SnakeTail[1];
            if (Y[i] < Y[i-1]) BodyPiece = &SnakeTail[3];
            if (X[i] < X[i-1]) BodyPiece = &SnakeTail[0];
            if (X[i] > X[i-1]) BodyPiece = &SnakeTail[2];
        } else {
            // Vertical Lines
            if (Y[i] > Y[i-1] && Y[i] < Y[i+1]) BodyPiece = &SnakeLine[1];
            if (Y[i] < Y[i-1] && Y[i] > Y[i+1]) BodyPiece = &SnakeLine[1];

            // Corners
            if (Y[i] < Y[i-1] && X[i] < X[i+1]) BodyPiece = &SnakeCorner[0];
            if (Y[i] < Y[i+1] && X[i] < X[i-1]) BodyPiece = &SnakeCorner[0];

            if (Y[i] < Y[i-1] && X[i] > X[i+1]) BodyPiece = &SnakeCorner[1];
            if (Y[i] < Y[i+1] && X[i] > X[i-1]) BodyPiece = &SnakeCorner[1];

            if (X[i] < X[i-1] && Y[i] > Y[i+1]) BodyPiece = &SnakeCorner[2];
            if (X[i] < X[i+1] && Y[i] > Y[i-1]) BodyPiece = &SnakeCorner[2];

            if (Y[i] > Y[i-1] && X[i] > X[i+1]) BodyPiece = &SnakeCorner[3];
            if (X[i] > X[i-1] && Y[i] > Y[i+1]) BodyPiece = &SnakeCorner[3];
        }

        DrawTextureTiled(Assets::Images::Snake, *BodyPiece, (Rectangle){rx+(X[i]*32), ry+(Y[i]*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
    }

    // Drawing the Head Last
    DrawTextureTiled(Assets::Images::Snake, SnakeHead[HeadDirection], (Rectangle){rx+(X[0]*32), ry+(Y[0]*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
}

void Game::Snake::Update(char* map, int mw, int mh) {
    // Starting by managing movement
    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && (Y[0] > Y[1] || Y[0] == Y[1])) HeadDirection = 1;
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (Y[0] < Y[1] || Y[0] == Y[1])) HeadDirection = 3;
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && (X[0] < X[1] || X[0] == X[1])) HeadDirection = 2;
    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && (X[0] > X[1] || X[0] == X[1])) HeadDirection = 0;

    movetime += GetFrameTime();
    if (movetime > MOVEFREQ) Move();

    // COLLISIONS //
    // Check if collision with border
    if (X[0] < 0 || X[0] >= mw || Y[0] < 0 || Y[0] >= mh) crash = true;

    // Check if collision with map tile
    char maptilevalue = map[(Y[0]*mw)+X[0]];
    if (maptilevalue == '0') crash = true;

    // Now we check for collisions with self
    for (int i=2; i < length; i++) {
        if (X[0] == X[i] && Y[0] == Y[i]) crash = true;
    }
}

//--------//
// BLOCKS //
//--------//

void Game::Block::Draw(int topleftx, int toplefty) {
    if (inSlot) DrawTextureTiled(Assets::Images::Blocks, (Rectangle){32, 0, 32, 16}, (Rectangle){topleftx+(X[1]*32), toplefty+(Y[1]*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
    else {
        DrawTextureTiled(Assets::Images::Blocks, (Rectangle){0, 0, 16, 16}, (Rectangle){topleftx+(X[0]*32), toplefty+(Y[0]*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
        DrawTextureTiled(Assets::Images::Blocks, (Rectangle){16, 0, 16, 16}, (Rectangle){topleftx+(X[1]*32), toplefty+(Y[1]*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
    }
}

void Game::Block::Update(Game::Snake player, bool* crash, char* map, int mw, int mh) {
    if (X[0] == X[1] && Y[0] == Y[1]) inSlot = true;

    if (!inSlot) {
        // The m stands for movement
        int mx = 0;
        int my = 0;
        if (player.X[0] == X[0] && player.Y[0] == Y[0]) {

            if (player.HeadDirection == 0) mx = 1;
            if (player.HeadDirection == 1) my = 1;
            if (player.HeadDirection == 2) mx = -1;
            if (player.HeadDirection == 3) my = -1;

            if (map[((Y[0]+my)*mw)+(X[0]+mx)] == '0') {
                *crash = true;
            } else if (X[0]+mx < 0 || X[0]+mx >= mw || Y[0]+my < 0 || Y[0]+my >= mh) {
                *crash = true;
            } else {
                X[0] += mx;
                Y[0] += my;
            }
        }
    } else {
        if (!PlayedSound) {
            PlaySoundMulti(Assets::Audio::Blip);
            PlayedSound = true;
        }
    }
}

//---------------//
// LEVEL GENERAL //
//---------------//

// probably the most redundant method of coding this in,
// but honestly it's not like I could find a fast and easy way here :man_shrugging:
// Yes I used a discord emote and I'm commenting like it's TF2 code. too bad!
void Game::Level::InitBlockData(int blockcoords[], int blockcount) {
    for (int i=0; i < blockcount; i++) {
        blocks[i] = Game::Block(blockcoords[i*4], blockcoords[i*4+1], blockcoords[i*4+2], blockcoords[i*4+3]);
    }
    BlockCount = blockcount;
}

void Game::Level::Draw(std::string LevelName) {
    // Drawing the Map
    int topleftx = 400 - width*16;
    int toplefty = 300 - height*16;
    
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            if (Map[(y*width)+x] == '1') {
                DrawTextureTiled(Assets::Images::Tileset, (Rectangle){0, 0, 16, 16}, (Rectangle){topleftx+(x*32), toplefty+(y*32), 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
                if (y==0 || Map[((y-1)*width)+x] == '0') {
                    DrawTextureTiled(Assets::Images::Tileset, (Rectangle){16, 0, 16, 16}, (Rectangle){topleftx+(x*32), toplefty+(y*32)-32, 32, 32}, (Vector2){0, 0}, 0, 2, WHITE);
                }
            }
        }
    }

    // Drawing the Game Blocks
    for (int i = 0; i < BlockCount; i++) {
        blocks[i].Draw(topleftx, toplefty);
    }

    // Drawing the Snake
    player.Draw(topleftx, toplefty);

    // Just some UI stuff
    std::string snakelength = "Snake Length: " + std::to_string(player.length);
    DrawText(LevelName.c_str(), 14, 14, 24, (Color){0, 0, 0, 100});
    DrawText(LevelName.c_str(), 10, 10, 24, WHITE);
    DrawText(snakelength.c_str(), 10, 34, 16, WHITE);

    if (Complete) {
        DrawText("Level Complete", 800/2-(64/7), 10, 48, WHITE);
        DrawText("Taking you to the next level", 800/2-(64/7), 58, 24, WHITE);
    }
}

void Game::Level::Update(void* exitCallback, void* resetCallback, void* winCallback) {
    // Update Snake first
    if (IsKeyPressed(KEY_SPACE)) {
        player.Move(); 
        Running = true; 
    }
    if (Running && !Complete) {
        player.Update(Map, width, height);
    }

    bool Levelcomplete = true;

    // lets get the blocks moving around!
    // I'm also going to use this for loop to check if all the blocks are in the certain spots
    for (int i=0; i < BlockCount; i++) {
        blocks[i].Update(player, &player.crash, Map, width, height);
        if (!blocks[i].inSlot) Levelcomplete = false;
    }

    // Check if the player completed the level
    if (Levelcomplete) {
        Complete = true;
    }

    if (Complete) CountingTimer += GetFrameTime();
    if (CountingTimer > 3) ((void(*)())winCallback)();

    // Now check if the player crashed or the level is reset
    if (player.crash || (IsKeyPressed(KEY_TAB) && !Complete)) {
        ((void(*)())resetCallback)();
    }

    // Just
    if (IsKeyPressed(KEY_ESCAPE)) {
        ((void(*)())exitCallback)();
    }
}