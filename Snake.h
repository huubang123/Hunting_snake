#pragma once
#include "Header1.h"
#include "Global.h"


bool IsValid(int x, int y);
void ResetData(int initialSize = DEFAULT_SNAKE_LENGTH);
void Draw(const char* str);
void ProcessDead();
void ProcessDeadAnimation();
void ProcessLevelUp();
void ProcessGatePass(int nextX, int nextY);
void Eat();
