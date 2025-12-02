//#include "Menu.h"
//#include "Global.h"
//#include "Console.h"
//
//int ShowMenu()
//{
//    system("cls");
//    ShowCursor(false);
//
//    int center_x = (WIDTH_CONSOLE + 5) / 2;
//    int center_y = HEIGH_CONSOLE / 2;
//
//    string options[] = {
//     "1. START",
//     "2. ABOUT",
//     "3. HIGH SCORE",
//     "4. LOAD",
//     "5. SETTINGS",
//     "6. EXIT"
//    };
//
//
//    int selected_option = 0;
//    int num_options = 3;
//
//    while (1)
//    {
//        GotoXY(center_x - 12, center_y - 4);
//        printf("--- THE HUNTING SNAKE ---");
//
//        for (int i = 0; i < num_options; i++)
//        {
//            GotoXY(center_x - 5, center_y + i);
//            printf("%s %s", (i == selected_option ? ">>" : "  "), options[i].c_str());
//        }
//
//        char key = toupper(_getch());
//
//        if (key == 'W') selected_option = (selected_option - 1 + num_options) % num_options;
//        else if (key == 'S') selected_option = (selected_option + 1) % num_options;
//        else if (key == 13) return selected_option + 1;
//        else if (key == 27) return 3;
//    }
//}


#include "Menu.h"
#include "Global.h"
#include "Console.h"

int ShowMenu()
{
    system("cls");
    ShowCursor(false);

    int center_x = (WIDTH_CONSOLE + 5) / 2;
    int center_y = HEIGH_CONSOLE / 2;

    string options[] = {
     "1. START",
     "2. ABOUT",
     "3. HIGH SCORE",
     "4. LOAD",
     "5. SETTINGS",
     "6. EXIT"
    };

    int selected_option = 0;
    int num_options = 6;

    while (1)
    {
        system("cls");
        GotoXY(center_x - 12, center_y - 6);
        printf("--- THE HUNTING SNAKE ---");
        for (int i = 0; i < num_options; i++)
        {
            GotoXY(center_x - 8, center_y - 2 + i);
            printf("%s %s", (i == selected_option ? ">>" : "  "), options[i].c_str());
        }
        GotoXY(center_x - 16, center_y + 6);
        printf("W/S: chon   SPACE/ENTER: xac nhan   ESC: thoat");

        char key = toupper(_getch());
        if (key == 'W') selected_option = (selected_option - 1 + num_options) % num_options;
        else if (key == 'S') selected_option = (selected_option + 1) % num_options;
        else if (key == 13 || key == ' ') return selected_option + 1;
        else if (key == 27) return 6; // Exit
    }
}
