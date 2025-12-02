#include "Level.h"
#include "Global.h"
#include "Console.h"

// ===== Helper vẽ tường liền mạch =====
static void AddObstacleLineH(int x1, int x2, int y) {
    for (int x = x1; x <= x2; ++x) OBSTACLES.push_back({ x, y });
}
static void AddObstacleLineV(int x, int y1, int y2) {
    for (int y = y1; y <= y2; ++y) OBSTACLES.push_back({ x, y });
}

// ===== Helper vẽ tường có "khoảng trống" (khe/door) =====
static void AddObstacleLineHGap(int x1, int x2, int y, int gap_from, int gap_to) {
    if (gap_from > gap_to) { int t = gap_from; gap_from = gap_to; gap_to = t; }
    for (int x = x1; x <= x2; ++x) {
        if (x >= gap_from && x <= gap_to) continue; // chừa khe
        OBSTACLES.push_back({ x, y });
    }
}
static void AddObstacleLineVGap(int x, int y1, int y2, int gap_from, int gap_to) {
    if (gap_from > gap_to) { int t = gap_from; gap_from = gap_to; gap_to = t; }
    for (int y = y1; y <= y2; ++y) {
        if (y >= gap_from && y <= gap_to) continue; // chừa khe
        OBSTACLES.push_back({ x, y });
    }
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

    if (lv == 1) {
        // Level 1: không có vật cản bên trong
    }
    else if (lv == 2) {
        // Level 2: khung trong nhưng có 4 cửa 
        AddObstacleLineHGap(10, 40, 6, 24, 26); // top có cửa giữa
        AddObstacleLineHGap(10, 40, 14, 24, 26); // bottom có cửa giữa
        AddObstacleLineVGap(10, 6, 14, 9, 11); // left có cửa giữa
        AddObstacleLineVGap(40, 6, 14, 9, 11); // right có cửa giữa
    }
    else if (lv == 3) {
        // Level 3: KHÔNG khung kín, KHÔNG tường giữa
        // Tạo mê cung mở với nhiều khe hở:

        // 3 hàng ngang rải rác, mỗi hàng đều có khe hở
        AddObstacleLineHGap(10, 40, 6, 22, 28);  // hàng trên, hở ở giữa
        // (bỏ HÀNG GIỮA hoàn toàn để không có vật cản giữa)
        AddObstacleLineHGap(10, 40, 14, 33, 38);  // hàng dưới, hở lệch phải

        // Một vài cột dọc rời, mỗi cột đều có khe để băng qua
        AddObstacleLineVGap(16, 6, 14, 9, 11);    // cột trái, hở giữa
        AddObstacleLineVGap(28, 6, 14, 6, 8);     // cột giữa-trái, hở gần trên
        AddObstacleLineVGap(36, 6, 14, 12, 14);   // cột phải, hở gần dưới

    }
    else if (lv == 4) {
        // Level 4: dựa trên Level 3 + object di chuyển
        SetLevel(3); // kế thừa vật cản LV3 (đã mở)
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
        if (!IsObstacle(x, y)) {
            MOV_OBJ = { x, y };
            MOV_DX = 1; MOV_DY = 1;
            return;
        }
    }
    MOV_OBJ = { 0, 0 };
}

void UpdateMovingObject() {
    if (LEVEL != 4 || MOV_OBJ.x == 0) return;

    // xóa cũ
    GotoXY(MOV_OBJ.x, MOV_OBJ.y); printf(" ");

    int nx = MOV_OBJ.x + MOV_DX;
    int ny = MOV_OBJ.y + MOV_DY;

    // bật tường ngoài
    if (nx <= 1 || nx >= WIDTH_CONSOLE - 1)  MOV_DX = -MOV_DX;
    if (ny <= 1 || ny >= HEIGH_CONSOLE - 1)  MOV_DY = -MOV_DY;

    nx = MOV_OBJ.x + MOV_DX;
    ny = MOV_OBJ.y + MOV_DY;

    // bật vật cản bên trong
    if (IsObstacle(nx, ny)) { MOV_DX = -MOV_DX; MOV_DY = -MOV_DY; }

    MOV_OBJ.x += MOV_DX;
    MOV_OBJ.y += MOV_DY;

    // vẽ mới
    GotoXY(MOV_OBJ.x, MOV_OBJ.y); printf("X");
}
