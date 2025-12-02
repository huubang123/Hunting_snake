#include "system.h"
#include <iostream>

void GotoXY(int x, int y) {
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowCursor(bool show) {
    CONSOLE_CURSOR_INFO info = { 1, show };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void PauseGame(HANDLE t) {
    SuspendThread(t);
}

void ExitGame(HANDLE t) {
    TerminateThread(t, 0);
    system("cls");
}
