/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 6
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int studentID;
    char fullName[100];
    char batch[32]; /* CS, SE, Cyber Security, AI */
    char membershipType[8]; /* IEEE or ACM */
    char registrationDate[11]; /* YYYY-MM-DD */
    char dob[11]; /* YYYY-MM-DD */
    char interestIn[8]; /* IEEE/ACM/Both */
} Student;

typedef struct {
    Student *arr;
    int size;
    int capacity;
} DB;

/* dynamic array helpers */
int db_init(DB *db) {
    db->capacity = 8;
    db->size = 0;
    db->arr = malloc(sizeof(Student) * db->capacity);
    return db->arr != NULL;
}
void db_free(DB *db) {
    free(db->arr);
    db->arr = NULL;
    db->size = db->capacity = 0;
}
int db_grow(DB *db) {
    int nc = db->capacity * 2;
    Student *tmp = realloc(db->arr, sizeof(Student) * nc);
    if (!tmp) return 0;
    db->arr = tmp;
    db->capacity = nc;
    return 1;
}

/* loadDatabase: read entire file into memory */
int loadDatabase(const char *filename, DB *db) {
    FILE *f = fopen(filename, "rb");
    if (!f) return 0;
    db_free(db);
    if (!db_init(db)) { fclose(f); return 0; }
    Student tmp;
    while (fread(&tmp, sizeof(Student), 1, f) == 1) {
        if (db->size >= db->capacity) {
            if (!db_grow(db)) { fclose(f); return 0; }
        }
        db->arr[db->size++] = tmp;
    }
    fclose(f);
    return 1;
}

