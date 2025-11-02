#include <stdio.h>

// Function prototype
void updateSectorStatus(int grid[5][5], int rows, int cols);
void querySectorStatus(int grid[5][5], int rows, int cols);
void runSystemDiagnostic(int grid[5][5], int rows, int cols);
void displayMenu();
void printStatus(int status);

int main() {
    int grid[5][5] = {0}; // 5x5 grid initialized with all 0
    int choice;
    int rows = 5, cols = 5;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                updateSectorStatus(grid, rows, cols);
                break;
            case 2:
                querySectorStatus(grid, rows, cols);
                break;
            case 3:
                runSystemDiagnostic(grid, rows, cols);
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 4);

    return 0;
}

// display menu
void displayMenu() {
    printf("\n===== IESCO Power Grid Monitoring System =====\n");
    printf("1. Update Sector Status\n");
    printf("2. Query Sector Status\n");
    printf("3. Run System Diagnostic\n");
    printf("4. Exit\n");
}

// update a specific sector's status
void updateSectorStatus(int grid[5][5], int rows, int cols) {
    int row, col, flagChoice, action;

    // Bit positions
    int POWER_ON = 1;       // binary 001
    int OVERLOAD = 2;       // binary 010
    int MAINTENANCE = 4;    // binary 100

    printf("Enter row (0-%d): ", rows - 1);
    scanf("%d", &row);
    printf("Enter column (0-%d): ", cols - 1);
    scanf("%d", &col);

    if(row < 0 || row >= rows || col < 0 || col >= cols) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSelect flag to modify:\n");
    printf("1. Power Status\n");
    printf("2. Overload Warning\n");
    printf("3. Maintenance Required\n");
    printf("Enter your choice: ");
    scanf("%d", &flagChoice);

    printf("1. Set (Turn ON)\n");
    printf("2. Clear (Turn OFF)\n");
    printf("Enter your action: ");
    scanf("%d", &action);

    int flagMask = 0;
    if(flagChoice == 1)
        flagMask = POWER_ON;
    else if(flagChoice == 2)
        flagMask = OVERLOAD;
    else if(flagChoice == 3)
        flagMask = MAINTENANCE;
    else {
        printf("Invalid flag choice!\n");
        return;
    }

    if(action == 1)
        grid[row][col] |= flagMask;    // set
    else if(action == 2)
        grid[row][col] &= ~flagMask;   // clear
    else {
        printf("Invalid action!\n");
        return;
    }

    printf("Sector [%d][%d] updated successfully!\n", row, col);
}

// query a sector’s status
void querySectorStatus(int grid[5][5], int rows, int cols) {
    int row, col;
    printf("Enter row (0-%d): ", rows - 1);
    scanf("%d", &row);
    printf("Enter column (0-%d): ", cols - 1);
    scanf("%d", &col);

    if(row < 0 || row >= rows || col < 0 || col >= cols) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nStatus Report for Sector [%d][%d]:\n", row, col);
    printStatus(grid[row][col]);
}

// print  status
void printStatus(int status) {
    int POWER_ON = 1;
    int OVERLOAD = 2;
    int MAINTENANCE = 4;

    printf("Power: %s\n", (status & POWER_ON) ? "ON" : "OFF");
    printf("Overload: %s\n", (status & OVERLOAD) ? "YES" : "NO");
    printf("Maintenance Required: %s\n", (status & MAINTENANCE) ? "YES" : "NO");
}

// run diagnostic on the entire grid
void runSystemDiagnostic(int grid[5][5], int rows, int cols) {
    int OVERLOAD = 2;
    int MAINTENANCE = 4;
    int overloadedCount = 0, maintenanceCount = 0;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(grid[i][j] & OVERLOAD)
                overloadedCount++;
            if(grid[i][j] & MAINTENANCE)
                maintenanceCount++;
        }
    }

    printf("\n===== System Diagnostic Report =====\n");
    printf("Total overloaded sectors: %d\n", overloadedCount);
    printf("Total sectors needing maintenance: %d\n", maintenanceCount);
}

