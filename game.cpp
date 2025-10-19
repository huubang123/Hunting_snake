#include "game.h"
#include <iostream>
#include <stdio.h>
#include <thread>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <string.h>

using namespace std;

// constants and globals
const string ID_STRING = "2012033822120019";
const int ID_LEN = (int)ID_STRING.length();

POINT2 snake[MAX_SIZE_SNAKE];
POINT2 food[MAX_SIZE_FOOD];
int CHAR_LOCK;
int MOVING;
int SPEED;
int HEIGH_CONSOLE, WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int STATE;

POINT2 GATE_POINT;
int IS_GATE_ACTIVE = 0;
int OriginalSnakeSize = 0;
HANDLE handle_t1;

char snake_chars[MAX_SIZE_SNAKE];

bool IsValid(int x, int y) {
    if (x <= 0 || x >= WIDTH_CONSOLE || y <= 0 || y >= HEIGH_CONSOLE) return false;

    for (int i = 0; i < SIZE_SNAKE; i++) {
        if (x == snake[i].x && y == snake[i].y) return false;
    }

    if (IS_GATE_ACTIVE) {
        if (x == GATE_POINT.x && y == GATE_POINT.y) return false;
    }

    return true;
}

void GenerateFood() {
    int x, y;
    int attempt_limit = 1000;
    int attempts;

    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        attempts = 0;
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGH_CONSOLE - 1) + 1;
            attempts++;

            if (attempts > attempt_limit) {
                food[i] = { 0, 0 };
                break;
            }
        } while (IsValid(x, y) == false);

        if (attempts <= attempt_limit) {
            food[i] = { x, y };
        }
    }
}

void GenerateGate() {
    int gateX, gateY;
    int attempts = 0;

    do {
        gateX = rand() % (WIDTH_CONSOLE - 1) + 1;
        gateY = rand() % (HEIGH_CONSOLE - 1) + 1;
        attempts++;
        if (attempts > 1000) return;
    } while (!IsValid(gateX, gateY));

    GATE_POINT = { gateX, gateY };
    IS_GATE_ACTIVE = 1;
}

void Draw(const char* str) {
    if (IS_GATE_ACTIVE == 0) {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        printf(str);
    }

    for (int i = 0; i < SIZE_SNAKE; i++) {
        GotoXY(snake[i].x, snake[i].y);

        if (strcmp(str, " ") == 0) {
            printf(" ");
        }
        else {
            printf("%c", snake_chars[i]);
        }
    }

    if (IS_GATE_ACTIVE) {
        GotoXY(GATE_POINT.x, GATE_POINT.y);
        printf("|");
    }
}

bool CheckSelfBite(int nextX, int nextY) {
    for (int i = 0; i < SIZE_SNAKE - 1; i++) {
        if (nextX == snake[i].x && nextY == snake[i].y) return true;
    }
    return false;
}

void ProcessDead() {
    STATE = 0;
    GotoXY(0, HEIGH_CONSOLE + 2);
    printf("Game Over! Type Y to continue or any other key to exit.");
}

void ResetData(int initialSize) {
    SPEED = 4;
    srand((unsigned int)time(NULL));
    FOOD_INDEX = 0;

    MOVING = 'A';
    CHAR_LOCK = 'D';

    SIZE_SNAKE = initialSize;

    int centerX = WIDTH_CONSOLE / 2;
    int centerY = HEIGH_CONSOLE / 2;

    int safeY = (centerY < 3) ? 3 : centerY;
    safeY = (safeY > HEIGH_CONSOLE - 3) ? HEIGH_CONSOLE - 3 : safeY;

    int startX = centerX - (SIZE_SNAKE / 2);
    if (startX < 1) startX = 1;

    for (int i = 0; i < SIZE_SNAKE; i++) {
        snake[i].x = startX + i;
        snake[i].y = safeY;
        snake_chars[i] = ID_STRING[i % ID_LEN];
    }

    for (int i = 0; i < SIZE_SNAKE / 2; i++) {
        POINT2 temp_p = snake[i];
        snake[i] = snake[SIZE_SNAKE - 1 - i];
        snake[SIZE_SNAKE - 1 - i] = temp_p;

        char temp_c = snake_chars[i];
        snake_chars[i] = snake_chars[SIZE_SNAKE - 1 - i];
        snake_chars[SIZE_SNAKE - 1 - i] = temp_c;
    }

    GenerateFood();
}

