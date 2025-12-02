#include "About.h"
#include "Console.h"
#include "Global.h"

void ShowAbout() {
    system("cls");
    GotoXY(5, 2);  printf("=== ABOUT & HUONG DAN ===");
    GotoXY(5, 4);  printf("- Nhom: 6 ");
    GotoXY(5, 6);  printf("- Dieu khien: W/A/S/D di chuyen; P tam dung; Z luu; X tai; ESC Menu");
    GotoXY(5, 8);  printf("- Moi level an 4 moi -> xuat cong. Di qua cong de qua man.");
    GotoXY(5, 10); printf("- Cham tuong/vat can/than minh/object (LV4) -> thua.");
    GotoXY(5, 12); printf("Nhan [ESC] de quay lai Menu...");
    while (toupper(_getch()) != 27) {}
}
