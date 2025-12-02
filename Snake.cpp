//#include "Snake.h"
//#include "Global.h"
//#include "Console.h"
//#include "Board.h"
//#include "Food.h"
//#include "Gate.h"
//#include "ThreadControl.h"
//
//bool IsValid(int x, int y)
//{
//    if (x <= 0 || x >= WIDTH_CONSOLE || y <= 0 || y >= HEIGH_CONSOLE) return false;
//
//    for (int i = 0; i < SIZE_SNAKE; i++)
//        if (x == snake[i].x && y == snake[i].y) return false;
//
//    if (IS_GATE_ACTIVE && x == GATE_POINT.x && y == GATE_POINT.y) return false;
//
//    return true;
//}
//
//void Draw(const char* str)
//{
//    if (!IS_GATE_ACTIVE)
//    {
//        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
//        printf(str);
//    }
//
//    for (int i = 0; i < SIZE_SNAKE; i++)
//    {
//        GotoXY(snake[i].x, snake[i].y);
//        if (strcmp(str, " ") == 0) printf(" ");
//        else printf("%c", snake_chars[i]);
//    }
//
//    if (IS_GATE_ACTIVE)
//    {
//        GotoXY(GATE_POINT.x, GATE_POINT.y);
//        printf("|");
//    }
//}
//
//void ProcessDeadAnimation()
//{
//    for (int k = 0; k < 7; k++)
//    {
//        for (int i = 0; i < SIZE_SNAKE; i++)
//        {
//            GotoXY(snake[i].x, snake[i].y);
//            printf("%c", snake_chars[i]);
//        }
//        Sleep(150);
//
//        for (int i = 0; i < SIZE_SNAKE; i++)
//        {
//            GotoXY(snake[i].x, snake[i].y);
//            printf(" ");
//        }
//        Sleep(150);
//    }
//}
//
//void ProcessDead()
//{
//    STATE = 0;
//    ProcessDeadAnimation();
//    GotoXY(WIDTH_CONSOLE / 2 - 5, HEIGH_CONSOLE / 2);
//    printf("GAME OVER!");
//}
//void Eat()
//{
//
//    POINT old_tail_pos = snake[0];
//    char old_tail_char = snake_chars[0];
//
//    for (int i = SIZE_SNAKE - 1; i >= 0; i--)
//    {
//        snake[i + 1] = snake[i];
//        snake_chars[i + 1] = snake_chars[i];
//    }
//
//    snake[0] = old_tail_pos;
//
//    snake_chars[0] = ID_STRING[SIZE_SNAKE % ID_LEN];
//
//    SIZE_SNAKE++;
//
//    if (FOOD_INDEX == MAX_SIZE_FOOD - 1)
//    {
//        OriginalSnakeSize = SIZE_SNAKE;
//
//        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
//        printf(" ");
//
//        GenerateGate();
//    }
//    else
//    {
//        FOOD_INDEX++;
//    }
//}
//
//void ResetData(int initialSize)
//{
//    SPEED = 4;
//    srand(time(NULL));
//    FOOD_INDEX = 0;
//
//    MOVING = 'A';
//    CHAR_LOCK = 'D';
//
//    SIZE_SNAKE = initialSize;
//
//    int centerX = WIDTH_CONSOLE / 2;
//    int centerY = HEIGH_CONSOLE / 2;
//
//    int safeY = (centerY < 3) ? 3 : centerY;
//    safeY = (safeY > HEIGH_CONSOLE - 3) ? HEIGH_CONSOLE - 3 : safeY;
//
//    int startX = centerX - (SIZE_SNAKE / 2);
//    if (startX < 1) startX = 1;
//
//    for (int i = 0; i < SIZE_SNAKE; i++)
//    {
//        snake[i].x = startX + i;
//        snake[i].y = safeY;
//        snake_chars[i] = ID_STRING[i % ID_LEN];
//    }
//
//    for (int i = 0; i < SIZE_SNAKE / 2; i++)
//    {
//        POINT temp_p = snake[i];
//        snake[i] = snake[SIZE_SNAKE - 1 - i];
//        snake[SIZE_SNAKE - 1 - i] = temp_p;
//
//        char temp_c = snake_chars[i];
//        snake_chars[i] = snake_chars[SIZE_SNAKE - 1 - i];
//        snake_chars[SIZE_SNAKE - 1 - i] = temp_c;
//    }
//
//    GenerateFood();
//}
//void ProcessLevelUp()
//{
//    Sleep(500);
//
//    system("cls");
//
//    int sizeToKeep = OriginalSnakeSize;
//
//    if (SPEED < MAX_SPEED)
//    {
//        SPEED++;
//    }
//    else
//    {
//        sizeToKeep = DEFAULT_SNAKE_LENGTH;
//    }
//
//    IS_GATE_ACTIVE = 0;
//    OriginalSnakeSize = 0;
//
//    ResetData(sizeToKeep);
//
//    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
//}
//
//void ProcessGatePass(int nextX, int nextY)
//{
//    GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
//    printf(" ");
//
//    SIZE_SNAKE--;
//
//    snake[SIZE_SNAKE].x = nextX;
//    snake[SIZE_SNAKE].y = nextY;
//
//    if (OriginalSnakeSize > 0 && SIZE_SNAKE == 0)
//    {
//        ProcessLevelUp();
//    }
//}


