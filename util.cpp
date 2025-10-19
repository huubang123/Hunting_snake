#include "game.h"
#include <stdio.h>
#include <windows.h>

// Di chuyển con trỏ tới vị trí (x, y)
void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Vẽ khung bao quanh màn hình
void DrawBoard(int x, int y, int width, int height) {
    GotoXY(x, y); printf("%c", 201);
    for (int i = 1; i < width; i++) {
        GotoXY(x + i, y); printf("%c", 205);
    }
    GotoXY(x + width, y); printf("%c", 187);

    for (int i = 1; i < height; i++) {
        GotoXY(x, y + i); printf("%c", 186);
        GotoXY(x + width, y + i); printf("%c", 186);
    }

    GotoXY(x, y + height); printf("%c", 200);
    for (int i = 1; i < width; i++) {
        GotoXY(x + i, y + height); printf("%c", 205);
    }
    GotoXY(x + width, y + height); printf("%c", 188);
}

// Ẩn hoặc hiện con trỏ
void ShowCursor(bool show) {
    CONSOLE_CURSOR_INFO info = { 1, (BOOL)show };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

// Tạm dừng game (tạm dừng luồng chạy)
void PauseGame(HANDLE t) {
    SuspendThread(t);
}

// Thoát game (kết thúc luồng chạy)
void ExitGame(HANDLE t) {
    TerminateThread(t, 0);
    system("cls");
}
