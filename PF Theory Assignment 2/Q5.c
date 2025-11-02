#include <stdio.h>
#include <string.h>

// Function prototypes
void encodeMessage(char message[]);
void decodeMessage(char message[]);
void reverseString(char str[]);
char toggleBits(char ch);

int main() {
    char message[200];
    int choice;

    while (1) {
        printf("\n=== TCS Secure Message Tool ===\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nEnter message to ENCODE: ");
                scanf(" %[^\n]", message);
                encodeMessage(message);
                break;

            case 2:
                printf("\nEnter message to DECODE: ");
                scanf(" %[^\n]", message);
                decodeMessage(message);
                break;

            case 3:
                printf("Exiting system...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}



// ======================= FUNCTION DEFINITIONS =======================

// Reverse the string
void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}



// Toggle 2nd and 5th bits of a character
char toggleBits(char ch) {
    ch = ch ^ (1 << 1); 
    ch = ch ^ (1 << 4);
    return ch;
}



// Encode function
void encodeMessage(char message[]) {
    reverseString(message);  // reverse

    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]);  // toggle bits
    }

    printf("\nEncoded Message: %s\n", message);
}



// Decode function
void decodeMessage(char message[]) {
    // toggle bits again to untoggle
    for (int i = 0; message[i] != '\0'; i++) {
        message[i] = toggleBits(message[i]);
    }

    // reverse the string again
    reverseString(message);

    printf("\nDecoded Message: %s\n", message);
}
