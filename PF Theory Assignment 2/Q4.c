#include <stdio.h>

#define MAX 5   // maximum size of stack

// Function prototypes
void push(int stack[], int *top);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);

int main() {
    int stack[MAX];
    int top = -1;  // stack initially empty
    int choice;

    while (1) {
        printf("\n=== STACK MENU ===\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                push(stack, &top);
                break;
            case 2:
                pop(stack, &top);
                break;
            case 3:
                peek(stack, top);
                break;
            case 4:
                display(stack, top);
                break;
            case 5:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

// ===================== FUNCTION DEFINITIONS =====================

// PUSH function: adds an element to the top of the stack
void push(int stack[], int *top) {
    if (*top == MAX - 1) {
        printf("Stack Overflow! Cannot push more elements.\n");
        return;
    }

    int value;
    printf("Enter value to push: ");
    scanf("%d", &value);

    (*top)++;
    stack[*top] = value;
    printf("%d pushed to stack.\n", value);
}

// POP function: removes the top element
void pop(int stack[], int *top) {
    if (*top == -1) {
        printf("Stack Underflow! No elements to pop.\n");
        return;
    }

    int value = stack[*top];
    (*top)--;
    printf("Popped element: %d\n", value);
}

// PEEK function: displays the top element without removing it
void peek(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Top element: %d\n", stack[top]);
}

// DISPLAY function: shows all elements in the stack
void display(int stack[], int top) {
    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack elements (top to bottom):\n");
    for (int i = top; i >= 0; i--) {
        printf("%d\n", stack[i]);
    }
}
