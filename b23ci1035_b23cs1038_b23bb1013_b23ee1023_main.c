#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<string.h>

#define width 115
#define height 45
#define NUM_STOCKS 10
#define MIN_VALUE 100 // INR
#define MAX_VALUE 10000 // INR
#define FLUCTUATION_MIN -10
#define FLUCTUATION_MAX 10


FILE * fptr;
FILE *fptr2;
char fname[50];

long Acc_No;
long passcode;
long balance;

typedef struct {
    long account_number;
    long passcode;
    double balance;
} AccountInfo;

typedef struct {
    char name[20];
    double value;
    double growth_rate;
    int quantity_owned;
} Stock;

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);//predefined function in conio.h for windows system but for unix based compilers have to define
}
void delay(int microseconds) {
    usleep(microseconds);
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
printf("IIT Jodhpur Banking systum");
}
//void encryptDecrypt(char *data) {
  //  char key = ENCRYPTION_KEY;
   // size_t len = strlen(data);
    //int i;
   // for (i = 0; i < len; i++) {
    //    data[i] ^= key;
  //  }
//}
long generateRandomNumber(int numDigits) {
    long minRange = 1;
    long maxRange = 1;
    int i;
    for ( i = 1; i < numDigits; i++) {
        minRange *= 10;
        maxRange = maxRange * 10 + 9;
    }

    srand(time(NULL));

    long randomNumber = minRange + rand() % (maxRange - minRange + 1);

    return randomNumber;
}

void initialize_stocks(Stock stocks[], int num_stocks) {
    int i;
    for (i = 0; i < num_stocks; ++i) {
        sprintf(stocks[i].name, "Stock%d", i + 1);
        stocks[i].value = (double)(rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE);
        stocks[i].growth_rate = 0.0;
        stocks[i].quantity_owned = 0;
    }
}

double random_fluctuation() {
    return (rand() % (FLUCTUATION_MAX - FLUCTUATION_MIN + 1) + FLUCTUATION_MIN) / 100.0;
}

void simulate_stock_market(Stock stocks[], int num_stocks) {
    tempelate();
    int i;
    for (i = 0; i < num_stocks; ++i) {
        double previous_value = stocks[i].value;
        double fluctuation = random_fluctuation();
        stocks[i].growth_rate = fluctuation * 100.0;
        stocks[i].value *= (1 + fluctuation);

        double percentage_change = ((stocks[i].value - previous_value) / previous_value) * 100;
        gotoxy(40, 12 + i);
        printf("%s: INR %.2f  Quantity Owned: %d  Change: %.2f%%\n", stocks[i].name, stocks[i].value, stocks[i].quantity_owned, percentage_change);
    }
}

void buy_stocks(Stock stocks[], int num_stocks, double *balance) {
    tempelate();
    int stock_index;
    int quantity;
    gotoxy(40, 10);
    printf("\tEnter the index of the stock you want to buy (1-%d): ", num_stocks);
    scanf("%d", &stock_index);
    gotoxy(40, 11);
    printf("\tEnter the quantity you want to buy: ");
    scanf("%d", &quantity);

    if (stock_index < 1 || stock_index > num_stocks) {
        gotoxy(40, 14);
        printf("\tInvalid stock index.\n");
        return;
    }

    stock_index--;
    if (stocks[stock_index].value * quantity <= *balance) {
        stocks[stock_index].quantity_owned += quantity;
        *balance -= stocks[stock_index].value * quantity;
        gotoxy(40, 15);
        printf("\tSuccessfully purchased %d shares of %s.\n", quantity, stocks[stock_index].name);
    } else {
        gotoxy(40, 15);
        printf("\tInsufficient funds to purchase.\n");
    }
}

void sell_stocks(Stock stocks[], int num_stocks, double *balance) {
    tempelate();
    int stock_index;
    int quantity;
    gotoxy(40, 10);
    printf("\tEnter the index of the stock you want to sell (1-%d): ", num_stocks);
    scanf("%d", &stock_index);
    gotoxy(40, 11);
    printf("\tEnter the quantity you want to sell: ");
    scanf("%d", &quantity);

    if (stock_index < 1 || stock_index > num_stocks) {
        gotoxy(40, 14);
        printf("\tInvalid stock index.\n");
        return;
    }

    stock_index--;
    if (stocks[stock_index].quantity_owned >= quantity) {
        stocks[stock_index].quantity_owned -= quantity;
        *balance += stocks[stock_index].value * quantity;
        gotoxy(40, 15);
        printf("\tSuccessfully sold %d shares of %s.\n", quantity, stocks[stock_index].name);
    } else {
        gotoxy(40, 15);
        printf("\tInsufficient shares to sell.\n");
    }
}

