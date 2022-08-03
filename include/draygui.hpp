// DRayGUI is an alternative library to RayLib's raygui.
// It does more or less what raygui does, but in a more practical way for myself

#if !defined(DRAYGUI_STANDALONE)
    #include "raylib.h"
#endif

namespace draygui {
    class Button {
        public:
            int X;
            int Y;
            int Width;
            int Height;

            char* Text;

            void Draw() {
                DrawRectangle(X, Y, Width, Height, WHITE);
                DrawText(Text, X, Y, 32, BLACK);
            };

            void Update(void *callback) {
                if (IsMouseButtonPressed(0)) {
                    if (GetMouseX() > X && GetMouseX() < X + Width) {
                        if (GetMouseY() > Y && GetMouseY() < Y + Height) {
                            ((void(*)())callback)();
                        }
                    }
                }
            };

            Button(char* text, int x, int y, int w, int h) {
                Text = text;
                X = x;
                Y = y;
                Width = w;
                Height = h;
            }
    };
}