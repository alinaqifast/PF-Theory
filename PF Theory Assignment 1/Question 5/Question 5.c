/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/

#include <stdio.h>

int main() {
    int freq0 = 0, freq1 = 0, freq2 = 0, freq3 = 0, freq4 = 0;
    int freq5 = 0, freq6 = 0, freq7 = 0, freq8 = 0, freq9 = 0;
    int input;

    do {
        printf("Enter a digit (0–9). Enter anything else to stop: ");
        scanf("%d", &input);

        if (input == 0) {
            freq0++;
        } else if (input == 1) {
            freq1++;
        } else if (input == 2) {
            freq2++;
        } else if (input == 3) {
            freq3++;
        } else if (input == 4) {
            freq4++;
        } else if (input == 5) {
            freq5++;
        } else if (input == 6) {
            freq6++;
        } else if (input == 7) {
            freq7++;
        } else if (input == 8) {
            freq8++;
        } else if (input == 9) {
            freq9++;
        }
    } while (input >= 0 && input <= 9);

    printf("\nDigit   |  Times Entered\n");
    printf("   0    |       %d\n", freq0);
    printf("   1    |       %d\n", freq1);
    printf("   2    |       %d\n", freq2);
    printf("   3    |       %d\n", freq3);
    printf("   4    |       %d\n", freq4);
    printf("   5    |       %d\n", freq5);
    printf("   6    |       %d\n", freq6);
    printf("   7    |       %d\n", freq7);
    printf("   8    |       %d\n", freq8);
    printf("   9    |       %d\n", freq9);

    return 0;
}
