#pragma once

#include <windows.h>
#include <string>

using namespace std;

#define MAX_SIZE_SNAKE 100
#define MAX_SIZE_FOOD 3
#define DEFAULT_SNAKE_LENGTH 6
#define MAX_SPEED 6

extern const string ID_STRING;
extern const int ID_LEN;

struct POINT2 {
    int x;
    int y;
};

extern POINT2 snake[MAX_SIZE_SNAKE];
extern POINT2 food[MAX_SIZE_FOOD];

extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE;
extern int WIDTH_CONSOLE;
extern int FOOD_INDEX;
extern int SIZE_SNAKE;
extern int STATE;

extern POINT2 GATE_POINT;
extern int IS_GATE_ACTIVE;
extern int OriginalSnakeSize;
extern HANDLE handle_t1;

extern char snake_chars[MAX_SIZE_SNAKE];

// Utility functions (in util.cpp)
void GotoXY(int x, int y);
void DrawBoard(int x, int y, int width, int height);
void ShowCursor(bool show);
void PauseGame(HANDLE t);
void ExitGame(HANDLE t);

// Game functions (in game.cpp)
bool IsValid(int x, int y);
void GenerateFood();
void GenerateGate();
void Draw(const char* str);
bool CheckSelfBite(int nextX, int nextY);
void ProcessDead();

void ResetData(int initialSize = DEFAULT_SNAKE_LENGTH);
void UpdateSnakeBodyNormal();
void Eat();
void ProcessGatePass(int nextX, int nextY);
void ProcessLevelUp();

void MoveRight();
void MoveLeft();
void MoveUp();
void MoveDown();

void ThreadFunc();
void StartGame();
