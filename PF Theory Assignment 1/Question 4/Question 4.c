/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/
#include <stdio.h>

int main() {
    int c1, c2, c3, c4, c5;
    int firstRank, secondRank;
    int firstCount = 0, secondCount = 0;

    printf("Enter the ranks of your 5 cards (as numbers):\n");

    printf("Card 1: ");
    scanf("%d", &c1);
    printf("Card 2: ");
    scanf("%d", &c2);
    printf("Card 3: ");
    scanf("%d", &c3);
    printf("Card 4: ");
    scanf("%d", &c4);
    printf("Card 5: ");
    scanf("%d", &c5);

    firstRank = c1;
    firstCount++;

    // Check card 2
    if (c2 == firstRank) {
        firstCount++;
    } else {
        secondRank = c2;
        secondCount++;
    }

    // Check card 3
    if (c3 == firstRank) {
        firstCount++;
    } else {
        if (secondCount == 0) {
            secondRank = c3;
            secondCount++;
        } else if (c3 == secondRank) {
            secondCount++;
        }
    }

    // Check card 4
    if (c4 == firstRank) {
        firstCount++;
    } else {
        if (secondCount == 0) {
            secondRank = c4;
            secondCount++;
        } else if (c4 == secondRank) {
            secondCount++;
        }
    }

    // Check card 5
    if (c5 == firstRank) {
        firstCount++;
    } else {
        if (secondCount == 0) {
            secondRank = c5;
            secondCount++;
        } else if (c5 == secondRank) {
            secondCount++;
        }
    }

    // Decision
    if ((firstCount == 3 && secondCount == 2) || (firstCount == 2 && secondCount == 3)) {
        printf("You have a Full House!\n");
    } else {
        printf("This is not a Full House.\n");
    }

    return 0;
}