double read_balance(long account_number) {
    FILE *file = fopen("acc_details.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 0.0;
    }

    AccountInfo account;
    while (fscanf(file, "%ld %ld %lf", &account.account_number, &account.passcode, &account.balance) == 3) {
        if (account.account_number == account_number) {
            fclose(file);
            return account.balance;
        }
    }

    fclose(file);
    printf("Account not found.\n");
    return 0.0;
}

void write_balance(long account_number, double balance) {
    FILE *file = fopen("acc_details.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    AccountInfo account;
    while (fscanf(file, "%ld %ld %lf", &account.account_number, &account.passcode, &account.balance) == 3) {
        if (account.account_number == account_number) {
            fprintf(temp, "%ld %ld %.2lf\n", account_number, account.passcode, balance);
        } else {
            fprintf(temp, "%ld %ld %.2lf\n", account.account_number, account.passcode, account.balance);
        }
    }

    fclose(file);
    fclose(temp);

    if (remove("acc_details.txt") != 0) {
        printf("Error deleting the original file.\n");
        return;
    }

    if (rename("temp.txt", "acc_details.txt") != 0) {
        printf("Error renaming the temporary file.\n");
        return;
    }
    gotoxy(40,24);

    printf("Balance updated successfully.\n");
}

void displayInsuranceSchemes() {
    tempelate();
    gotoxy(22, 6);
    printf("Insurance Schemes Offered:");
    gotoxy(22, 8);
    printf("1. Life Insurance");
    gotoxy(22, 9);
    printf("2. Health Insurance");
    gotoxy(22, 10);
    printf("3. Property Insurance");
    gotoxy(22, 11);
    printf("4. Vehicle Insurance");
    gotoxy(22, 12);
    printf("5. Travel Insurance");
        int option;
    gotoxy(22,14);
      printf("Enter your choice: ");
    scanf("%d", &option);

    // Handle user selection
    selectOption(option);
}
void displayLifeInsurance() {
    tempelate();
    gotoxy(22, 6);
    printf("Life Insurance Coverage:");
    gotoxy(22, 8);
    printf("- Financial protection for family members");
    gotoxy(22, 9);
    printf("- Covers funeral expenses");
    gotoxy(22, 10);
    printf("- Pays off debts");
    gotoxy(22,12);
    char ch;
    printf("At mere monthly payments of 123 p.m");
    gotoxy(22,13);
    printf("Would you like to sign up for it(y/n) ");
    long temppass;
    ch=getch();
    if(ch=='y'){
            gotoxy(22,15);
        printf("Confirm passcode- ");
        scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            gotoxy(22,17);
            printf("Re-try entering password ");
    scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }else{
            system("cls");
            gotoxy(55,8);
            printf("Intruder Alert ");
            gotoxy(55,10);
            printf("Logging out...");
            delay(750000);
            return 0;
        }
        }
    }
    else if(ch=='n'){
        gotoxy(22,15);
            printf("Thankyou for enquiring our services  ");
            gotoxy(22,16);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
    }
}

// Function to display what Health Insurance covers
void displayHealthInsurance() {
    tempelate();
    gotoxy(22, 6);
    printf("Health Insurance Coverage:");
    gotoxy(22, 8);
    printf("- Medical expenses for illnesses and injuries");
    gotoxy(22, 9);
    printf("- Hospitalization costs");
    gotoxy(22, 10);
    printf("- Prescription drugs");
     char ch;
    printf("At mere monthly payments of 123 p.m");
    gotoxy(22,13);
    printf("Would you like to sign up for it(y/n) ");
    long temppass;
    ch=getch();
    if(ch=='y'){
            gotoxy(22,15);
        printf("Confirm passcode- ");
        scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            gotoxy(22,17);
            printf("Re-try entering password ");
    scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }else{
            system("cls");
            gotoxy(55,8);
            printf("Intruder Alert ");
            gotoxy(55,10);
            printf("Logging out...");
            delay(750000);
            return 0;
        }
        }
    }
    else if(ch=='n'){
        gotoxy(22,15);
            printf("Thankyou for enquiring our services  ");
            gotoxy(22,16);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
    }
}

// Function to display what Property Insurance covers
void displayPropertyInsurance() {
    tempelate();
    gotoxy(22, 6);
    printf("Property Insurance Coverage:");
    gotoxy(22, 8);
    printf("- Protection for your home or property against damage or theft");
    gotoxy(22, 9);
    printf("- Coverage for personal belongings");
    gotoxy(22, 10);
    printf("- Liability protection");
     char ch;
    printf("At mere monthly payments of 486 p.m");
    gotoxy(22,13);
    printf("Would you like to sign up for it(y/n) ");
    long temppass;
    ch=getch();
    if(ch=='y'){
            gotoxy(22,15);
        printf("Confirm passcode- ");
        scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            balance=balance-486;
            rewind(fptr);
            long temp;
            while(fscanf(fptr, "%ld", &temp)!=EOF || temp!=Acc_No){
                fscanf(fptr, "%ld", &temp);
                fprintf(fptr, "%ld", balance);
            }
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            gotoxy(22,17);
            printf("Re-try entering password ");
    scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }else{
            system("cls");
            gotoxy(55,8);
            printf("Intruder Alert ");
            gotoxy(55,10);
            printf("Logging out...");
            delay(750000);
            return 0;
        }
        }
    }
    else if(ch=='n'){
        gotoxy(22,15);
            printf("Thankyou for enquiring our services  ");
            gotoxy(22,16);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
    }
}







