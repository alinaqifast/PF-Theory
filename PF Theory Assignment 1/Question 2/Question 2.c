/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/
#include <stdio.h>

int main() {
    float xCoord, yCoord;

    printf("Coordinates are written as (x, y)\n");
    printf("Enter value for x: ");
    scanf("%f", &xCoord);

    printf("Enter value for y: ");
    scanf("%f", &yCoord);

    if (xCoord > 0 && yCoord > 0) {
        printf("The point is in Quadrant I");
    }
    else if (xCoord > 0 && yCoord < 0) {
        printf("The point is in Quadrant IV");
    }
    else if (xCoord < 0 && yCoord > 0) {
        printf("The point is in Quadrant II");
    }
    else if (xCoord < 0 && yCoord < 0) {
        printf("The point is in Quadrant III");
    }
    else {
        printf("The point lies on one of the axes!");
    }

    return 0;
}
