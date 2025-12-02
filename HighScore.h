#pragma once
#include "Header1.h"
#include <string>


struct ScoreEntry {
    string name;
    int score;
};

void ShowHighScores();
void SaveHighScorePrompt();
