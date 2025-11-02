// ALI NAQI KHOSO
// 25K-0989
// PF Theory Assignment 2
// Question 1


#include <stdio.h>
#include <string.h>

int isbns[100];
char titles[100][50];
float prices[100];
int quantities[100];
int bookCount=0;


void addBook(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount){
    if(*bookCount>=100){
        printf("Inventory full! Cannot add more books.\n");
        return;
    }

    int isbn;
    printf("Enter ISBN: ");
    scanf(" %d", &isbn);

    for(int i=0;i<*bookCount;i++){
        if(isbn==isbns[i]){
            printf("Error: A book with this ISBN already exists!\n");
            return;
        }
    }

    isbns[*bookCount]=isbn;
    printf("Enter Book Title: ");
    scanf(" %[^\n]", titles[*bookCount]);

    printf("Enter the price of the Book in PKR: ");
    scanf("%f", &prices[*bookCount]);
    
    printf("Enter the quantity of the Book you're adding: ");
    scanf("%d", &quantities[*bookCount]);

    *bookCount+=1;

    printf("Book added successfully!\n\n");
}

void processSale(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount) {
    int isbn, sales, index = -1;

    printf("Enter ISBN: ");
    scanf("%d", &isbn);

    printf("Enter number of copies to be sold: ");
    scanf("%d", &sales);

    for (int i = 0; i < *bookCount; i++) {
        if (isbn == isbns[i]) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: No such Book exists\n");
        return;
    }

    if (quantities[index] >= sales) {
        quantities[index] -= sales;
        printf("Sale processed successfully. Remaining stock: %d\n", quantities[index]);
    } else {
        printf("Not available! Only %d left in stock.\n", quantities[index]);
    }
}


void lowStockReport(int isbns[], char titles[][50], float prices[], int quantities[], int *bookCount){
    int low = 0;

    for(int i = 0; i < *bookCount; i++){
        if(quantities[i] < 5){
            if(low == 0)
                printf("======================= Low-Stock Books =======================\n\n");
            
            low++;
            printf("%d. ISBN: %d  Title: %s  Price: %.2f  Quantity: %d\n",
                   low, isbns[i], titles[i], prices[i], quantities[i]);
        }   
    }

    if(low == 0){
        printf("There are no Low-Stock Books!\n");
    }
}

void mainMenu(void)
{
    int choice;
    do{
        printf("\n--- Liberty Books Inventory ---\n");
        printf("1. Add New Book\n2. Process a Sale\n3. Generate Low-Stock Report\n4. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addBook(isbns, titles, prices, quantities, &bookCount);
            break;
        case 2:
            processSale(isbns, titles, prices, quantities, &bookCount);
            break;
        case 3:
            lowStockReport(isbns, titles, prices, quantities, &bookCount);
            break;
        case 4:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid Input\n");
        }
    } while (choice!=4);
}

int main()
{
    mainMenu();
    printf("\n");
    return 0;
}