#include "Snake.h"
#include "Global.h"
#include "Console.h"
#include "Board.h"
#include "Food.h"
#include "Gate.h"
#include "ThreadControl.h"
#include "Level.h"
#include "HighScore.h"

// -------------------- Tiện ích --------------------
static void SetTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// -------------------- Hợp lệ vị trí --------------------
bool IsValid(int x, int y)
{
    if (x <= 0 || x >= WIDTH_CONSOLE || y <= 0 || y >= HEIGH_CONSOLE) return false;
    if (IsObstacle(x, y)) return false;

    for (int i = 0; i < SIZE_SNAKE; i++)
        if (x == snake[i].x && y == snake[i].y) return false;

    if (IS_GATE_ACTIVE && x == GATE_POINT.x && y == GATE_POINT.y) return false;

    return true;
}

// -------------------- Vẽ --------------------
void Draw(const char* str)
{
    // vẽ mồi hiện tại (chỉ khi chưa có cổng)
    if (!IS_GATE_ACTIVE)
    {
        GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
        if (strcmp(str, " ") == 0) printf(" ");
        else { SetTextColor(COL_YELLOW); printf("*"); SetTextColor(SNAKE_COLOR); }
    }

    // vẽ thân rắn
    SetTextColor(SNAKE_COLOR);
    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        GotoXY(snake[i].x, snake[i].y);
        if (strcmp(str, " ") == 0) printf(" ");
        else printf("%c", snake_chars[i]);
    }
    SetTextColor(COL_DEFAULT);

    // vẽ gate nếu có
    if (IS_GATE_ACTIVE)
    {
        GotoXY(GATE_POINT.x, GATE_POINT.y);
        printf("|");
    }

}

// -------------------- Hiệu ứng chết --------------------
void ProcessDeadAnimation()
{
    SetTextColor(SNAKE_COLOR);
    if (SOUND_ON) Beep(500, 120);
    for (int k = 0; k < 7; k++)
    {
        for (int i = 0; i < SIZE_SNAKE; i++)
        {
            GotoXY(snake[i].x, snake[i].y);
            printf("%c", snake_chars[i]);
        }
        Sleep(150);

        for (int i = 0; i < SIZE_SNAKE; i++)
        {
            GotoXY(snake[i].x, snake[i].y);
            printf(" ");
        }
        Sleep(150);
    }
}

// -------------------- Xử lý chết --------------------
void ProcessDead()
{
    STATE = 0;
    ProcessDeadAnimation();
    GotoXY(WIDTH_CONSOLE / 2 - 5, HEIGH_CONSOLE / 2);
    printf("GAME OVER!");

    SaveHighScorePrompt();  // hỏi tên & lưu top 10
    GO_BACK_MENU = 1;
}

