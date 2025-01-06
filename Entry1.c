#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>

#define pr 546000000
#define width 115
#define height 45

void delay(int microseconds) {
    usleep(microseconds);
}
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);//predefined function in conio.h for windows system but for unix based compilers have to define
}

void tempelate(){
    system("cls");
gotoxy(20,1);
printf("%c",201);
int i;
for( i=0; i<width-2; i++){
    printf("%c", 205);
}
printf("%c", 187);
printf("\n");
gotoxy(20,2);
for( i=0; i<height-2; i++){
    gotoxy(20,i+2);
    printf("%c", 186);
}
gotoxy(20+width-1, 2);
for( i=0; i<height-2; i++){
gotoxy(20+width-1, 2+i);
printf("%c", 186);
}
gotoxy(20, height);
printf("%c",200);
for( i=0; i<width-2; i++){
printf("%c", 205);
}
printf("%c",188);
gotoxy(62,3);
printf("Tatinator buggati year finder");
}

int main(){
  tempelate();
  gotoxy(56,22);
printf("Escaping the matrix...\n");
delay(750000);
int n;
system("cls");
tempelate();
gotoxy(25,7);
printf("Enter your yearly income(in INR)- ");
scanf("%d", &n);
gotoxy(25,11);
printf("Even if you don't spend a penny on anything even food or water \n");
delay(750000);
 n=n/2;
 gotoxy(25,13);
 system("cls");
 tempelate();
 gotoxy(25,11);
 printf("%d years %d years is the time you will have to slave in your best preferences to buy my buggati\n", (pr/n)+1, (pr/n)+1);
gotoxy(25,13);
 printf("You are a slave , slave for the matrix for that time");
getch();
getch();
return 0;
}
