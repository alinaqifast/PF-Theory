/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/
#include <stdio.h>
#include <string.h>

int main() {
    int dailyLimit;
    int todaysTotal;
    int transactionAmount;
    int transactionsLastHour;
    char usualCountry[30];
    char currentCountry[30];

    // We are geatting the inputs, but in practice a good program will fetch data from database and process accordingly
    printf("Enter daily spending limit: ");
    scanf("%d", &dailyLimit);

    printf("Enter today's total spending so far: ");
    scanf("%d", &todaysTotal);

    printf("Enter current transaction amount: ");
    scanf("%d", &transactionAmount);

    printf("Enter number of transactions in the last hour: ");
    scanf("%d", &transactionsLastHour);

    printf("Enter customer's usual country: ");
    scanf("%s", usualCountry);

    printf("Enter transaction country: ");
    scanf("%s", currentCountry);

    // Rule 1: Check if total exceeds daily limit
    if (todaysTotal + transactionAmount > dailyLimit) {
        printf("Suspicious transaction: Daily spending limit exceeded.\n");
        return 0;
    }

    // Rule 2: Check if transaction is from a foreign country
    if (strcmp(usualCountry, currentCountry) != 0) {
        printf("Suspicious transaction: Transaction in unusual country.\n");
        return 0;
    }

    // Rule 3: Check if too many transactions in last hour
    if (transactionsLastHour > 3) {
        printf("Suspicious transaction: More than 3 transactions in the last hour.\n");
        return 0;
    }

    // Otherwise, allow the transaction
    todaysTotal += transactionAmount;
    printf("Transaction Successful.\n");
    printf("Updated total spending today: %d\n", todaysTotal);

    return 0;
}