// Function to display what Vehicle Insurance covers
void displayVehicleInsurance() {
    tempelate();
    gotoxy(22, 6);
    printf("Vehicle Insurance Coverage:");
    gotoxy(22, 8);
    printf("- Protection for your vehicle against accidents and theft");
    gotoxy(22, 9);
    printf("- Coverage for repairs or replacement");
    gotoxy(22, 10);
    printf("- Liability protection");
     char ch;
    printf("At mere monthly payments of 209 p.m");
    gotoxy(22,13);
    printf("Would you like to sign up for it(y/n) ");
    long temppass;
    ch=getch();
    if(ch=='y'){
            gotoxy(22,15);
        printf("Confirm passcode- ");
        scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            gotoxy(22,17);
            printf("Re-try entering password ");
    scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }else{
            system("cls");
            gotoxy(55,8);
            printf("Intruder Alert ");
            gotoxy(55,10);
            printf("Logging out...");
            delay(750000);
            return 0;
        }
        }
    }
    else if(ch=='n'){
        gotoxy(22,15);
            printf("Thankyou for enquiring our services  ");
            gotoxy(22,16);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
    }
}

// Function to display what Travel Insurance covers
void displayTravelInsurance() {
    tempelate();
    gotoxy(22, 6);
    printf("Travel Insurance Coverage:");
    gotoxy(22, 8);
    printf("- Trip cancellation and interruption coverage");
    gotoxy(22, 9);
    printf("- Emergency medical and dental coverage");
    gotoxy(22, 10);
    printf("- Lost or delayed baggage coverage");
     char ch;
    printf("At mere monthly payments of 121 p.m");
    gotoxy(22,13);
    printf("Would you like to sign up for it(y/n) ");
    long temppass;
    ch=getch();
    if(ch=='y'){
            gotoxy(22,15);
        printf("Confirm passcode- ");
        scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            balance-=121;
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            gotoxy(22,17);
            printf("Re-try entering password ");
    scanf("%ld", &temppass);
        if(temppass==passcode){
                system("cls");
        tempelate();
        gotoxy(55,7);
            printf("Thankyou for availing our services ");
            balance-=121;
            gotoxy(55,9);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
        }
        else{
            system("cls");
            gotoxy(55,8);
            printf("Intruder Alert ");
            gotoxy(55,10);
            printf("Logging out...");
            delay(750000);
            return 0;
        }
        }
    }
    else if(ch=='n'){
        gotoxy(22,15);
            printf("Thankyou for enquiring our services  ");
            gotoxy(22,16);
            printf("Taking you back to the home page...");
            delay(750000);
            options();
    }

}
// Function to handle selection using switch-case mechanism
void selectOption(int option) {
    switch (option) {
        case 1:
            tempelate();
            gotoxy(22, 6);
            printf("You have selected: Life Insurance");
            displayLifeInsurance();
            break;
        case 2:
            tempelate();
            gotoxy(22, 6);
            printf("You have selected: Health Insurance");
            displayHealthInsurance();
            break;
        case 3:
            tempelate();
            gotoxy(22, 6);
            printf("You have selected: Property Insurance");
            displayPropertyInsurance();
            break;
        case 4:
            tempelate();
            gotoxy(22, 6);
            printf("You have selected: Vehicle Insurance");
            displayVehicleInsurance();
            break;
        case 5:
            tempelate();
            gotoxy(22, 6);
            printf("You have selected: Travel Insurance");
            displayTravelInsurance();
            break;
        default:
            tempelate();
            gotoxy(22, 6);
            printf("Invalid option");
    }
}
long encrypt(long input) {
    // Define a secret key for encryption
    long key = 1234567890;
    // Perform encryption using XOR operation with the key
    return input ^ key;
}

// Function to decrypt a long type encrypted object
long decrypt(long encrypted) {
    // Define the same secret key used for encryption
    long key = 1234567890;
    // Perform decryption using XOR operation with the key
    return encrypted ^ key;
}



