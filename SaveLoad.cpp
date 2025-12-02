//#include "SaveLoad.h"
//#include "Global.h"
//#include "Console.h"
//#include "Board.h"
//#include "Snake.h"
//#include "ThreadControl.h"
//
//
//bool LoadGame()
//{
//    ifstream fin(SAVE_FILE_NAME);
//
//    if (!fin.is_open())
//    {
//        GotoXY(0, HEIGH_CONSOLE + 3);
//        printf("Save file not found!");
//        _getch();
//        return false;
//    }
//
//    int moving_int, lock_int;
//    fin >> SPEED >> FOOD_INDEX >> SIZE_SNAKE >> moving_int >> lock_int >> IS_GATE_ACTIVE >> OriginalSnakeSize;
//    MOVING = (char)moving_int;
//    CHAR_LOCK = (char)lock_int;
//
//    for (int i = 0; i < SIZE_SNAKE; i++)
//        fin >> snake[i].x >> snake[i].y >> snake_chars[i];
//
//    for (int i = 0; i < MAX_SIZE_FOOD; i++)
//        fin >> food[i].x >> food[i].y;
//
//    fin >> GATE_POINT.x >> GATE_POINT.y;
//    fin.close();
//
//    system("cls");
//    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
//    STATE = 1;
//
//    return true;
//}
//
//void SaveGame()
//{
//    PauseGame(handle_t1);
//
//    ofstream fout(SAVE_FILE_NAME);
//
//    if (!fout.is_open())
//    {
//        GotoXY(0, HEIGH_CONSOLE + 3);
//        printf("Save error!");
//        ResumeThread(handle_t1);
//        return;
//    }
//
//    fout << SPEED << endl;
//    fout << FOOD_INDEX << endl;
//    fout << SIZE_SNAKE << endl;
//    fout << (int)MOVING << endl;
//    fout << (int)CHAR_LOCK << endl;
//    fout << IS_GATE_ACTIVE << endl;
//    fout << OriginalSnakeSize << endl;
//
//    for (int i = 0; i < SIZE_SNAKE; i++)
//        fout << snake[i].x << " " << snake[i].y << " " << snake_chars[i] << endl;
//
//    for (int i = 0; i < MAX_SIZE_FOOD; i++)
//        fout << food[i].x << " " << food[i].y << endl;
//
//    fout << GATE_POINT.x << " " << GATE_POINT.y << endl;
//    fout.close();
//
//    GotoXY(0, HEIGH_CONSOLE + 3);
//    printf("Game saved! Press any key...");
//    _getch();
//
//    ResumeThread(handle_t1);
//}


#include "SaveLoad.h"
#include "Global.h"
#include "Console.h"
#include "Board.h"
#include "Snake.h"
#include "ThreadControl.h"
#include "Level.h"

#include <fstream>
#include <string>
using namespace std;

static const char* MAGIC = "HSV1";

bool LoadGame()
{
    ifstream fin(SAVE_FILE_NAME);
    if (!fin.is_open())
    {
        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Save file not found!");
        _getch();
        return false;
    }

    string magic;
    fin >> magic;
    if (magic != MAGIC) {
        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Save format mismatch!");
        _getch();
        return false;
    }

    // --- thông tin chung ---
    fin >> LEVEL >> SPEED >> SCORE >> FOODS_EATEN_IN_LEVEL;
    fin >> WIDTH_CONSOLE >> HEIGH_CONSOLE;
    fin >> SNAKE_COLOR >> SOUND_ON;

    // --- rắn / trạng thái di chuyển ---
    int moving_int, lock_int;
    fin >> SIZE_SNAKE >> moving_int >> lock_int >> IS_GATE_ACTIVE >> OriginalSnakeSize;
    MOVING = (char)moving_int;
    CHAR_LOCK = (char)lock_int;

    for (int i = 0; i < SIZE_SNAKE; i++)
        fin >> snake[i].x >> snake[i].y >> snake_chars[i];

    // --- mồi & chỉ số mồi hiện tại ---
    int max_food, food_index_in;
    fin >> max_food >> food_index_in;
    // max_food để phòng sau này thay đổi, hiện đang là 4
    FOOD_INDEX = food_index_in;
    for (int i = 0; i < max_food && i < MAX_SIZE_FOOD; i++)
        fin >> food[i].x >> food[i].y;

    // --- cổng ---
    fin >> GATE_POINT.x >> GATE_POINT.y;

    // --- chướng ngại ---
    size_t obs_count;
    fin >> obs_count;
    OBSTACLES.clear();
    OBSTACLES.reserve(obs_count);
    for (size_t i = 0; i < obs_count; ++i) {
        POINT p;
        fin >> p.x >> p.y;
        OBSTACLES.push_back(p);
    }

    // --- object LV4 ---
    fin >> MOV_OBJ.x >> MOV_OBJ.y >> MOV_DX >> MOV_DY;

    fin.close();

    system("cls");
    DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE);
    // KHÔNG gọi SetLevel(LEVEL) vì ta đã load OBSTACLES từ file
    DrawLevel();
    STATE = 1;

    return true;
}

void SaveGame()
{
    PauseGame(handle_t1);

    ofstream fout(SAVE_FILE_NAME, ios::trunc);
    if (!fout.is_open())
    {
        GotoXY(0, HEIGH_CONSOLE + 3);
        printf("Save error!");
        ResumeThread(handle_t1);
        return;
    }

    // --- magic/version ---
    fout << MAGIC << "\n";

    // --- thông tin chung ---
    fout << LEVEL << " " << SPEED << " " << SCORE << " " << FOODS_EATEN_IN_LEVEL << "\n";
    fout << WIDTH_CONSOLE << " " << HEIGH_CONSOLE << "\n";
    fout << SNAKE_COLOR << " " << SOUND_ON << "\n";

    // --- rắn / trạng thái di chuyển ---
    fout << SIZE_SNAKE << " " << (int)MOVING << " " << (int)CHAR_LOCK
        << " " << IS_GATE_ACTIVE << " " << OriginalSnakeSize << "\n";

    for (int i = 0; i < SIZE_SNAKE; i++)
        fout << snake[i].x << " " << snake[i].y << " " << snake_chars[i] << "\n";

    // --- mồi & chỉ số mồi ---
    fout << MAX_SIZE_FOOD << " " << FOOD_INDEX << "\n";
    for (int i = 0; i < MAX_SIZE_FOOD; i++)
        fout << food[i].x << " " << food[i].y << "\n";

    // --- cổng ---
    fout << GATE_POINT.x << " " << GATE_POINT.y << "\n";

    // --- chướng ngại ---
    fout << OBSTACLES.size() << "\n";
    for (const auto& p : OBSTACLES)
        fout << p.x << " " << p.y << "\n";

    // --- object LV4 ---
    fout << MOV_OBJ.x << " " << MOV_OBJ.y << " " << MOV_DX << " " << MOV_DY << "\n";

    fout.close();

    GotoXY(0, HEIGH_CONSOLE + 3);
    printf("Game saved! Press any key...");
    _getch();

    ResumeThread(handle_t1);
}
