#include <iostream>
#include "raylib.h"

int main()
{
    // Das Window definieren
    int screenWidth{1000};
    int screenHeight{800};
    InitWindow(screenWidth, screenHeight, "SnakeGamey");
    SetTargetFPS(60);
    //Background color define


    while(!WindowShouldClose())
    {
        // Game inhalt. Also alle bedingungen

        //Drawing, also auf dem Hintergeund malen
        BeginDrawing();
        Color BackgroundColor{254, 234, 250, 100};
        ClearBackground(BackgroundColor);

        EndDrawing();
    }

    CloseWindow();

    return 0;

}
