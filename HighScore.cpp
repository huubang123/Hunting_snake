#define NOMINMAX  

#include "HighScore.h"
#include "Global.h"
#include "Console.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// LOAD toàn bộ điểm từ file
static vector<ScoreEntry> LoadAll() {
    vector<ScoreEntry> v;
    ifstream f(HIGHSCORE_FILE);
    if (!f.is_open()) return v;

    string name;
    int sc;

    while (true)
    {
        if (!getline(f, name)) break;     // đọc tên người chơi
        if (!(f >> sc)) break;            // đọc điểm
        f.ignore(1000, '\n');             // bỏ ký tự xuống dòng

        v.push_back({ name, sc });
    }
    return v;
}

// SAVE toàn bộ vào file
static void SaveAll(const vector<ScoreEntry>& v) {
    ofstream f(HIGHSCORE_FILE, ios::trunc);
    for (auto& e : v) {
        f << e.name << "\n";
        f << e.score << "\n";
    }
}

// HIỂN THỊ HIGH SCORE TOP 10

void ShowHighScores() {
    system("cls");

    auto v = LoadAll();
    sort(v.begin(), v.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });

    if ((int)v.size() > 10) v.resize(10);

    GotoXY(5, 2); printf("=== HIGH SCORE TOP 10 ===");

    int row = 4;
    int rank = 1;

    for (auto& e : v) {
        GotoXY(5, row++);
        printf("%2d) %-20s %6d", rank++, e.name.c_str(), e.score);
    }

    GotoXY(5, row + 2);
    printf("Nhan [ESC] de quay lai Menu...");

    while (toupper(_getch()) != 27) {}
}
// LƯU ĐIỂM SAU KHI GAME OVER

void SaveHighScorePrompt() {
    auto v = LoadAll();

    system("cls");
    ShowCursor(true);

    GotoXY(5, 5);
    printf("Nhap ten cua ban: ");

    string name;
    getline(cin, name);
    if (name.empty()) name = "Player";

    ShowCursor(false);

    v.push_back({ name, SCORE });

    sort(v.begin(), v.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) {
            return a.score > b.score;
        });

    if ((int)v.size() > 10) v.resize(10);

    SaveAll(v);
    GO_BACK_MENU = 1;

    GotoXY(5, 7);
    printf("Da luu ket qua! Diem: %d", SCORE);

    GotoXY(5, 9);
    printf("Nhan phim bat ky de tiep tuc...");
    _getch();
}