void displayCustomerSupport() {
    system("cls");
    tempelate();
    gotoxy(40, 12);
    printf("\033[1;32mCustomer Support\033[0m\n"); // Green color
    gotoxy(40, 15);
    printf("You can contact us on given 24*7 service number : +91 8529364522\n");
    gotoxy(40, 16);
    printf("You can also mail us on following Emails: B23EE1023@iitj.ac.in, B23CI1035@iitj.ac.in\n");
    gotoxy(40, 17);
    printf("Address: O-4, IIT Jodhpur, NH65, Nagaur Road, Karwar, Rajasthan\n");
    gotoxy(40, 20);
    printf("\033[1;32mPress any key to exit...\033[0m"); // Green color
    getch();
    options();
}
fclose(fptr);

typedef struct {
    char name[50];
    long accountNumber;
    long passcode;
    long balance;
} Account;

Account senderAccount, receiverAccount;

void loadAccountDetails(long accountNumber, Account *account) {
    FILE *file = fopen("acc_details.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%ld %ld %ld", &account->accountNumber, &account->passcode, &account->balance) != EOF) {
        if (account->accountNumber == accountNumber) {
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Account not found for account number: %ld\n", accountNumber);
    exit(EXIT_FAILURE);
}

void saveAccountDetails(Account *account) {
    FILE *file = fopen("acc_details.txt", "r+");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(EXIT_FAILURE);
    }

    FILE *tempFile = fopen("temp.txt", "a+");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    long fileAccountNumber;
    long filePasscode;
    long fileBalance;

    while (fscanf(file, "%ld %ld %ld", &fileAccountNumber, &filePasscode, &fileBalance) != EOF) {
        if (fileAccountNumber == account->accountNumber) {
            fprintf(tempFile, "%-10ld %-10ld %ld\n", account->accountNumber, account->passcode, account->balance);
        } else {
            fprintf(tempFile, "%-10ld %-10ld %ld\n", fileAccountNumber, filePasscode, fileBalance);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("acc_details.txt");
    rename("temp.txt", "acc_details.txt");
}

void transferMoney() {
    long senderAccountNumber, receiverAccountNumber;
    long amount;

    gotoxy(40, 11);
    printf("Enter sender account number: ");
    scanf("%ld", &senderAccountNumber);
    loadAccountDetails(senderAccountNumber, &senderAccount);

    gotoxy(40, 12);
    printf("Enter receiver account number: ");
    scanf("%ld", &receiverAccountNumber);
    loadAccountDetails(receiverAccountNumber, &receiverAccount);

    gotoxy(40, 14);
    printf("Enter amount to transfer: ");
    scanf("%ld", &amount);

    if (amount > senderAccount.balance) {
        gotoxy(40, 16);
        printf("Insufficient balance in sender's account.\n");
        return;
    }

    senderAccount.balance -= amount;
    receiverAccount.balance += amount;

    saveAccountDetails(&senderAccount);
    saveAccountDetails(&receiverAccount);

    gotoxy(40, 17);
    printf("Transfer successful.\n");
    delay(750000);
        gotoxy(40, 20);
    printf("\033[1;32mPress any key to exit...\033[0m"); // Green color
    getch();
    options();


}
long passcodez;
void endh(){
    gotoxy(20, 1);
    printf("%c", 201);
    int i;
    for ( i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    for ( i = 0; i < height - 2; i++) {
        gotoxy(20, i + 2);
        printf("%c", 186);
        int j;
        for ( j = 0; j < width - 2; j++) {
            printf(" ");
        }
        printf("%c", 186);
    }
    gotoxy(20, height);
    printf("%c", 200);
    for ( i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
    gotoxy(62, 5);
    printf("IIT Jodhpur Banking systum");


    int ascii_art_x = 30;
    int ascii_art_y = 5;

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
    delay(750000);
    gotoxy(58,40);
    printf("Press any key to exit");
    getch();
}
void updateacc(long acc_number, long balance_INR, long balance_USD, long balance_EUR, long balance_GBP) {
    FILE *fptr = fopen("acc_details.txt", "r+");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    long file_acc_number, file_passcode, file_balance_INR, file_balance_USD, file_balance_EUR, file_balance_GBP;

    // Move file pointer to the start of the file
    fseek(fptr, 0, SEEK_SET);

    while (fscanf(fptr, "%ld %ld %ld %ld %ld %ld", &file_acc_number, &file_passcode, &file_balance_INR, &file_balance_USD, &file_balance_EUR, &file_balance_GBP) != EOF) {
        if (file_acc_number == acc_number) {
            fseek(fptr, -1 * (7 +dig(file_acc_number) + dig(file_passcode) + dig(file_balance_INR) + dig(file_balance_USD) + dig(file_balance_EUR) + dig(file_balance_GBP) ), SEEK_CUR); // Move file pointer back to the start of the line
            fprintf(fptr, "%ld %ld %ld %ld %ld %ld\n", file_acc_number, file_passcode, balance_INR, balance_USD, balance_EUR, balance_GBP);
            break;
        }
    }

    fclose(fptr);
}

Account account;

void loadAccountDetailsavings(long inputAccountNumber) {
    FILE *file = fopen("acc_details.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }

    long fileAccountNumber;
    long filePasscode;
    long fileBalance;

    while (fscanf(file, "%ld %ld %ld", &fileAccountNumber, &filePasscode, &fileBalance) != EOF) {
        if (fileAccountNumber == inputAccountNumber) {
            account.accountNumber = fileAccountNumber;
            account.passcode = filePasscode;
            account.balance = fileBalance;
            break;
        }
    }

    fclose(file);
}

void saveAccountDetailsavings() {
    FILE *originalFile = fopen("acc_details.txt", "r");
    if (originalFile == NULL) {
        printf("Error opening the original file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_acc_details.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening the temporary file.\n");
        fclose(originalFile);
        return;
    }

    long fileAccountNumber;
    long filePasscode;
    long fileBalance;
    long originalFilePosition;

    while (fscanf(originalFile, "%ld %ld %ld", &fileAccountNumber, &filePasscode, &fileBalance) != EOF) {
        if (fileAccountNumber == account.accountNumber) {
            fprintf(tempFile, "%ld %ld %ld\n", account.accountNumber, account.passcode, account.balance);
        } else {
            fprintf(tempFile, "%ld %ld %ld\n", fileAccountNumber, filePasscode, fileBalance);
        }
    }

    fclose(originalFile);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove("acc_details.txt");
    rename("temp_acc_details.txt", "acc_details.txt");
}


void deposit(long amount) {
    tempelate();
    account.balance += amount;
    saveAccountDetailsavings();

    gotoxy(40, 20);
    printf("Deposited %ld\n", amount);

    FILE *file = fopen("HISTORY.txt", "a+");
    fprintf(file, "Deposit: %ld\n", amount);
    fclose(file);
    system("cls");
}

void withdraw(long amount) {
    tempelate();
    if (amount > account.balance) {
        printf("Insufficient balance\n");
    } else {
        account.balance -= amount;
        saveAccountDetailsavings();

        printf("Withdrawn %ld\n", amount);

        FILE *file = fopen("HISTORY.txt", "a+");
        fprintf(file, "Withdrawal: %ld\n", amount);
        fclose(file);
        system("cls");
    }
}

void applyInterest() {
    float interestRate = 0.005;
    long interest = (long)(account.balance * interestRate);
    account.balance += interest;
    saveAccountDetailsavings();

    FILE *file = fopen("HISTORY.txt", "a+");
    fprintf(file, "Interest: %ld\n", interest);
    fclose(file);
}

void generateMonthlyStatement() {
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

    char fileName[50];
    strftime(fileName, sizeof(fileName), "statement_%Y%m%d%H%M%S.txt", localTime);

    FILE *file = fopen(fileName, "w");
    fprintf(file, "Monthly Statement\n");
    fprintf(file, "Date: %s", asctime(localTime));
    fprintf(file, "Account Number: %ld\n", account.accountNumber);
    fprintf(file, "Total Balance: %ld\n", account.balance);
    fclose(file);

    printf("Monthly statement generated: %s\n", fileName);
}

int dig(long phalana){
int a=0;
while(phalana!=0){
    phalana=phalana/10;
    a++;
}
return a;
}

// Function to perform currency exchange
void exchangeCurrency(long passcodez, int choice) {
    system("cls");
    double amount, result;
    gotoxy(40,25);
    printf("Enter amount to exchange: ");
    scanf("%lf", &amount);

    long file_acc_number, file_balance_INR, file_balance_USD, file_balance_EUR, file_balance_GBP, file_passcode;

    FILE *fptr = fopen("acc_details.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file.\n");
        return;
    }
    long acc_number=Acc_No;

    while (fscanf(fptr, "%ld %ld %ld %ld %ld %ld", &file_acc_number, &file_passcode, &file_balance_INR, &file_balance_USD, &file_balance_EUR, &file_balance_GBP) != EOF) {
        if (file_passcode == encrypt(passcodez)) {
            // Perform currency exchange based on user's choice
            switch (choice) {
                case 1:
                    result = amount * 75.0; // Example conversion rate
                    if (file_balance_USD - amount >= 0) {
                        file_balance_INR += result;
                        file_balance_USD -= amount;
                        printf("Amount in INR: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in USD.\n");
                    }
                    break;
                case 2:
                    result = amount * 88.0; // Example conversion rate
                    if (file_balance_EUR - amount >= 0) {
                        file_balance_INR += result;
                        file_balance_EUR -= amount;
                        printf("Amount in INR: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in EUR.\n");
                    }
                    break;
                case 3:
                    result = amount * 103.0; // Example conversion rate
                    if (file_balance_GBP - amount >= 0) {
                        file_balance_INR += result;
                        file_balance_GBP -= amount;
                        printf("Amount in INR: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in GBP.\n");
                    }
                    break;
                case 4:
                    result = amount / 75.0; // Example conversion rate
                    if (file_balance_INR - amount >= 0) {
                        file_balance_INR -= amount;
                        file_balance_USD += result;
                        printf("Amount in USD: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in INR.\n");
                    }
                    break;
                case 5:
                    result = amount / 88.0; // Example conversion rate
                    if (file_balance_INR - amount >= 0) {
                        file_balance_INR -= amount;
                        file_balance_EUR += result;
                        printf("Amount in EUR: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in INR.\n");
                    }
                    break;
                case 6:
                    result = amount / 103.0; // Example conversion rate
                    if (file_balance_INR - amount >= 0) {
                        file_balance_INR -= amount;
                        file_balance_GBP += result;
                        printf("Amount in GBP: %.2lf\n", result);
                    } else {
                        printf("Insufficient balance in INR.\n");
                    }
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
            // Update account details in file with new balances
            updateacc(acc_number, file_balance_INR, file_balance_USD, file_balance_EUR, file_balance_GBP);
            break;
        }
    }

}
void currency_exch(){

    int choice;

    printf("Enter account number: ");
    scanf("%ld", &passcodez);

    printf("1. Exchange USD to INR\n");
    printf("2. Exchange EUR to INR\n");
    printf("3. Exchange GBP to INR\n");
    printf("4. Exchange INR to USD\n");
    printf("5. Exchange INR to EUR\n");
    printf("6. Exchange INR to GBP\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    exchangeCurrency(passcodez, choice);
}

void signin(){
gotoxy(68,9);

    printf("Sign In-");
    delay(500000);
    gotoxy(60, 11);
    system("cls");
    tempelate();
    gotoxy(60, 5);
   printf(" Enter Bank Account Number:");
   gotoxy(62,7);
   scanf("%ld", &Acc_No);
   getchar();
    long temp_acc;
   while(1){
    if(fscanf( fptr ,"%ld", &temp_acc)!=EOF){
    if(Acc_No==temp_acc){
        break;
    }
    }
    else{
        system("cls");
        gotoxy(48,5);
        printf("Account does not exist, Please recheck the account number entered-");
        tempelate();
        gotoxy(60, 7);
        printf(" Please Re-enter Bank Account Number:");
        gotoxy(62,9);
        scanf("%ld", &Acc_No);
        fseek(fptr, 0, SEEK_SET);
        continue;
    }}
   gotoxy(62, 9);
   printf("Enter 6-digit Passcode");
   gotoxy(62,11);
   scanf("%ld", &passcode);
   getchar();
   fscanf( fptr ,"%ld", &temp_acc);
   if(passcode==decrypt(temp_acc)){
    delay(500000);
   }else{
    while(1){
    system("cls");
    tempelate();
    gotoxy(62,5);
    printf("Enter the passcode again-");
    scanf("%ld", &passcode);
    if(passcode==decrypt(temp_acc)){
        break;
    }
    }
   }
   fscanf(fptr, "%ld", &balance);
       gotoxy(68,13);
       printf("Logging in...");
       delay(750000);
       fclose(fptr);
        options();
        fptr=fopen("acc_details.txt", "r+");
}
void insurance(){
}


void displayOptions() {
    system("cls");
    tempelate();
    gotoxy(21, 7);
    printf("Services Offered:");
    gotoxy(21, 9);
    printf("1. Savings Accounts: Earn interest on your savings while keeping your money safe.");
    gotoxy(21, 10);
    printf("2. Current Accounts: Manage your day-to-day transactions conveniently.");
    gotoxy(21, 11);
    printf("3. Stocks and Investments: Explore opportunities to grow your wealth through investments.");
    gotoxy(21, 12);
    printf("4. Digital Banking: Bank anytime, anywhere with our online and mobile banking services.");
    gotoxy(21, 13);
    printf("5. Customer Support: Receive assistance and guidance from our dedicated customer support team.");
    gotoxy(21, 14);
    printf("6. Foreign Exchange Services: Exchange currencies for international transactions and travel.");
    gotoxy(21, 15);
    printf("7. Insurance Products: Protect yourself and your assets with our range of insurance offerings.");
    gotoxy(21,16);
    printf("8. Exit Securely");
}

void handleOption(int option) {
    switch(option) {
        case 1:
            gotoxy(21,21);
            printf("You chose Savings Accounts");
            long inputAccountNumber;
            gotoxy(21,22);
    printf("Enter your account number: ");
    scanf("%ld", &inputAccountNumber);

    loadAccountDetailsavings(inputAccountNumber);

    tempelate();
    getchar();
    system("cls");

    int choice;
    long amount;

    gotoxy(40, 12);
    printf("Welcome to Savings Account\n");

    do {
        tempelate();
        gotoxy(40, 15);
        printf("1. Deposit\n");
        gotoxy(40, 16);
        printf("2. Withdraw\n");
        gotoxy(40, 17);
        printf("3. Generate Monthly Statement\n");
        gotoxy(40, 18);
        printf("4. Exit\n");
        gotoxy(40, 19);
        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);
        system("cls");

        tempelate();
        gotoxy(50, 20);
        switch (choice) {
            case 1:
                printf("Enter amount to deposit: ");
                scanf("%ld", &amount);
                deposit(amount);
                applyInterest();
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%ld", &amount);
                withdraw(amount);
                break;
            case 3:
                generateMonthlyStatement();
                break;
            case 4:
                printf("Exiting...\n");
                delay(500000);
                options();
                break;
            default:
                gotoxy(40,25);
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }

    } while (choice != 4);


            break;
        case 2:
            gotoxy(21,21);
            printf("You chose Current Accounts\n");
            tempelate();
            gotoxy(55,9);
            printf("This site is under construction...");
            delay(750000);
            gotoxy(55,11);
            printf("Taking you back to the options page");
            delay(500000);
            options();
            break;

        case 3:
            gotoxy(21,21);
            printf("You chose Stocks and Investments\n");
            Stock stocks[NUM_STOCKS];
    double balance;
    long account_number;

    srand(time(NULL)); // Seed for random number generation

    initialize_stocks(stocks, NUM_STOCKS);

    tempelate();

    // Prompt for account number
    gotoxy(40, 8);
    printf("Enter your account number: ");
    scanf("%ld", &account_number);

    // Read balance associated with the account number
    balance = read_balance(account_number);

    while (1) {
        gotoxy(40, 10);
        printf(" 1. View Stock Market\n");
        gotoxy(40, 11);
        printf(" 2. Buy Stocks\n");
        gotoxy(40, 12);
        printf(" 3. Sell Stocks\n");
        gotoxy(40, 13);
        printf(" 4. Exit\n");
        gotoxy(40, 14);
        printf(" Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                simulate_stock_market(stocks, NUM_STOCKS);
                gotoxy(40,25);
                printf("Press Enter to return to the main menu...");
                getch();
                getch();
                system("cls");
                tempelate();
                break;
            case 2:
                system("cls");
                buy_stocks(stocks, NUM_STOCKS, &balance);
                write_balance(account_number, balance); // Write updated balance to file
                system("cls");
                tempelate();
                break;
            case 3:
                system("cls");
                sell_stocks(stocks, NUM_STOCKS, &balance);
                write_balance(account_number, balance); // Write updated balance to file
                system("cls");
                tempelate();
                break;
            case 4:
                write_balance(account_number, balance); // Write final balance before exiting
                exit(0);
            default:
                gotoxy(40, 20);
                printf("Invalid choice. Please try again.\n");
        }
    }

            break;
        case 4:
            gotoxy(21,21);
            printf("You chose Digital Banking\n");
            tempelate();
    transferMoney();
            break;

        case 5:
            gotoxy(21,21);
            printf("You chose Customer Support\n");
            displayCustomerSupport();
            break;
        case 6:
            gotoxy(21,21);
            printf("You chose Foreign Exchange Services\n");
            currency_exch();
            break;
        case 7:
            gotoxy(21,21);
            printf("You chose Insurance Products\n");
            displayInsuranceSchemes();
            break;
        case 8:
            gotoxy(21,21);
            printf("Exitting securely...");
            delay(500000);
            endh();
            break;


        default:
            printf("Invalid option\n");
    }
}
void options(){
 tempelate();
    displayOptions();

    int option;
    gotoxy(21, 19);
    printf("Enter your choice: ");
    scanf("%d", &option);
    handleOption(option);


    getchar();}


int main() {

fptr=fopen("acc_details.txt", "a+");
fptr2=fopen("personal_details.txt", "a+");
fseek(fptr,0, SEEK_SET);
fseek(fptr2,0, SEEK_SET);
    char ch;
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
printf("IIT Jodhpur Banking systum");
gotoxy(60,5);
delay(500000);
printf("Are you already an user?(y/n)");
gotoxy(74,7);
ch=getch();
if(ch=='y' || ch=='Y'){
    gotoxy(68,9);

    printf("Sign In-");
    delay(1000000);
    signin();
//main screen   ******************************************************************************************************************************


}
 else if(ch=='n' || ch=='N'){
system("cls");
tempelate();
gotoxy(21,6);
printf("Welcome to IIT Jodhpur Bank, where we blend innovation with tradition to offer you a seamless banking experience");
gotoxy(21,7);
 printf("As a premier financial institution, we pride ourselves on our commitment to excellence, integrity, ");
 gotoxy(21,8);
 printf("and customer satisfaction.");
gotoxy(21,10);
printf("At IIT Jodhpur Bank, we understand that each customer is unique, with diverse financial needs and aspirations.");
gotoxy(21,11);
printf("Whether you're a student, faculty member, staff, or a resident of the vibrant Jodhpur community we're here to ");
gotoxy(21,12);
printf("serve with personalized solutions tailored to your requirements.");
gotoxy(21,14);
printf("Experience the difference with IIT Jodhpur Bank where innovation meets tradition, and your financial well-being");
gotoxy(21,15);
printf("is our top priority. Join us today and embark on a journey towards financial success and prosperity.");
delay(750000);
gotoxy(55,18);
printf("Would you like to check our services- (y/n) ");
ch=getch();
if(ch=='y' || ch=='Y'){
    system("cls");
    tempelate();
    gotoxy(25, 6);
    printf("Services Offered:");
    gotoxy(25, 8);
    printf("1. Savings Accounts: Earn interest on your savings while keeping your money safe.");
    gotoxy(25, 9);
    printf("2. Current Accounts: Manage your day-to-day transactions conveniently.");
    gotoxy(25, 10);
    printf("3. Loans: Access financial support for your various needs with flexible repayment options.");
    gotoxy(25, 11);
    printf("4. Stocks and Investments: Explore opportunities to grow your wealth through investments.");
    gotoxy(25, 12);
    printf("5. Digital Banking: Bank anytime, anywhere with our online and mobile banking services.");
    gotoxy(25, 13);
    printf("6. Debit and Credit Cards: Enjoy the convenience of cashless transactions with our cards.");
    gotoxy(25, 14);
    printf("7. Customer Support: Receive assistance and guidance from our dedicated customer support team.");
    gotoxy(25, 15);
    printf("8. Foreign Exchange Services: Exchange currencies for international transactions and travel.");
    gotoxy(25, 16);
    printf("9. Insurance Products: Protect yourself and your assets with our range of insurance offerings.");
    delay(750000);
    gotoxy(48, 19);
    printf("Would you like to sign up for our services(y/n)");
    gotoxy(55,20);
    char ch2=getch();
    if(ch2=='y'|| ch2=='Y'){
        system("cls");
        tempelate();
        gotoxy(72,5);
        printf("Sign up-");
        gotoxy(55,7);
        printf("Enter your details below:");
        gotoxy(55,9);
        printf("Enter your First Name- ");
        char lname[50];
        char DOB[15];
        fgets(fname,50, stdin);
        fname[strlen(fname)-1]='\0';
        gotoxy(55,10);
        printf("Enter your Last Name- ");
        fgets(lname,50, stdin);
        lname[strlen(lname)-1]='\0';
        gotoxy(55, 11);
        printf("Enter your Date of Birth (dd/mm/yyyy)  ");
        fgets(DOB, 15, stdin);
        DOB[strlen(DOB)+1]='\0';
        system("cls");
        tempelate();
        gotoxy(65,5);
        printf("Hello, %s ", fname);
        gotoxy(55,7);
        printf("Let's set you up further...");
        gotoxy(55,9);
        printf("Generating your account number...");
        delay(750000);
        Acc_No=generateRandomNumber(10);
        gotoxy(55,9);
        printf("Your Account number is %ld", Acc_No );
        gotoxy(55, 11);
        printf("Would you like an randomly generated passcode(y/n) ");
        char ch3=getch();
        gotoxy(55,13);
        if(ch3=='y'){
                passcode= generateRandomNumber(6);
            printf("Your passcode is %ld", passcode);
            gotoxy(55,14);
            printf("Please secure the passcode and press any key ");
            getch();
            gotoxy(55,16);
            printf("Taking you back to Sign-in page");
            delay(750000);
        }
        else if(ch3=='n'){
            gotoxy(55,13);
            printf("Enter your custom passcode(6-digits)- ");
            scanf("%ld", &passcode);}

            fprintf(fptr ,"%ld ",Acc_No );
            long encrypted;
            encrypted=encrypt(passcode);
            fprintf(fptr ,"%ld ", encrypted);
            fprintf(fptr ,"10000 ");
            fprintf(fptr ,"%c", '\n');
            balance=10000;

            fprintf(fptr2, "%s ", fname);
            fprintf(fptr2, "%s ", lname);
            int a=strlen(DOB);
            DOB[a+1]='\n';
            fprintf(fptr2, "%s", DOB);
            fclose(fptr);
            fclose(fptr2);
            fptr=fopen("acc_details.txt", "a+");
            fptr2=fopen("personal_details.txt", "a+");
            fseek(fptr,0,SEEK_SET);
            fseek(fptr2,0,SEEK_SET);
            signin();

        }
        else if(ch2=='n' ){
            system("cls");
            tempelate();
            gotoxy(40,7);
            printf("Thank you for enquiring in our bank, we hope to see you again!!");
            endh();
        }
    }
    else if(ch=='n' || ch=="N"){
        system("cls");
            tempelate();
            gotoxy(40,7);
            printf("Thank you for enquiring in our bank, we hope to see you again!!");
            endh();
    }
}

fclose(fptr);
fclose(fptr2);
    return 0;
}



