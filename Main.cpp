//#include "Header.h"
//#include "Global.h"
//#include "Menu.h"
//#include "Game.h"
//#include "SaveLoad.h"
//#include "ThreadControl.h"
//#include "Console.h"
//
//int main()
//{
//    int choice;
//    thread t1;
//
//    WIDTH_CONSOLE = 50;
//    HEIGH_CONSOLE = 20;
//
//    do
//    {
//        choice = ShowMenu();
//
//        if (choice == 1)
//        {
//            StartGame();
//        }
//        else if (choice == 2)
//        {
//            if (!LoadGame()) continue;
//        }
//        else
//        {
//            system("cls");
//            printf("Goodbye. See you again.\n");
//            break;
//        }
//
//        if (!t1.joinable())
//        {
//            t1 = thread(ThreadFunc);
//            handle_t1 = t1.native_handle();
//        }
//        else
//        {
//            ResumeThread(handle_t1);
//            STATE = 1;
//        }
//
//        char temp;
//        while (STATE == 1)
//        {
//            temp = toupper(_getch());
//
//            if (temp == 'P') PauseGame(handle_t1);
//            else if (temp == 'Z') SaveGame();
//            else if (temp == 'X')
//            {
//                PauseGame(handle_t1);
//                LoadGame();
//                ResumeThread(handle_t1);
//            }
//            else if (temp == 27)
//            {
//                ExitGame(handle_t1);
//                STATE = 0;
//            }
//            else
//            {
//                ResumeThread(handle_t1);
//
//                if ((temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') && temp != CHAR_LOCK)
//                {
//                    if (temp == 'D') CHAR_LOCK = 'A';
//                    else if (temp == 'A') CHAR_LOCK = 'D';
//                    else if (temp == 'W') CHAR_LOCK = 'S';
//                    else if (temp == 'S') CHAR_LOCK = 'W';
//
//                    MOVING = temp;
//                }
//            }
//        }
//
//        GotoXY(0, HEIGH_CONSOLE + 3);
//        printf("Press M to return to Menu, or any key to exit.");
//        char exit_choice = toupper(_getch());
//
//        if (exit_choice != 'M') break;
//
//    } while (true);
//
//    if (t1.joinable()) t1.detach();
//    return 0;
//}

#include "Header1.h"
#include "Global.h"
#include "Menu.h"
#include "Game.h"
#include "SaveLoad.h"
#include "ThreadControl.h"
#include "Console.h"
#include "About.h"
#include "HighScore.h"
#include "Level.h"
#include "Settings.h"

int main()
{
    int choice;
    thread t1;

    WIDTH_CONSOLE = 50;
    HEIGH_CONSOLE = 20;

    do
    {
        choice = ShowMenu();

        if (choice == 1)            // START
        {
            StartGame();
        }
        else if (choice == 2)       // ABOUT
        {
            ShowAbout();
            continue;
        }
        else if (choice == 3)       // HIGH SCORE
        {
            ShowHighScores();
            continue;
        }
        else if (choice == 4)       // LOAD
        {
            if (!LoadGame()) continue;
        }
        else if (choice == 5)       // SETTINGS
        {
            ShowSettings();
            continue;
        }
        else                        // EXIT
        {
            system("cls");
            printf("Goodbye. See you again.\n");
            break;
        }

        if (!t1.joinable())
        {
            t1 = thread(ThreadFunc);
            handle_t1 = t1.native_handle();
        }
        else
        {
            ResumeThread(handle_t1);
            STATE = 1;
        }

        // HUD đơn giản
        GotoXY(2, HEIGH_CONSOLE + 1); printf("Level: %d  Speed: %d  Score: %d", LEVEL, SPEED, SCORE);
        GotoXY(2, HEIGH_CONSOLE + 2); printf("[P]Pause [Z]Save [ESC]Menu");

        char temp;
        while (STATE == 1)
        {
            temp = toupper(_getch());

            if (temp == 'P') PauseGame(handle_t1);
            else if (temp == 'Z') SaveGame();

            else if (temp == 27)
            {
                ExitGame(handle_t1);
                STATE = 0;
            }
            else
            {
                ResumeThread(handle_t1);

                if ((temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') && temp != CHAR_LOCK)
                {
                    if (temp == 'D') CHAR_LOCK = 'A';
                    else if (temp == 'A') CHAR_LOCK = 'D';
                    else if (temp == 'W') CHAR_LOCK = 'S';
                    else if (temp == 'S') CHAR_LOCK = 'W';

                    MOVING = temp;
                }
            }

            // cập nhật HUD
            GotoXY(2, HEIGH_CONSOLE + 1); printf("Level: %d  Speed: %d  Score: %d", LEVEL, SPEED, SCORE);
            GotoXY(2, HEIGH_CONSOLE + 2); printf("[P]Pause [Z]Save [ESC]Menu");
        }

        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Press M to return to Menu, or any key to exit.");
        char exit_choice = toupper(_getch());

        if (exit_choice != 'M') break;

    } while (true);

    if (t1.joinable()) t1.detach();
    return 0;
}