void UpdateSnakeBodyNormal() {
    GotoXY(snake[0].x, snake[0].y);
    printf(" ");

    for (int i = 0; i < SIZE_SNAKE - 1; i++) {
        snake[i] = snake[i + 1];
        snake_chars[i] = snake_chars[i + 1];
    }
}

void Eat() {
    POINT2 old_tail_pos = snake[0];
    // shift everything right
    for (int i = SIZE_SNAKE - 1; i >= 0; i--) {
        snake[i + 1] = snake[i];
        snake_chars[i + 1] = snake_chars[i];
    }

    snake[0] = old_tail_pos;
    snake_chars[0] = ID_STRING[SIZE_SNAKE % ID_LEN];

    SIZE_SNAKE++;

    if (FOOD_INDEX == MAX_SIZE_FOOD - 1) {
        OriginalSnakeSize = SIZE_SNAKE;

        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        printf(" ");

        GenerateGate();
    }
    else {
        FOOD_INDEX++;
    }
}

void ProcessGatePass(int nextX, int nextY) {
    GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
    printf(" ");

    SIZE_SNAKE--;

    snake[SIZE_SNAKE].x = nextX;
    snake[SIZE_SNAKE].y = nextY;

    if (OriginalSnakeSize > 0 && SIZE_SNAKE == 0) {
        ProcessLevelUp();
    }
}

void ProcessLevelUp() {
    Sleep(500);
    system("cls");

    int sizeToKeep = OriginalSnakeSize;

    if (SPEED < MAX_SPEED) {
        SPEED++;
    }
    else {
        sizeToKeep = DEFAULT_SNAKE_LENGTH;
    }

    IS_GATE_ACTIVE = 0;
    OriginalSnakeSize = 0;

    ResetData(sizeToKeep);

    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
}

void MoveRight() {
    int nextX = snake[SIZE_SNAKE - 1].x + 1;
    int nextY = snake[SIZE_SNAKE - 1].y;

    if (nextX >= WIDTH_CONSOLE || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }

    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x && nextY == GATE_POINT.y) {
        ProcessGatePass(nextX, nextY); return;
    }

    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x && nextY == food[FOOD_INDEX].y) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveLeft() {
    int nextX = snake[SIZE_SNAKE - 1].x - 1;
    int nextY = snake[SIZE_SNAKE - 1].y;

    if (nextX <= 0 || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }

    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x && nextY == GATE_POINT.y) {
        ProcessGatePass(nextX, nextY); return;
    }

    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x && nextY == food[FOOD_INDEX].y) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveUp() {
    int nextX = snake[SIZE_SNAKE - 1].x;
    int nextY = snake[SIZE_SNAKE - 1].y - 1;

    if (nextY <= 0 || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }

    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x && nextY == GATE_POINT.y) {
        ProcessGatePass(nextX, nextY); return;
    }

    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x && nextY == food[FOOD_INDEX].y) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void MoveDown() {
    int nextX = snake[SIZE_SNAKE - 1].x;
    int nextY = snake[SIZE_SNAKE - 1].y + 1;

    if (nextY >= HEIGH_CONSOLE || CheckSelfBite(nextX, nextY)) { ProcessDead(); return; }

    if (IS_GATE_ACTIVE && nextX == GATE_POINT.x && nextY == GATE_POINT.y) {
        ProcessGatePass(nextX, nextY); return;
    }

    if (!IS_GATE_ACTIVE && nextX == food[FOOD_INDEX].x && nextY == food[FOOD_INDEX].y) { Eat(); return; }

    UpdateSnakeBodyNormal();
    snake[SIZE_SNAKE - 1] = { nextX, nextY };
}

void ThreadFunc() {
    while (1) {
        if (STATE == 1) {
            Draw(" ");
            switch (MOVING) {
            case 'A': MoveLeft(); break;
            case 'D': MoveRight(); break;
            case 'W': MoveUp(); break;
            case 'S': MoveDown(); break;
            }

            if (STATE == 1) {
                Draw("O");
            }

            Sleep(1000 / SPEED);
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void StartGame() {
    system("cls");
    ShowCursor(false);

    WIDTH_CONSOLE = 50;
    HEIGH_CONSOLE = 20;

    ResetData(DEFAULT_SNAKE_LENGTH);

    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
    STATE = 1;
}
