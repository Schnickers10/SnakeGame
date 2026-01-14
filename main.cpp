#include <iostream>
#include "raylib.h"

// Das Window definieren, constant, shouldn't change in the game
const int screenWidth{1000};
const int screenHeight{800};
const int cellSize{30};
const Color gridColor{239, 211, 215, 255};

const int cols{screenWidth/cellSize};
const int rows{screenHeight/cellSize};

//grid drawing function
void DrawGrid()
{
    for (int y = 0; y <= cols; y++)
    {
        DrawLine(y * cellSize, 0, y * cellSize, screenHeight, gridColor);
    }
    for (int x = 0; x <= rows; x++)
    {
        DrawLine(0, x * cellSize, screenWidth, x * cellSize, gridColor);
    }
}

//Snake definen
class Snake
{
public:
    int head;
    int tail;
    int body;

};


int main()
{
    // Game inhalt. Also alle bedingungen
    InitWindow(screenWidth, screenHeight, "SnakeGamey");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {

        //Drawing, also auf dem Hintergeund malen
        BeginDrawing();
        Color BackgroundColor{254, 234, 250, 255};
        ClearBackground(BackgroundColor);
        DrawGrid();

        EndDrawing();
    }

    CloseWindow();

    return 0;

}
