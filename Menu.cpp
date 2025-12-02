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
#include <string>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void DrawOptionBox(int x, int y, int width, int height, int color) {
    SetColor(color);

    GotoXY(x, y); printf("%c", 201);
    for (int i = 0; i < width - 2; i++) printf("%c", 205);
    printf("%c", 187);

    for (int j = 1; j < height - 1; j++) {
        GotoXY(x, y + j); printf("%c", 186);
        GotoXY(x + 1, y + j);
        for (int i = 0; i < width - 2; i++) printf(" ");
        GotoXY(x + width - 1, y + j); printf("%c", 186);
    }

    GotoXY(x, y + height - 1); printf("%c", 200);
    for (int i = 0; i < width - 2; i++) printf("%c", 205);
    printf("%c", 188);
}

void DrawMenuSnake(int x, int y) {
    SetColor(SNAKE_COLOR);

    GotoXY(x + 6, y - 4); printf("%c%c%c%c%c%c", 220, 219, 223, 219, 219, 220);
    GotoXY(x + 5, y - 3); printf("%c%c%c%c%c%c", 219, 219, 219, 223, 223, 223);
    GotoXY(x + 4, y - 2); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 3, y - 1); printf("%c%c%c", 219, 219, 219);

    GotoXY(x + 4, y); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 5, y + 1); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 6, y + 2); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 7, y + 3); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 7, y + 4); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 6, y + 5); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 5, y + 6); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 4, y + 7); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 4, y + 8); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 5, y + 9); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 6, y + 10); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 7, y + 11); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 7, y + 12); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 6, y + 13); printf("%c%c%c", 219, 219, 223);
    GotoXY(x + 5, y + 14); printf("%c%c", 219, 223);

    SetColor(7);
}

void DrawTitle(int x, int y)
{
    //H
    GotoXY(x, y); printf("%c%c%c", 219,' ', 219);
    GotoXY(x, y + 1); printf("%c%c%c", 219, 220, 219);
    GotoXY(x, y + 2); printf("%c%c%c", 219, ' ', 219);
    //U
    GotoXY(x + 4, y); printf("%c%c%c", 219, ' ', 219);
    GotoXY(x + 4, y + 1); printf("%c%c%c", 219, ' ', 219);
    GotoXY(x + 4, y + 2); printf("%c%c%c", 219, 220, 219);
    //N
    GotoXY(x + 8, y); printf("%c%c%c", 219, 221, 219);
    GotoXY(x + 8, y + 1); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 8, y + 2); printf("%c%c%c", 219, 222, 219);
    //T
    GotoXY(x + 12, y); printf("%c%c%c", 223, 219, 223);
    GotoXY(x + 12, y + 1); printf("%c%c%c", ' ', 219, ' ');
    GotoXY(x + 12, y + 2); printf("%c%c%c", ' ', 219, ' ');
    //I
    GotoXY(x + 15, y); printf("%c%c%c", ' ', 219, ' ');
    GotoXY(x + 15, y + 1); printf("%c%c%c", ' ', 219, ' ');
    GotoXY(x + 15, y + 2); printf("%c%c%c", ' ', 219, ' ');
    //N
    GotoXY(x + 18, y); printf("%c%c%c", 219, 221, 219);
    GotoXY(x + 18, y + 1); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 18, y + 2); printf("%c%c%c", 219, 222, 219);
    //G
    GotoXY(x + 22, y); printf("%c%c%c", 219, 223, 223);
    GotoXY(x + 22, y + 1); printf("%c%c%c", 219, ' ', 220);
    GotoXY(x + 22, y + 2); printf("%c%c%c", 219, 220, 219);

    //S
    GotoXY(x + 30, y); printf("%c%c%c", 219, 223, 223);
    GotoXY(x + 30, y + 1); printf("%c%c%c", ' ', 219, ' ');
    GotoXY(x + 30, y + 2); printf("%c%c%c", 220, 220, 219);
    //N
    GotoXY(x + 34, y); printf("%c%c%c", 219, 221, 219);
    GotoXY(x + 34, y + 1); printf("%c%c%c", 219, 219, 219);
    GotoXY(x + 34, y + 2); printf("%c%c%c", 219, 222, 219);
    //A
    GotoXY(x + 38, y); printf("%c%c%c", 222, 223, 221);
    GotoXY(x + 38, y + 1); printf("%c%c%c", 219, 220, 219);
    GotoXY(x + 38, y + 2); printf("%c%c%c", 219, ' ', 219);
    //K
    GotoXY(x + 42, y); printf("%c%c%c", 219, ' ', 219);
    GotoXY(x + 42, y + 1); printf("%c%c%c", 219, 223, 220);
    GotoXY(x + 42, y + 2); printf("%c%c%c", 219, ' ', 219);
    //E
    GotoXY(x + 46, y); printf("%c%c%c", 219, 223, 223);
    GotoXY(x + 46, y + 1); printf("%c%c%c", 219, 223, 223);
    GotoXY(x + 46, y + 2); printf("%c%c%c", 219, 220, 220);
}


int ShowMenu() {
    system("cls");
    ShowCursor(false);

    const int OPTION_BOX_W = 25;
    const int OPTION_BOX_H = 3;
    const int SPACING = 0;

    int center_x = WIDTH_CONSOLE / 2;
    int start_x = center_x - OPTION_BOX_W / 2;
    int start_y = HEIGH_CONSOLE / 2 - 4;

    const int tit_x = center_x - 20;
    const int tit_y = start_y - 5;


    const int SNAKE_X = start_x + OPTION_BOX_W + 3;
    const int SNAKE_Y = start_y + 4; 

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

    const int HIGHLIGHT_COLOR = 11;
    const int DEFAULT_COLOR = 7;
    const char BLOCK = 219;

    while (1) {
        system("cls");

        SetColor(11);
        DrawTitle(tit_x, tit_y);

        SetColor(DEFAULT_COLOR);

        DrawMenuSnake(SNAKE_X, SNAKE_Y);

        for (int i = 0; i < num_options; i++) {

            int current_y = start_y + (OPTION_BOX_H + SPACING) * i;

            int box_color = (i == selected_option) ? HIGHLIGHT_COLOR : DEFAULT_COLOR;
            int text_color = (i == selected_option) ? HIGHLIGHT_COLOR : DEFAULT_COLOR;

            DrawOptionBox(start_x, current_y, OPTION_BOX_W, OPTION_BOX_H, box_color);

            SetColor(text_color);
            GotoXY(start_x + 3, current_y + 1);
            printf("%s", options[i].c_str());
            SetColor(DEFAULT_COLOR);
        }

        char key = toupper(_getch());

        if (key == 'W') {
            selected_option = (selected_option - 1 + num_options) % num_options;
        }
        else if (key == 'S') {
            selected_option = (selected_option + 1) % num_options;
        }
        else if (key == 13) { // ENTER
            return selected_option + 1;
        }
        else if (key == 27) { // ESC
            return 6; // Quay về EXIT
        }
    }
}
