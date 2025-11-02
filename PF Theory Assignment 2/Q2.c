#include <stdio.h>
#include <string.h>

// Function declarations
void getCustomerInfo(char name[], char cnic[]);
void displayInventory(int codes[], int quantities[], int prices[], int size);
void addToCart(int codes[], int quantities[], int prices[], int cart[], int cartQty[], int size);
void updateInventory(int quantities[], int index, int qty);
void displayTotalBill(int prices[], int cartQty[], int size);
void showInvoice(char name[], char cnic[], int codes[], int prices[], int cart[], int cartQty[], int size);

int main() {
    int productCodes[4] = {1, 2, 3, 4};
    int quantities[4] = {50, 10, 20, 8};
    int prices[4] = {100, 200, 300, 150};
    int cart[4] = {0};
    int cartQty[4] = {0};
    char customerName[50];
    char customerCNIC[20];

    int choice;

    while (1) {
        printf("\n===== Supermarket Menu =====\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            getCustomerInfo(customerName, customerCNIC);
        } 
        else if (choice == 2) {
            displayInventory(productCodes, quantities, prices, 4);
        } 
        else if (choice == 3) {
            addToCart(productCodes, quantities, prices, cart, cartQty, 4);
        } 
        else if (choice == 4) {
            displayTotalBill(prices, cartQty, 4);
        } 
        else if (choice == 5) {
            showInvoice(customerName, customerCNIC, productCodes, prices, cart, cartQty, 4);
        } 
        else if (choice == 6) {
            printf("Exiting system. Thank you!\n");
            break;
        } 
        else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function definitions

void getCustomerInfo(char name[], char cnic[]) {
    printf("Enter customer name: ");
    scanf(" %[^\n]", name);
    printf("Enter CNIC number: ");
    scanf(" %[^\n]", cnic);
}

void displayInventory(int codes[], int quantities[], int prices[], int size) {
    printf("\n--- Inventory ---\n");
    printf("Code\tQuantity\tPrice\n");
    for (int i = 0; i < size; i++) {
        printf("%03d\t%d\t\t%d\n", codes[i], quantities[i], prices[i]);
    }
}

void addToCart(int codes[], int quantities[], int prices[], int cart[], int cartQty[], int size) {
    int code, qty, found = -1;

    printf("Enter product code: ");
    scanf("%d", &code);

    for (int i = 0; i < size; i++) {
        if (codes[i] == code) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Product code not found!\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &qty);

    if (qty > quantities[found]) {
        printf("Not enough stock available.\n");
        return;
    }

    cart[found] = codes[found];
    cartQty[found] += qty;
    updateInventory(quantities, found, qty);

    printf("%d of product %03d added to cart successfully.\n", qty, code);
}

void updateInventory(int quantities[], int index, int qty) {
    quantities[index] -= qty;
}

void displayTotalBill(int prices[], int cartQty[], int size) {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += cartQty[i] * prices[i];
    }

    char promo[20];
    printf("Do you have a promo code? (Enter code or 'no'): ");
    scanf("%s", promo);

    int discounted = 0;
    if (strcmp(promo, "Eid2025") == 0) {
        total = total - (total * 25 / 100);
        discounted = 1;
    }

    printf("Total bill %s discount: %d\n", discounted ? "with" : "without", total);
}

void showInvoice(char name[], char cnic[], int codes[], int prices[], int cart[], int cartQty[], int size) {
    printf("\n--- Invoice ---\n");
    printf("Customer Name: %s\n", name);
    printf("CNIC: %s\n", cnic);
    printf("Code\tQty\tPrice\tSubtotal\n");

    int total = 0;
    for (int i = 0; i < size; i++) {
        if (cartQty[i] > 0) {
            int subtotal = cartQty[i] * prices[i];
            total += subtotal;
            printf("%03d\t%d\t%d\t%d\n", codes[i], cartQty[i], prices[i], subtotal);
        }
    }

    char promo[20];
    printf("Enter promo code if any: ");
    scanf("%s", promo);

    if (strcmp(promo, "Eid2025") == 0) {
        printf("Discount applied: 25%%\n");
        total = total - (total * 25 / 100);
    }

    printf("Total Amount: %d\n", total);
}
