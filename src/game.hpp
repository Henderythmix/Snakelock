#ifndef GAMEPLAY
#define GAMEPLAY

namespace Game {
    class Level;
    class Snake;
    class Block;
}

class Game::Snake {
    public:
        int X[100];
        int Y[100];
        int HeadDirection;
        int length;

        float movetime;

        bool crash;

        void Move();

        void Draw(int rx, int ry);
        void Update(char* map, int mw, int mh);
        
        Snake(int l, int startx, int starty, int dir);
};

class Game::Block {
    public:
        // These blocks have two positions.
        // index 0 is the current position
        // index 1 is the goal position
        int X[2];
        int Y[2];

        bool inSlot = false;

        bool PlayedSound = false;

        void Draw(int topleftx, int toplefty);
        void Update(Game::Snake player, bool* crash, char* map, int mw, int mh);

        Block() {};
        Block(int startx, int starty, int goalx, int goaly) {
            X[0] = startx;
            X[1] = goalx;
            Y[0] = starty;
            Y[1] = goaly;
        }
};

class Game::Level {
    public:
        char* Map;
        int width;
        int height;

        bool Running = false;
        bool Complete = false;
        float CountingTimer = 0;

        Game::Snake player;
        Game::Block blocks[10] = {};
        int BlockCount = 0;

        void Draw(std::string LevelName);
        void Update(void* exitCallback, void* resetCallback, void* winCallback);

        void InitBlockData(int blocks[], int blockcount);
        
        Level(int w, int h, char* mapdata, Game::Snake Snake) : player(Snake), Map(mapdata), width(w), height(h) {};
};

#endif