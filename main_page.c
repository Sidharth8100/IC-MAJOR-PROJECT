#include <stdio.h>
#include<conio.h>

#define width 115
#define height 45

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void endh() {
    gotoxy(20, 1);
    printf("%c", 201);
    for (int i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    for (int i = 0; i < height - 2; i++) {
        gotoxy(20, i + 2);
        printf("%c", 186);
        for (int j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("%c", 186);
    }
    gotoxy(20, height);
    printf("%c", 200);
    for (int i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
    gotoxy(62, 5);
    printf("IIT Jodhpur Banking systum");

    // ASCII art placement inside the box
    int ascii_art_x = 30; // Adjust X-coordinate for ASCII art placement
    int ascii_art_y = 5; // Adjust Y-coordinate for ASCII art placement

    gotoxy(ascii_art_x, ascii_art_y);
    printf("                                   **,,*/ /*,,**                                ");
    gotoxy(ascii_art_x, ascii_art_y + 1);
    printf("                                  **/**//(/***//.                               ");
    gotoxy(ascii_art_x, ascii_art_y + 2);
    printf("                                  //*,,,*(*,,,*(/                               ");
    gotoxy(ascii_art_x, ascii_art_y + 3);
    printf("                                 ,//*,,**(*,,,*//.                              ");
    gotoxy(ascii_art_x, ascii_art_y + 4);
    printf("                                 (//*,,**(**,,*/(,                              ");
    gotoxy(ascii_art_x, ascii_art_y + 5);
    printf("                                 /(*,,,*/(**,,,/(*                              ");
    gotoxy(ascii_art_x, ascii_art_y + 6);
    printf("                                 ((*,,,*/(*,,,,/(/                              ");
    gotoxy(ascii_art_x, ascii_art_y + 7);
    printf("                                ,//*,,,*/(*,,,,*((.                             ");
    gotoxy(ascii_art_x, ascii_art_y + 8);
    printf("                                *//*,,,*/(/*,,,*/(,                             ");
    gotoxy(ascii_art_x, ascii_art_y + 9);
    printf("                               .((/*,,,*/#/*,,,*/(/                             ");
    gotoxy(ascii_art_x, ascii_art_y + 10);
    printf("                              .//(**,,,*(#/*,,,**((*                            ");
    gotoxy(ascii_art_x, ascii_art_y + 11);
    printf("                             ./(//*,,,,*(%/*,,,**/((/                           ");
    gotoxy(ascii_art_x, ascii_art_y + 12);
    printf("                             /((/**,,,**(#/*,,,,**/((                           ");
    gotoxy(ascii_art_x, ascii_art_y + 13);
    printf("                            .((/***,,,**(#/*,,,,**/(((                          ");
    gotoxy(ascii_art_x, ascii_art_y + 14);
    printf("                            /((/**,,,,**(#/**,,,,**/((,                         ");
    gotoxy(ascii_art_x, ascii_art_y + 15);
    printf("                           .((//*,,,,,**(#/*,,,,,**//(/                         ");
    gotoxy(ascii_art_x, ascii_art_y + 16);
    printf("                           *(//**,,,,,*/(%(**,,,,**/(((.                        ");
    gotoxy(ascii_art_x, ascii_art_y + 17);
    printf("                           (//**,,,,,**/(%(**,,,,**/(//                        ");
    gotoxy(ascii_art_x, ascii_art_y + 18);
    printf("                         .(///**,,,,,**/#%(***,,,,**///(/                       ");
    gotoxy(ascii_art_x, ascii_art_y + 19);
    printf("                        ,////***,,,,,***/(%(/***,,,,***////(.                     ");
    gotoxy(ascii_art_x, ascii_art_y + 20);
    printf("                      ./(///****,,,,***/(##(/****,,,****////(/                    ");
    gotoxy(ascii_art_x, ascii_art_y + 21);
    printf("                    .////******,,,,***/(#%#//*************/////..                ");
    gotoxy(ascii_art_x, ascii_art_y + 22);
    printf("              .(%%(/////********,****// (#%( (/****,*******/////((#%%(,          ");
    gotoxy(ascii_art_x, ascii_art_y + 23);
    printf("          (&%####(//*/**************// (#%# (//*************////(###%#%%%(       ");
    gotoxy(ascii_art_x, ascii_art_y + 24);
    printf("     *#%######(((///*************///(  #%##  ((/////***********///((((#####%%##*. ");
    gotoxy(ascii_art_x, ascii_art_y + 25);
    printf(",#%%######((((/////*/*********////(          . (((((/////*********/////((((#########\n");
    gotoxy(ascii_art_x, ascii_art_y + 26);
    printf("(#(((((///////*************///((#,              *((///***********//////(((((#####\n");
    gotoxy(ascii_art_x, ascii_art_y + 27);
    printf("(((((////////*************////(#%/                 %#((///**********///////((((((##\n");
    gotoxy(55,35);
    printf("Thankyou for banking with us!!");
    gotoxy(52,37);
    printf("IIT Jodhpur Bank, The Bank of tommorow...");
  //  delay(750000);
    gotoxy(58,40);
    printf("Press any key to exit");
    getch();
}

int main() {
    endh();
    return 0;
}
