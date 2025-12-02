//#pragma once
//#include "Header1.h"
//
//#define MAX_SIZE_SNAKE 100
//#define MAX_SIZE_FOOD 3
//#define DEFAULT_SNAKE_LENGTH 6
//#define MAX_SPEED 6
//#define SAVE_FILE_NAME "snake_save.txt"
//
//extern const string ID_STRING;
//#define ID_LEN ID_STRING.length()
//
//extern POINT snake[MAX_SIZE_SNAKE];
//extern POINT food[MAX_SIZE_FOOD];
//extern POINT GATE_POINT;
//
//extern int CHAR_LOCK;
//extern int MOVING;
//extern int SPEED;
//extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
//extern int FOOD_INDEX;
//extern int SIZE_SNAKE;
//extern int STATE;
//
//extern int IS_GATE_ACTIVE;
//extern int OriginalSnakeSize;
//extern HANDLE handle_t1;
//
//extern char snake_chars[MAX_SIZE_SNAKE];
//


#pragma once
#include "Header1.h"

#define MAX_SIZE_SNAKE 100
#define MAX_SIZE_FOOD  4     
#define DEFAULT_SNAKE_LENGTH 6
#define MAX_SPEED 6
#define SAVE_FILE_NAME "snake_save.txt"
#define HIGHSCORE_FILE "highscores.txt"

// Màu console (Windows)
#define COL_DEFAULT 7
#define COL_RED     12
#define COL_GREEN   10
#define COL_YELLOW  14
#define COL_CYAN    11
#define COL_MAGENTA 13

extern const string ID_STRING;
#define ID_LEN ID_STRING.length()

extern POINT snake[MAX_SIZE_SNAKE];
extern POINT food[MAX_SIZE_FOOD];
extern POINT GATE_POINT;

extern int CHAR_LOCK;
extern int MOVING;
extern int SPEED;
extern int HEIGH_CONSOLE, WIDTH_CONSOLE;
extern int FOOD_INDEX;            
extern int SIZE_SNAKE;
extern int STATE;

extern int IS_GATE_ACTIVE;         
extern int OriginalSnakeSize;
extern HANDLE handle_t1;
extern char snake_chars[MAX_SIZE_SNAKE];

// level & chướng ngại & object LV4
extern int LEVEL;                  
extern std::vector<POINT> OBSTACLES;
bool IsObstacle(int x, int y);     

// Object di chuyển (LV4)
extern POINT MOV_OBJ;
extern int MOV_DX, MOV_DY;

// Điểm & thiết đặt
extern int SCORE;
extern int FOODS_EATEN_IN_LEVEL;   
extern int SOUND_ON;                
extern int SNAKE_COLOR;            
