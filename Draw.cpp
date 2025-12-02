#include "draw.h"
#include "system.h"
#include "global.h"
#include <iostream>
using namespace std;

void DrawBoard(int x, int y, int width, int height)
{
    GotoXY(x, y); printf("%c", 201);
    for (int i = 1; i < width; i++)
        printf("%c", 205);
    printf("%c", 187);

    for (int i = 1; i < height; i++)
    {
        GotoXY(x, y + i); printf("%c", 186);
        GotoXY(x + width, y + i); printf("%c", 186);
    }

    GotoXY(x, y + height); printf("%c", 200);
    for (int i = 1; i < width; i++)
        printf("%c", 205);
    printf("%c", 188);
}

void Draw(const char* str)
{
    if (!IS_GATE_ACTIVE) {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        printf(str);
    }

    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);

        if (strcmp(str, " ") == 0) printf(" ");
        else printf("%c", snake_chars[i]);
    }

    if (IS_GATE_ACTIVE)
    {
        GotoXY(GATE_POINT.x, GATE_POINT.y);
        printf("|");
    }
}
