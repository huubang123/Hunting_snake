#include "Gate.h"
#include "Global.h"
#include "Snake.h"

void GenerateGate()
{
    int gateX, gateY;
    int attempts = 0;

    do {
        gateX = rand() % (WIDTH_CONSOLE - 1) + 1;
        gateY = rand() % (HEIGH_CONSOLE - 1) + 1;
        attempts++;
        if (attempts > 1000) return;
    } while (!IsValid(gateX, gateY));

    GATE_POINT = { gateX, gateY };
    IS_GATE_ACTIVE = 1;
}
