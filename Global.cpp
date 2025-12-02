//#include "Global.h"
//
//const string ID_STRING = "2012033822120019";
//
//POINT snake[MAX_SIZE_SNAKE];
//POINT food[MAX_SIZE_FOOD];
//POINT GATE_POINT;
//
//int CHAR_LOCK;
//int MOVING;
//int SPEED;
//int HEIGH_CONSOLE, WIDTH_CONSOLE;
//int FOOD_INDEX;
//int SIZE_SNAKE;
//int STATE;
//
//int IS_GATE_ACTIVE = 0;
//int OriginalSnakeSize = 0;
//HANDLE handle_t1;
//
//char snake_chars[MAX_SIZE_SNAKE];
//


#include "Global.h"

const string ID_STRING = "2012033822120019";

POINT snake[MAX_SIZE_SNAKE];
POINT food[MAX_SIZE_FOOD];
POINT GATE_POINT;

int CHAR_LOCK;
int MOVING;
int SPEED;
int HEIGH_CONSOLE, WIDTH_CONSOLE;
int FOOD_INDEX;
int SIZE_SNAKE;
int STATE;

int IS_GATE_ACTIVE = 0;
int OriginalSnakeSize = 0;
HANDLE handle_t1;

char snake_chars[MAX_SIZE_SNAKE];


int LEVEL = 1;
std::vector<POINT> OBSTACLES;

POINT MOV_OBJ{ 0,0 };
int MOV_DX = 1, MOV_DY = 1;

int SCORE = 0;
int FOODS_EATEN_IN_LEVEL = 0;
int SOUND_ON = 1;
int SNAKE_COLOR = COL_GREEN;


int GO_BACK_MENU = 0;