/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/
#include <stdio.h>

int main() {
    int dayNum;

    printf("Enter a number between 1 and 7: ");
    scanf("%d", &dayNum);

    // Match number to day of the week
    if (dayNum == 1) {
        printf("Day is Monday\n");
    }
    else if (dayNum == 2) {
        printf("Day is Tuesday\n");
    }
    else if (dayNum == 3) {
        printf("Day is Wednesday\n");
    }
    else if (dayNum == 4) {
        printf("Day is Thursday\n");
    }
    else if (dayNum == 5) {
        printf("Day is Friday\n");
    }
    else if (dayNum == 6) {
        printf("Day is Saturday\n");
    }
    else if (dayNum == 7) {
        printf("Day is Sunday\n");
    }
    else {
        printf("Invalid input! Number not in range 1–7.\n");
    }

    return 0;
}
