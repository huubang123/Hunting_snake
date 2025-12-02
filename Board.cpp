#include "Board.h"
#include "Console.h"
#include "Global.h"

void DrawBoard(int x, int y, int width, int height)
{
    GotoXY(x, y); printf("%c", 201);
    for (int i = 1; i < width; i++)
    {
        GotoXY(x + i, y); printf("%c", 205);
    }
    GotoXY(x + width, y); printf("%c", 187);

    for (int i = 1; i < height; i++)
    {
        GotoXY(x, y + i); printf("%c", 186);
        GotoXY(x + width, y + i); printf("%c", 186);
    }

    GotoXY(x, y + height); printf("%c", 200);
    for (int i = 1; i < width; i++)
    {
        GotoXY(x + i, y + height); printf("%c", 205);
    }
    GotoXY(x + width, y + height); printf("%c", 188);
}

