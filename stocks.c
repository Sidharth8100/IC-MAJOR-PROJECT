#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

#define NUM_STOCKS 10
#define MIN_VALUE 100 // INR
#define MAX_VALUE 10000 // INR
#define FLUCTUATION_MIN -10
#define FLUCTUATION_MAX 10
#define MINUTES_PER_INTERVAL 1

// Structure to hold stock information
typedef struct {
    char name[20];
    double value;
    double growth_rate;
    int quantity_owned;
} Stock;

// Function to generate random percent fluctuation
double random_fluctuation() {
    return (rand() % (FLUCTUATION_MAX - FLUCTUATION_MIN + 1) + FLUCTUATION_MIN) / 100.0;
}

// Function to initialize stock data
void initialize_stocks(Stock stocks[], int num_stocks) {
    for (int i = 0; i < num_stocks; ++i) {
        sprintf(stocks[i].name, "Stock%d", i + 1);
        stocks[i].value = (double)(rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE);
        stocks[i].growth_rate = 0.0;
        stocks[i].quantity_owned = 0; // Initialize quantity owned to zero
    }
}

// Function to simulate stock values and growth rates
void simulate_stock_market(Stock stocks[], int num_stocks) {
    // Update stock values and growth rates
    for (int i = 0; i < num_stocks; ++i) {
        double fluctuation = random_fluctuation();
        stocks[i].growth_rate = fluctuation * 100.0;
        stocks[i].value *= (1 + fluctuation);
    }
}

// Function to buy stocks
void buy_stocks(Stock stocks[], int num_stocks) {
    int stock_index;
    int quantity;
    printf("Enter the index of the stock you want to buy (1-%d): ", num_stocks);
    scanf("%d", &stock_index);
    printf("Enter the quantity you want to buy: ");
    scanf("%d", &quantity);

    if (stock_index < 1 || stock_index > num_stocks) {
        printf("Invalid stock index.\n");
        return;
    }

    stock_index--; // Adjust for 0-based indexing
    if (stocks[stock_index].value * quantity > 0) {
        stocks[stock_index].quantity_owned += quantity;
        printf("Successfully purchased %d shares of %s.\n", quantity, stocks[stock_index].name);
    } else {
        printf("Insufficient funds to purchase.\n");
    }
}
void runstocks(){
Stock stocks[NUM_STOCKS];
    int choice;

    // Initialize stocks
    initialize_stocks(stocks, NUM_STOCKS);

    // Main menu loop
    while (1) {
        // Display menu options
        printf("\n1. View Stock Market\n");
        printf("2. Buy Stocks\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                simulate_stock_market(stocks, NUM_STOCKS);
                // Display current stock values after update
                printf("Current Stock Values:\n");
                for (int i = 0; i < NUM_STOCKS; ++i) {
                    printf("%s: INR %.2f  Quantity Owned: %d\n", stocks[i].name, stocks[i].value, stocks[i].quantity_owned);
                }
                break;
            case 2:
                buy_stocks(stocks, NUM_STOCKS);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }}

int main() {
    runstocks();

    return 0;
}

