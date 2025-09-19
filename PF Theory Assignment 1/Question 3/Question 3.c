/*

NAME: ALI NAQI KHOSO
ROLL NO: 25K-0989
CLASS/SECTION: BS(CS)-1C

*/
#include <stdio.h>

int main() {
    int userAge;
    char visionTest, theoryTest, roadTest, medicalProof;

    printf("Enter your age: ");
    scanf("%d", &userAge);

    if (userAge < 18) {
        printf("You are not old enough to apply for a license!\n");
    }
    else {
        printf("Did you pass your eyesight test? (P/F): ");
        scanf(" %c", &visionTest);

        if (visionTest == 'f' || visionTest == 'F') {
            printf("You need corrective glasses before applying!\n");
        }
        else {
            printf("Did you pass your written/theory test? (P/F): ");
            scanf(" %c", &theoryTest);

            if (theoryTest == 'f' || theoryTest == 'F') {
                printf("You must retake the written test!\n");
            }
            else {
                printf("Did you pass your driving/road test? (P/F): ");
                scanf(" %c", &roadTest);

                if (roadTest == 'f' || roadTest == 'F') {
                    printf("Not eligible for license, road test failed.\n");
                }
                else {
                    if (userAge < 60) {
                        printf("Congratulations! You qualify for a driving license.\n");
                    }
                    else {
                        printf("Do you hold a valid medical certificate? (Y/N): ");
                        scanf(" %c", &medicalProof);

                        if (medicalProof == 'y' || medicalProof == 'Y') {
                            printf("Congratulations! You qualify for a driving license.\n");
                        }
                        else {
                            printf("Sorry, you cannot get a license without medical approval.\n");
                        }
                    }
                }
            }
        }
    }

    return 0;
}
