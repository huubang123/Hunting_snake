//#include "Game.h"
//#include "Global.h"
//#include "Console.h"
//#include "Board.h"
//#include "Move.h"
//#include "Snake.h"
//#include "ThreadControl.h"
//
//void ThreadFunc()
//{
//    while (1)
//    {
//        if (STATE == 1)
//        {
//            Draw(" ");
//            switch (MOVING)
//            {
//            case 'A': MoveLeft(); break;
//            case 'D': MoveRight(); break;
//            case 'W': MoveUp(); break;
//            case 'S': MoveDown(); break;
//            }
//            if (STATE == 1) Draw("O");
//
//            Sleep(1000 / SPEED);
//        }
//    }
//}
//
//void StartGame()
//{
//    system("cls");
//    ShowCursor(false);
//
//    WIDTH_CONSOLE = 50;
//    HEIGH_CONSOLE = 20;
//
//    ResetData(DEFAULT_SNAKE_LENGTH);
//
//    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
//    STATE = 1;
//}

#include "Game.h"
#include "Global.h"
#include "Console.h"
#include "Board.h"
#include "Move.h"
#include "Snake.h"
#include "ThreadControl.h"
#include "Level.h"

static void DrawHUD() {

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COL_DEFAULT);

    GotoXY(2, HEIGH_CONSOLE + 1);
    printf("Level: %d  Speed: %d  Score: %d    ", LEVEL, SPEED, SCORE);

    GotoXY(2, HEIGH_CONSOLE + 2);
    printf("[P]Pause [Z]Save [X]Load [ESC]Menu      ");
}

void ThreadFunc()
{
    while (1)
    {
        if (STATE == 1)
        {
            // update object LV4
            if (LEVEL == 4) UpdateMovingObject();

            Draw(" ");
            switch (MOVING)
            {
            case 'A': MoveLeft(); break;
            case 'D': MoveRight(); break;
            case 'W': MoveUp(); break;
            case 'S': MoveDown(); break;
            }
            if (STATE == 1) Draw("O");
            DrawHUD();
            Sleep(1000 / SPEED);
        }
    }
}

void StartGame()
{
    system("cls");
    ShowCursor(false);

    WIDTH_CONSOLE = 50;
    HEIGH_CONSOLE = 20;

    LEVEL = 1;               // bắt đầu từ level 1
    SCORE = 0;
    FOODS_EATEN_IN_LEVEL = 0;
    IS_GATE_ACTIVE = 0;

    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
    SetLevel(LEVEL);
    ResetData(DEFAULT_SNAKE_LENGTH);
    DrawLevel();
    DrawHUD();
    STATE = 1;
}
