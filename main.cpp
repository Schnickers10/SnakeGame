#include <iostream>
#include "raylib.h"
#include <vector>

// Das Window definieren, constant, shouldn't change in the game
const int screenWidth{1000};
const int screenHeight{800};
const int cellSize{50};
const Color gridColor{239, 211, 215, 255};
const Color snakeColor{142, 154, 175, 255};

const int cols{screenWidth/cellSize};
const int rows{screenHeight/cellSize};

//food bild definen
Texture2D foodTexture;

//game over function
bool gameOver = false;

//playing or not playing gamestate
enum gameState
{
    PLAYING,
    GAME_OVER
};

gameState gamestate = PLAYING;

//score count
int score{0};

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

    int nextDirX;
    int nextDirY;

    bool growing{false};

    Snake(int startX, int startY)
    {
        body.push_back({startX, startY}); //creating the head with the coordinates we put in, in main
        //now moving right
        dirX = 1;
        dirY = 0;

        nextDirX = dirX;
        nextDirY = dirY;
    }

    void move()
    {
        dirX = nextDirX;
        dirY = nextDirY;

        cell newHead = {
            body[0].x + dirX,
            body[0].y + dirY

        };

        body.insert(body.begin(), newHead);

        if (!growing)
        {
            body.pop_back();
        }

        else
        {
            growing = false;
        }
        //puts a new head and takes the tail away, so that it looks like it's moving
    }

    void grow()
    {
        growing = true;
    }

    void changeDirection(int x, int y)
    {
        if (body.size() > 1 && x == -dirX && y == -dirY) return; //if the body size is more than one and the directions make 180 it would crash into its self so it returns so it doesn't happen
        nextDirX = x;
        nextDirY = y;

    }
    void draw()
    {
        for (auto& part : body)
        {
            DrawRectangle(part.x * cellSize, part.y * cellSize, cellSize, cellSize, snakeColor);
        }
    }

    bool wallCollision() const
    {
        return (body[0].x < 0 || body[0].x >= cols || body[0].y < 0 || body[0].y >= rows);
    }

    void selfCollision()
    {
        for (int i = 1; i < body.size(); i++)
        {
            if (body[0].x == body[i].x && body[0].y == body[i].y)
            {
                gamestate = GAME_OVER;
                return;
            }

        }
    }
};

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

            for(auto& part : snakeBody)//auto means searching for the type it is so the struct we made cell part & means taking the real original and not a copy, with this we go through every two vector number parts of the snake and then can check it
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

    void DrawFood(cell foodPos)
    {
        DrawTexturePro(
            foodTexture,
            Rectangle{0, 0, (float)foodTexture.width, (float)foodTexture.height},
            Rectangle{
            (float)foodPos.x * cellSize,
            (float)foodPos.y * cellSize,
            (float)cellSize,
            (float)cellSize
            },
            Vector2{0, 0},
            0.0f,
            WHITE
            );


    }

};

int main()
{
    // Game inhalt. Also alle bedingungen
    InitWindow(screenWidth, screenHeight, "SnakeGamey");
    SetTargetFPS(60);

    foodTexture = LoadTexture("Food.png");

    Snake snake(0, 0);
    Food food;

    food.spawnFood(snake.body);

    float moveTimer = 0.0f; //theWindowShouldClose! loop runs every 60 seconds. these are definitions. moveTimer = how much time has passed
    float moveDelay = 0.15f; //moveDelay = how much we wait before moving

    while(!WindowShouldClose())
    {
        if (gamestate == PLAYING)
        {
            //assigning the keys
            if (IsKeyPressed(KEY_UP))   snake.changeDirection(0, -1);
            if (IsKeyPressed(KEY_DOWN))   snake.changeDirection(0, 1);
            if (IsKeyPressed(KEY_LEFT))   snake.changeDirection(-1, 0);
            if (IsKeyPressed(KEY_RIGHT))   snake.changeDirection(1, 0);
            //Making the snake move
            moveTimer += GetFrameTime(); //short for moveTimer = moveTimer + GetFrameTime(); GetFrameTime gets ud the number of seconds since the last frame. at 60fps it is about 0.016. so, moveTimer = moveTimer + 0.016
            if (moveTimer >= moveDelay) //if enough time has passed since the last frame we can move the snake again. so it's always +0.016 until it is at 0.16 seconds and then the snake moves
            {
                snake.move();
                moveTimer = 0.0f;

                if (snake.body[0].x == food.foodPos.x && snake.body[0].y == food.foodPos.y)
                {
                    snake.grow();
                    food.spawnFood(snake.body);
                    score += 1;
                }

                if (snake.wallCollision()) {
                    gamestate = GAME_OVER;
                }

                snake.selfCollision();

            }
        }

        //Drawing, also auf dem Hintergeund malen
        BeginDrawing();
        Color BackgroundColor{254, 234, 250, 255};
        ClearBackground(BackgroundColor);
        DrawGrid();
        food.DrawFood(food.foodPos);
        snake.draw();

        if (gamestate == GAME_OVER)
        {
            DrawText("GAME OVER", screenWidth / 2 - 300, screenHeight / 2 - 30, 100, RED);
            DrawText(TextFormat("score: %i", score),screenWidth / 2 - 70, screenHeight / 2 + 50, 50, GREEN);

        }

        EndDrawing();
    }

    UnloadTexture(foodTexture);

    CloseWindow();

    return 0;

}
