//#include "Food.h"
//#include "Global.h"
//#include "Snake.h"
//
//void GenerateFood()
//{
//    int x, y;
//    int attempt_limit = 1000;
//    int attempts;
//
//    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
//        attempts = 0;
//        do {
//            x = rand() % (WIDTH_CONSOLE - 1) + 1;
//            y = rand() % (HEIGH_CONSOLE - 1) + 1;
//            attempts++;
//
//            if (attempts > attempt_limit)
//            {
//                food[i] = { 0, 0 };
//                break;
//            }
//        } while (!IsValid(x, y));
//
//        if (attempts <= attempt_limit)
//            food[i] = { x, y };
//    }
//}


#include "Food.h"
#include "Global.h"
#include "Snake.h"
#include "Level.h"

void GenerateFood()
{
    int x, y;
    int attempt_limit = 2000;

    for (int i = 0; i < MAX_SIZE_FOOD; i++) {
        int attempts = 0;
        do {
            x = rand() % (WIDTH_CONSOLE - 1) + 1;
            y = rand() % (HEIGH_CONSOLE - 1) + 1;
            attempts++;
            if (attempts > attempt_limit)
            {
                food[i] = { 1, 1 }; 
                break;
            }
        } while (!IsValid(x, y) || IsObstacle(x, y));
        food[i] = { x, y };
    }
}
