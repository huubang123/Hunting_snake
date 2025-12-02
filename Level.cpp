#include "Level.h"
#include "Global.h"
#include "Console.h"

static void AddObstacleLineH(int x1, int x2, int y) {
    for (int x = x1; x <= x2; ++x) OBSTACLES.push_back({ x,y });
}
static void AddObstacleLineV(int x, int y1, int y2) {
    for (int y = y1; y <= y2; ++y) OBSTACLES.push_back({ x,y });
}

bool IsObstacle(int x, int y) {
    for (const auto& p : OBSTACLES) if (p.x == x && p.y == y) return true;
    return false;
}

void ClearObstacles() {
    OBSTACLES.clear();
}

void DrawLevel() {
    // Vẽ vật cản
    for (const auto& p : OBSTACLES) {
        GotoXY(p.x, p.y); printf("#");
    }
    // Vẽ object LV4
    if (LEVEL == 4 && MOV_OBJ.x > 0) {
        GotoXY(MOV_OBJ.x, MOV_OBJ.y); printf("X");
    }
}

void SetLevel(int lv) {
    LEVEL = lv;
    ClearObstacles();

    // Level 1: không vật cản bên trong 
    if (lv == 1) {
       
    }
    // Level 2: vài tường ngang/dọc
    else if (lv == 2) {
        AddObstacleLineH(10, 40, 6);
        AddObstacleLineH(10, 40, 14);
        AddObstacleLineV(10, 6, 14);
        AddObstacleLineV(40, 6, 14);
    }
    // Level 3: mê cung nhỏ
    else if (lv == 3) {
        AddObstacleLineH(8, 42, 5);
        AddObstacleLineH(8, 42, 15);
        AddObstacleLineV(8, 5, 15);
        AddObstacleLineV(42, 5, 15);
        AddObstacleLineH(15, 35, 10);
        AddObstacleLineV(20, 7, 13);
        AddObstacleLineV(30, 7, 13);
    }
    // Level 4: giống LV3 + object di chuyển
    else if (lv == 4) {
        SetLevel(3); // kế thừa vật cản LV3
        LEVEL = 4;
        InitMovingObjectIfNeeded();
    }
}

void InitMovingObjectIfNeeded() {
    if (LEVEL != 4) return;
    // spawn ở vị trí trống
    for (int tries = 0; tries < 1000; ++tries) {
        int x = rand() % (WIDTH_CONSOLE - 2) + 1;
        int y = rand() % (HEIGH_CONSOLE - 2) + 1;
        bool clash = false;
        if (IsObstacle(x, y)) clash = true;
        if (!clash) {
            MOV_OBJ = { x,y };
            MOV_DX = 1; MOV_DY = 1;
            return;
        }
    }
    MOV_OBJ = { 0,0 };
}

void UpdateMovingObject() {
    if (LEVEL != 4 || MOV_OBJ.x == 0) return;

    // xóa cũ
    GotoXY(MOV_OBJ.x, MOV_OBJ.y); printf(" ");

    int nx = MOV_OBJ.x + MOV_DX;
    int ny = MOV_OBJ.y + MOV_DY;

    // bật tường
    if (nx <= 1 || nx >= WIDTH_CONSOLE - 1) MOV_DX = -MOV_DX;
    if (ny <= 1 || ny >= HEIGH_CONSOLE - 1) MOV_DY = -MOV_DY;

    nx = MOV_OBJ.x + MOV_DX;
    ny = MOV_OBJ.y + MOV_DY;

    // bật vật cản bên trong
    if (IsObstacle(nx, ny)) { MOV_DX = -MOV_DX; MOV_DY = -MOV_DY; }

    MOV_OBJ.x += MOV_DX;
    MOV_OBJ.y += MOV_DY;

    // vẽ mới
    GotoXY(MOV_OBJ.x, MOV_OBJ.y); printf("X");
}
