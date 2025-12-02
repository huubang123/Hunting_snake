#include "Settings.h"
#include "Global.h"
#include "Console.h"

void ShowSettings() {
    system("cls");
    int sel = 0;
    while (true) {
        GotoXY(5, 2); printf("=== SETTINGS ===           ");
        GotoXY(5, 4); printf("%s Mau ran (1-Xanh,2-Vang,3-Do,4-Cyan,5-Magenta): %d   ",
            sel == 0 ? ">>" : "  ", SNAKE_COLOR);
        GotoXY(5, 5); printf("%s Am thanh (Space: chuyen doi): %s    ",
            sel == 1 ? ">>" : "  ", SOUND_ON ? "ON" : "OFF");
        GotoXY(5, 7); printf("W/S: chon; A/D/So/Space: doi; ESC: quay lai");

        char k = toupper(_getch());
        if (k == 'W') sel = (sel + 1 + 2) % 2;
        else if (k == 'S') sel = (sel + 1) % 2;
        else if (k == 'A' || k == 'D' || (k >= '1' && k <= '5') || k == ' ') {
            if (sel == 0) {
                if (k >= '1' && k <= '5') {
                    int opt = k - '0';
                    if (opt == 1) SNAKE_COLOR = COL_GREEN;
                    if (opt == 2) SNAKE_COLOR = COL_YELLOW;
                    if (opt == 3) SNAKE_COLOR = COL_RED;
                    if (opt == 4) SNAKE_COLOR = COL_CYAN;
                    if (opt == 5) SNAKE_COLOR = COL_MAGENTA;
                }
            }
            else {
                SOUND_ON = !SOUND_ON;
            }
        }
        else if (k == 27) break;
    }
}
