#include "SaveLoad.h"
#include "Global.h"
#include "Console.h"
#include "Board.h"
#include "Snake.h"
#include "ThreadControl.h"


bool LoadGame()
{
    ifstream fin(SAVE_FILE_NAME);

    if (!fin.is_open())
    {
        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Save file not found!");
        _getch();
        return false;
    }

    int moving_int, lock_int;
    fin >> SPEED >> FOOD_INDEX >> SIZE_SNAKE >> moving_int >> lock_int >> IS_GATE_ACTIVE >> OriginalSnakeSize;
    MOVING = (char)moving_int;
    CHAR_LOCK = (char)lock_int;

    for (int i = 0; i < SIZE_SNAKE; i++)
        fin >> snake[i].x >> snake[i].y >> snake_chars[i];

    for (int i = 0; i < MAX_SIZE_FOOD; i++)
        fin >> food[i].x >> food[i].y;

    fin >> GATE_POINT.x >> GATE_POINT.y;
    fin.close();

    system("cls");
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
    STATE = 1;

    return true;
}

void SaveGame()
{
    PauseGame(handle_t1);

    ofstream fout(SAVE_FILE_NAME);

    if (!fout.is_open())
    {
        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Save error!");
        ResumeThread(handle_t1);
        return;
    }

    fout << SPEED << endl;
    fout << FOOD_INDEX << endl;
    fout << SIZE_SNAKE << endl;
    fout << (int)MOVING << endl;
    fout << (int)CHAR_LOCK << endl;
    fout << IS_GATE_ACTIVE << endl;
    fout << OriginalSnakeSize << endl;

    for (int i = 0; i < SIZE_SNAKE; i++)
        fout << snake[i].x << " " << snake[i].y << " " << snake_chars[i] << endl;

    for (int i = 0; i < MAX_SIZE_FOOD; i++)
        fout << food[i].x << " " << food[i].y << endl;

    fout << GATE_POINT.x << " " << GATE_POINT.y << endl;
    fout.close();

    GotoXY(0, HEIGH_CONSOLE + 3);
    printf("Game saved! Press any key...");
    _getch();

    ResumeThread(handle_t1);
}
