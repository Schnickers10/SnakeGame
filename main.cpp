#include <iostream>
#include "raylib.h"
#include <vector>

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

struct cell
{
    //stores position on the grid
    int x;
    int y;
};

class Snake
{
    public:
    std::vector<cell> body;
    int dirX;
    int dirY;

    Snake(int startX, int startY)
    {
        body.push_back({startX, startY}); //creating the head with the coordinates we put in, in main
        //now moving right
        dirX = 1;
        dirY = 0;
    }

    void move()
    {
        cell newHead = {
            body[0].x + dirX,
            body[0].y + dirY

        };

        body.insert(body.begin(), newHead); //making a new head to the snake
        body.pop_back(); //removing the last vectors so removing the tail, this makes it look like the snake is moving forwards
    }

    void grow()
    {
        body.push_back(body.back());
    }
};

//making the food
class Food
{
public:
    cell foodPos; //FoodPos.x is collumn FoodPos.y is row

    // spawing the food at random position and not make it spawn in the snake
    void spawnFood(std::vector<cell>& snakeBody) // we need the coordinates of the body of the snake so that we can make the body not spawn in it
    {
        while (true) //means it keeps repeating until we make it stop (with bool = false)
        {
            foodPos.x = GetRandomValue(0, cols - 1); //Making the food spawn at random place, the cols are like if you have 50 it only goes ot 49
            foodPos.y = GetRandomValue(0, rows - 1);//same thing

            bool onSnake = false; //we assume that the food isn't on a snake, this is a definition and creation of the value onSnake

            for(auto& part : snakeBody)//auto means searching for the type it is so the struct we made  cell part & means taking the real original and not a copy, with this we go through every two vector number parts of the snake and then can check it
            {
                if(part.x == foodPos.x && part.y == foodPos.y)//so if the coordinates of the vectors are the same this is true
                {
                    onSnake = true;
                    break;

                }

            }

            if (!onSnake) break;//this says that if we found a good spot we can stop trying and spawn the food, so this means food isn't on snake so if it is on the snake the loop repeates again and we get new values

        }

    }

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
