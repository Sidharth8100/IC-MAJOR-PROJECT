#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define width 115
#define height 45

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void tempelate() {
    gotoxy(20, 1);
    printf("%c", 201);
    int i;
    for (i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n");
    gotoxy(20, 2);

    for (i = 0; i < height - 2; i++) {
        gotoxy(20, i + 2);
        printf("%c", 186);
    }
    gotoxy(20 + width - 1, 2);
    for (i = 0; i < height - 2; i++) {
        gotoxy(20 + width - 1, 2 + i);
        printf("%c", 186);
    }
    gotoxy(20, height);
    printf("%c", 200);
    for (i = 0; i < width - 2; i++) {
        printf("%c", 205);
    }
    printf("%c", 188);
    gotoxy(50, 5);
    printf("IIT Jodhpur Banking system");
}

typedef struct {
    char name[50];
    int accountNumber;
    float balance;
    float interestRate;
} Account;

Account account;

void deposit(float amount) {
    tempelate();
    account.balance += amount;
    gotoxy(40,20);
    printf("Deposited %.2f\n", amount);

    // Log the transaction
    FILE *file = fopen("HISTORY.txt", "a+");
    fprintf(file, "Deposit: %.2f\n", amount);
    fclose(file);
    system("cls");
}

void withdraw(float amount) {
    tempelate();
    gotoxy(40,20);
    if (amount > account.balance) {
        printf("Insufficient balance\n");
    } else {
        account.balance -= amount;
        printf("Withdrawn %.2f\n", amount);

        // Log the transaction
        FILE *file = fopen("HISTORY.txt", "a+");
        fprintf(file, "Withdrawal: %.2f\n", amount);
        fclose(file);
        system("cls");
    }
}

void applyInterest() {
    float interest = (account.balance * account.interestRate);
    account.balance += interest;

    // Log the interest
    FILE *file = fopen("HISTORY.txt", "a+");
    fprintf(file, "Interest: %.2f\n", interest);
    fclose(file);
}

void generateMonthlyStatement() {
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

    // Generate file name with date and time
    char fileName[50];
    strftime(fileName, sizeof(fileName), "statement_%Y%m%d%H%M%S.txt", localTime);

    FILE *file = fopen(fileName, "w");
    fprintf(file, "Monthly Statement\n");
    fprintf(file, "Date: %s", asctime(localTime));
    fprintf(file, "Name: %s\n", account.name);
    fprintf(file, "Account Number: %d\n", account.accountNumber);
    fprintf(file, "Principal Amount: %.2f\n", account.balance / (1 + account.interestRate));
    fprintf(file, "Interest Earned: %.2f\n", account.balance - (account.balance / (1 + account.interestRate)));
    fprintf(file, "Total Balance: %.2f\n", account.balance);
    fclose(file);

    printf("Monthly statement generated: %s\n", fileName);
}

int main() {
    tempelate();
    getchar();
    system("cls");

    int choice;
    float amount;

    gotoxy(40, 12);
    printf("Welcome to Savings Account\n");
    account.interestRate = 0.04; // Fixed interest rate to 4%

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
                scanf("%f", &amount);
                deposit(amount);
                applyInterest(); // Apply interest after deposit
                break;
            case 2:
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw(amount);
                break;
            case 3:
                generateMonthlyStatement();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 4.\n");
        }

    } while (choice != 4);

    return 0;
}










