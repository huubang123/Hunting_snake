#include "ThreadControl.h"
#include "Global.h"

void PauseGame(HANDLE t)
{
    SuspendThread(t);
}

void ExitGame(HANDLE t)
{
    TerminateThread(t, 0);
    system("cls");
}