// -------------------- Ăn mồi --------------------
void Eat()
{
    if (SOUND_ON) Beep(750, 80);
    SCORE += 10;
    FOODS_EATEN_IN_LEVEL++;

    POINT old_tail_pos = snake[0];
    char old_tail_char = snake_chars[0]; 

    for (int i = SIZE_SNAKE - 1; i >= 0; i--)
    {
        snake[i + 1] = snake[i];
        snake_chars[i + 1] = snake_chars[i];
    }
    snake[0] = old_tail_pos;
    snake_chars[0] = ID_STRING[SIZE_SNAKE % ID_LEN];
    SIZE_SNAKE++;

    // xóa ký tự mồi vừa ăn
    GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y); printf(" ");

    if (FOODS_EATEN_IN_LEVEL >= 4)
    {
        OriginalSnakeSize = SIZE_SNAKE;
        GenerateGate(); // bật cổng
    }
    else
    {
        // chuyển sang mồi tiếp theo trong danh sách 4 mồi
        FOOD_INDEX++;
        if (FOOD_INDEX >= MAX_SIZE_FOOD) FOOD_INDEX = MAX_SIZE_FOOD - 1; 
    }
}

// -------------------- Reset dữ liệu level --------------------
void ResetData(int initialSize)
{
    SPEED = (SPEED > 0 ? SPEED : 4);
    srand((unsigned)time(NULL));

    FOOD_INDEX = 0;
    FOODS_EATEN_IN_LEVEL = 0;

    MOVING = 'A';
    CHAR_LOCK = 'D';

    SIZE_SNAKE = initialSize;

    int centerX = WIDTH_CONSOLE / 2;
    int centerY = HEIGH_CONSOLE / 2;

    int safeY = (centerY < 3) ? 3 : centerY;
    safeY = (safeY > HEIGH_CONSOLE - 3) ? HEIGH_CONSOLE - 3 : safeY;

    int startX = centerX - (SIZE_SNAKE / 2);
    if (startX < 1) startX = 1;

    for (int i = 0; i < SIZE_SNAKE; i++)
    {
        snake[i].x = startX + i;
        snake[i].y = safeY;
        snake_chars[i] = ID_STRING[i % ID_LEN];
    }

    // đảo mảng để đầu rắn ở bên phải
    for (int i = 0; i < SIZE_SNAKE / 2; i++)
    {
        POINT temp_p = snake[i];
        snake[i] = snake[SIZE_SNAKE - 1 - i];
        snake[SIZE_SNAKE - 1 - i] = temp_p;

        char temp_c = snake_chars[i];
        snake_chars[i] = snake_chars[SIZE_SNAKE - 1 - i];
        snake_chars[SIZE_SNAKE - 1 - i] = temp_c;
    }

    // Sinh trước 4 vị trí thức ăn
    GenerateFood();
    IS_GATE_ACTIVE = 0;
}

// -------------------- Qua màn --------------------
void ProcessLevelUp()
{
    // qua cổng thành công
    SCORE += 100;
    Sleep(500);
    system("cls");

    // tiến level
    if (LEVEL < 4) {
        LEVEL++;
    }
    else {
        // hoàn tất vòng 1..4: reset độ dài, tăng SPEED (nếu còn), lặp lại từ LV1
        if (SPEED < MAX_SPEED) SPEED++;
        LEVEL = 1;
    }

    int sizeToKeep = OriginalSnakeSize;
    if (LEVEL == 1) { // khi vòng mới bắt đầu, reset độ dài theo yêu cầu
        sizeToKeep = DEFAULT_SNAKE_LENGTH;
    }

    IS_GATE_ACTIVE = 0;
    OriginalSnakeSize = 0;

    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
    SetLevel(LEVEL);
    ResetData(sizeToKeep);
    DrawLevel();
}

// -------------------- Đi qua cổng --------------------
void ProcessGatePass(int nextX, int nextY)
{
    // xóa đuôi cũ
    GotoXY(snake[SIZE_SNAKE - 1].x, snake[SIZE_SNAKE - 1].y);
    printf(" ");

    // rút ngắn thân
    SIZE_SNAKE--;

    // đặt lại đầu ở vị trí tiến vào gate 
    snake[SIZE_SNAKE].x = nextX;
    snake[SIZE_SNAKE].y = nextY;

    // khi thân rút hết -> qua màn
    if (OriginalSnakeSize > 0 && SIZE_SNAKE == 0)
    {
        ProcessLevelUp();
    }
}
