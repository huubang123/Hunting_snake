//#include "Move.h"
//#include "Snake.h"
//#include "Global.h"
//#include "Console.h"
//#include "Food.h"
//#include "Gate.h"
//#include "ThreadControl.h"
//
//
//
//bool CheckSelfBite(int nextX, int nextY)
//{
//    for (int i = 0; i < SIZE_SNAKE - 1; i++)
//        if (nextX == snake[i].x && nextY == snake[i].y) return true;
//    return false;
//}
//
//void UpdateSnakeBodyNormal()
//{
//    GotoXY(snake[0].x, snake[0].y);
//    printf(" ");
//
//    for (int i = 0; i < SIZE_SNAKE - 1; i++)
//        snake[i] = snake[i + 1];
//}
//
//void MoveRight()
//{
//    int nextX = snake[SIZE_SNAKE - 1].x + 1;
//    int nextY = snake[SIZE_SNAKE - 1].y;
//
//    if (nextX >= WIDTH_CONSOLE || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }
//    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x) { ProcessGatePass(nextX, nextY); return; }
//    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x) { Eat(); return; }
//
//    UpdateSnakeBodyNormal();
//    snake[SIZE_SNAKE - 1] = { nextX, nextY };
//}
//
//
//
//void MoveLeft()
//{
//    int nextX = snake[SIZE_SNAKE - 1].x - 1;
//    int nextY = snake[SIZE_SNAKE - 1].y;
//
//    if (nextX <= 0 || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }
//    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x) { ProcessGatePass(nextX, nextY); return; }
//    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x) { Eat(); return; }
//
//    UpdateSnakeBodyNormal();
//    snake[SIZE_SNAKE - 1] = { nextX, nextY };
//}
//
//void MoveUp()
//{
//    int nextX = snake[SIZE_SNAKE - 1].x;
//    int nextY = snake[SIZE_SNAKE - 1].y - 1;
//
//    if (nextY <= 0 || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }
//    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x) { ProcessGatePass(nextX, nextY); return; }
//    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x) { Eat(); return; }
//
//    UpdateSnakeBodyNormal();
//    snake[SIZE_SNAKE - 1] = { nextX, nextY };
//}
//
//void MoveDown()
//{
//    int nextX = snake[SIZE_SNAKE - 1].x;
//    int nextY = snake[SIZE_SNAKE - 1].y + 1;
//
//    if (nextY >= HEIGH_CONSOLE || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }
//    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x) { ProcessGatePass(nextX, nextY); return; }
//    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x) { Eat(); return; }
//
//    UpdateSnakeBodyNormal();
//    snake[SIZE_SNAKE - 1] = { nextX, nextY };
//}




#include "Move.h"
#include "Snake.h"
#include "Global.h"
#include "Console.h"
#include "Food.h"
#include "Gate.h"
#include "ThreadControl.h"
#include "Level.h"

// Kiểm tra rắn tự cắn
bool CheckSelfBite(int nextX, int nextY)
{
    for (int i = 0; i < SIZE_SNAKE - 1; i++)
        if (nextX == snake[i].x && nextY == snake[i].y) return true;
    return false;
}

// Dịch thân rắn bình thường (không ăn, không qua cổng)
static void UpdateSnakeBodyNormal()
{
    GotoXY(snake[0].x, snake[0].y);
    printf(" ");

    for (int i = 0; i < SIZE_SNAKE - 1; i++)
        snake[i] = snake[i + 1];
}

// ===== Tiện ích va chạm =====
static bool HitsObstacleOrObject(int nx, int ny) {
    if (IsObstacle(nx, ny)) return true;
    if (LEVEL == 4 && nx == MOV_OBJ.x && ny == MOV_OBJ.y) return true;
    return false;
}

static bool HitsGate(int nx, int ny) {
    return IS_GATE_ACTIVE && nx == GATE_POINT.x && ny == GATE_POINT.y;
}

static bool HitsFood(int nx, int ny) {
    return (!IS_GATE_ACTIVE && nx == food[FOOD_INDEX].x && ny == food[FOOD_INDEX].y);
}

// ===== Di chuyển =====
void MoveRight()
{
    int nextX = snake[SIZE_SNAKE - 1].x + 1;
    int nextY = snake[SIZE_SNAKE - 1].y;

    if (nextX >= WIDTH_CONSOLE || CheckSelfBite(nextX, nextY) || HitsObstacleOrObject(nextX, nextY)) { ProcessDead(); return; }
    if (HitsGate(nextX, nextY)) { ProcessGatePass(nextX, nextY); return; }
    if (HitsFood(nextX, nextY)) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveLeft()
{
    int nextX = snake[SIZE_SNAKE - 1].x - 1;
    int nextY = snake[SIZE_SNAKE - 1].y;

    if (nextX <= 0 || CheckSelfBite(nextX, nextY) || HitsObstacleOrObject(nextX, nextY)) { ProcessDead(); return; }
    if (HitsGate(nextX, nextY)) { ProcessGatePass(nextX, nextY); return; }
    if (HitsFood(nextX, nextY)) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveUp()
{
    int nextX = snake[SIZE_SNAKE - 1].x;
    int nextY = snake[SIZE_SNAKE - 1].y - 1;

    if (nextY <= 0 || CheckSelfBite(nextX, nextY) || HitsObstacleOrObject(nextX, nextY)) { ProcessDead(); return; }
    if (HitsGate(nextX, nextY)) { ProcessGatePass(nextX, nextY); return; }
    if (HitsFood(nextX, nextY)) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveDown()
{
    int nextX = snake[SIZE_SNAKE - 1].x;
    int nextY = snake[SIZE_SNAKE - 1].y + 1;

    if (nextY >= HEIGH_CONSOLE || CheckSelfBite(nextX, nextY) || HitsObstacleOrObject(nextX, nextY)) { ProcessDead(); return; }
    if (HitsGate(nextX, nextY)) { ProcessGatePass(nextX, nextY); return; }
    if (HitsFood(nextX, nextY)) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}