/* saveDatabase: overwrite file with in-memory database */
int saveDatabase(const char *filename, DB *db) {
    FILE *f = fopen(filename, "wb");
    if (!f) return 0;
    if (db->size > 0) {
        if (fwrite(db->arr, sizeof(Student), db->size, f) != (size_t)db->size) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}

/* check duplicate ID */
int existsID(DB *db, int id) {
    int i;
    for (i = 0; i < db->size; i++) if (db->arr[i].studentID == id) return 1;
    return 0;
}

/* addStudent: append to in-memory DB and save */
int addStudent(DB *db, Student s, const char *filename) {
    if (existsID(db, s.studentID)) return 0;
    if (db->size >= db->capacity) if (!db_grow(db)) return 0;
    db->arr[db->size++] = s;
    return saveDatabase(filename, db);
}

/* updateStudent: update batch or membershipType for studentID and save */
int updateStudent(DB *db, int studentID, const char *newBatch, const char *newMembership, const char *filename) {
    int i;
    for (i = 0; i < db->size; i++) {
        if (db->arr[i].studentID == studentID) {
            if (newBatch && newBatch[0]) strncpy(db->arr[i].batch, newBatch, sizeof(db->arr[i].batch)-1);
            if (newMembership && newMembership[0]) strncpy(db->arr[i].membershipType, newMembership, sizeof(db->arr[i].membershipType)-1);
            return saveDatabase(filename, db);
        }
    }
    return 0;
}

/* deleteStudent: remove record and save */
int deleteStudent(DB *db, int studentID, const char *filename) {
    int i, found = -1;
    for (i = 0; i < db->size; i++) if (db->arr[i].studentID == studentID) { found = i; break; }
    if (found == -1) return 0;
    /* shift remaining */
    memmove(&db->arr[found], &db->arr[found+1], sizeof(Student) * (db->size - found - 1));
    db->size--;
    return saveDatabase(filename, db);
}

/* display all */
void displayAll(DB *db) {
    int i;
    printf("ID\tName\tBatch\tMembership\tRegDate\tDOB\tInterest\n");
    printf("-----------------------------------------------------------------\n");
    for (i = 0; i < db->size; i++) {
        Student *s = &db->arr[i];
        printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\n", s->studentID, s->fullName, s->batch, s->membershipType, s->registrationDate, s->dob, s->interestIn);
    }
}

/* batch-wise report (e.g., list AI students with IEEE membership) */
void batchReport(DB *db, const char *batch, const char *membershipFilter) {
    int i, found = 0;
    printf("Report for batch=%s membership=%s\n", batch, membershipFilter);
    for (i = 0; i < db->size; i++) {
        if (strcmp(db->arr[i].batch, batch) == 0) {
            if (strcmp(membershipFilter, "Both") == 0 || strcmp(db->arr[i].interestIn, membershipFilter) == 0 || strcmp(db->arr[i].membershipType, membershipFilter) == 0) {
                printf("%d\t%s\t%s\n", db->arr[i].studentID, db->arr[i].fullName, db->arr[i].membershipType);
                found = 1;
            }
        }
    }
    if (!found) printf("No matching records.\n");
}

int main(void) {
    const char *filename = "members.dat";
    DB db;
    db_init(&db);
    /* load existing */
    loadDatabase(filename, &db);

    while (1) {
        printf("\nMenu:\n1 Add\n2 Update\n3 Delete\n4 View All\n5 Batch Report\n6 Exit\nChoose: ");
        int choice;
        if (scanf("%d", &choice) != 1) break;
        if (choice == 1) {
            Student s;
            printf("Enter Student ID: "); scanf("%d", &s.studentID); getchar();
            if (existsID(&db, s.studentID)) { printf("Duplicate ID. Aborting.\n"); continue; }
            printf("Full Name: "); fgets(s.fullName, sizeof(s.fullName), stdin); s.fullName[strcspn(s.fullName, "\n")] = '\0';
            printf("Batch (CS/SE/Cyber Security/AI): "); fgets(s.batch, sizeof(s.batch), stdin); s.batch[strcspn(s.batch, "\n")] = '\0';
            printf("Membership Type (IEEE/ACM): "); fgets(s.membershipType, sizeof(s.membershipType), stdin); s.membershipType[strcspn(s.membershipType, "\n")] = '\0';
            printf("Registration Date (YYYY-MM-DD): "); fgets(s.registrationDate, sizeof(s.registrationDate), stdin); s.registrationDate[strcspn(s.registrationDate, "\n")] = '\0';
            printf("Date of Birth (YYYY-MM-DD): "); fgets(s.dob, sizeof(s.dob), stdin); s.dob[strcspn(s.dob, "\n")] = '\0';
            printf("Interest in (IEEE/ACM/Both): "); fgets(s.interestIn, sizeof(s.interestIn), stdin); s.interestIn[strcspn(s.interestIn, "\n")] = '\0';
            if (addStudent(&db, s, filename)) printf("Added and saved.\n"); else printf("Add failed.\n");
        } else if (choice == 2) {
            int id; char newBatch[32], newMembership[16];
            printf("Student ID to update: "); scanf("%d", &id); getchar();
            printf("New Batch (leave blank to skip): "); fgets(newBatch, sizeof(newBatch), stdin); newBatch[strcspn(newBatch, "\n")] = '\0';
            printf("New Membership (leave blank to skip): "); fgets(newMembership, sizeof(newMembership), stdin); newMembership[strcspn(newMembership, "\n")] = '\0';
            if (updateStudent(&db, id, newBatch, newMembership, filename)) printf("Updated and saved.\n"); else printf("Update failed.\n");
        } else if (choice == 3) {
            int id;
            printf("Student ID to delete: "); scanf("%d", &id);
            if (deleteStudent(&db, id, filename)) printf("Deleted and saved.\n"); else printf("Delete failed.\n");
        } else if (choice == 4) {
            displayAll(&db);
        } else if (choice == 5) {
            char batch[32], membership[16];
            printf("Batch: "); getchar(); fgets(batch, sizeof(batch), stdin); batch[strcspn(batch, "\n")] = '\0';
            printf("Membership filter (IEEE/ACM/Both): "); fgets(membership, sizeof(membership), stdin); membership[strcspn(membership, "\n")] = '\0';
            batchReport(&db, batch, membership);
        } else if (choice == 6) {
            saveDatabase(filename, &db);
            break;
        } else {
            printf("Invalid\n");
        }
    }

    db_free(&db);
    return 0;
}
