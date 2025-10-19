#include "game.h"
#include <thread>
#include <conio.h>
#include <ctype.h>
#include <iostream>

using namespace std;

int main() {
    StartGame();

    thread t1(ThreadFunc);
    handle_t1 = t1.native_handle();

    char temp;

    while (1) {
        temp = toupper(_getch());

        if (STATE == 1) {
            if (temp == 'P') {
                PauseGame(handle_t1);
            }
            else if (temp == 27) { // ESC
                ExitGame(handle_t1);
                t1.detach();
                return 0;
            }
            else {
                ResumeThread(handle_t1);

                if (temp == 'D' || temp == 'A' || temp == 'W' || temp == 'S') {
                    if (temp != CHAR_LOCK) {

                        if (temp == 'D') CHAR_LOCK = 'A';
                        else if (temp == 'A') CHAR_LOCK = 'D';
                        else if (temp == 'W') CHAR_LOCK = 'S';
                        else if (temp == 'S') CHAR_LOCK = 'W';

                        MOVING = temp;
                    }
                }
            }
        }
        else {
            if (temp == 'Y') {
                StartGame();
                ResumeThread(handle_t1);
            }
            else {
                ExitGame(handle_t1);
                t1.detach();
                return 0;
            }
        }
    }

    if (t1.joinable()) t1.join();
    return 0;
}
