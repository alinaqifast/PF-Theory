/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 5
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* readLine: returns malloc'd string (caller must free). Handles long lines safely. */
char *readLine(FILE *in) {
    size_t cap = 128;
    size_t len = 0;
    char *buf = malloc(cap);
    if (!buf) return NULL;
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (c == '\r') continue; /* ignore CR */
        if (c == '\n') break;
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
    }
    if (len == 0 && c == EOF) { free(buf); return NULL; }
    buf[len] = '\0';
    /* shrink to fit exact size */
    char *out = realloc(buf, len + 1);
    return out ? out : buf;
}

typedef struct {
    char **lines;
    int size;
    int capacity;
} Buffer;

int initBuffer(Buffer *b, int initCap) {
    b->lines = malloc(sizeof(char*) * initCap);
    if (!b->lines) return 0;
    b->size = 0;
    b->capacity = initCap;
    return 1;
}

void freeAll(Buffer *b) {
    int i;
    for (i = 0; i < b->size; i++) free(b->lines[i]);
    free(b->lines);
    b->lines = NULL;
    b->size = 0;
    b->capacity = 0;
}

int growBuffer(Buffer *b) {
    int newCap = b->capacity * 2;
    char **tmp = realloc(b->lines, sizeof(char*) * newCap);
    if (!tmp) return 0;
    b->lines = tmp;
    b->capacity = newCap;
    return 1;
}

int insertLine(Buffer *b, int index, const char *text) {
    if (index < 0 || index > b->size) return 0;
    if (b->size >= b->capacity) {
        if (!growBuffer(b)) return 0;
    }
    /* shift pointers to make room (do not move strings) */
    memmove(&b->lines[index+1], &b->lines[index], sizeof(char*) * (b->size - index));
    b->lines[index] = strdup(text);
    if (!b->lines[index]) return 0;
    b->size++;
    return 1;
}

int deleteLine(Buffer *b, int index) {
    if (index < 0 || index >= b->size) return 0;
    free(b->lines[index]);
    memmove(&b->lines[index], &b->lines[index+1], sizeof(char*) * (b->size - index - 1));
    b->size--;
    return 1;
}

void printAllLines(Buffer *b) {
    int i;
    for (i = 0; i < b->size; i++) {
        printf("%d: %s\n", i+1, b->lines[i]);
    }
}

/* shrinkToFit reduces allocated memory to exactly match number of lines */
int shrinkToFit(Buffer *b) {
    if (b->size == b->capacity) return 1;
    char **tmp = realloc(b->lines, sizeof(char*) * (b->size > 0 ? b->size : 1));
    if (!tmp && b->size > 0) return 0;
    b->lines = tmp;
    b->capacity = (b->size > 0 ? b->size : 1);
    return 1;
}

int saveToFile(Buffer *b, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) return 0;
    int i;
    for (i = 0; i < b->size; i++) {
        fprintf(f, "%s\n", b->lines[i]);
    }
    fclose(f);
    return 1;
}

int loadFromFile(Buffer *b, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;
    freeAll(b);
    if (!initBuffer(b, 4)) { fclose(f); return 0; }
    char *line;
    while ((line = readLine(f)) != NULL) {
        insertLine(b, b->size, line);
        free(line);
    }
    fclose(f);
    return 1;
}

/* Simple menu to demonstrate functionality */
int main(void) {
    Buffer b;
    if (!initBuffer(&b, 4)) { printf("Memory alloc failed\n"); return 1; }

    printf("Minimal editor. Commands:\n");
    printf("i idx -> insert at idx (1-based). then type the line and press enter.\n");
    printf("d idx -> delete line at idx (1-based).\n");
    printf("p     -> print all\n");
    printf("s fname -> save\n");
    printf("l fname -> load\n");
    printf("f     -> shrinkToFit\n");
    printf("q     -> quit\n");

    char cmd[16];
    while (1) {
        printf("> ");
        if (scanf("%15s", cmd) != 1) break;

        if (strcmp(cmd, "i") == 0) {
            int idx;
            if (scanf("%d", &idx) != 1) continue;
            getchar(); /* consume newline */
            printf("Enter line:\n");
            char *line = readLine(stdin);
            if (!line) { printf("No input\n"); continue; }
            if (!insertLine(&b, idx - 1, line)) {
                printf("Insert failed (memory?)\n");
            }
            free(line);
        } else if (strcmp(cmd, "d") == 0) {
            int idx;
            if (scanf("%d", &idx) != 1) continue;
            if (!deleteLine(&b, idx - 1)) printf("Delete failed\n");
        } else if (strcmp(cmd, "p") == 0) {
            printAllLines(&b);
        } else if (strcmp(cmd, "s") == 0) {
            char fname[256];
            scanf("%255s", fname);
            if (!saveToFile(&b, fname)) printf("Save failed\n");
        } else if (strcmp(cmd, "l") == 0) {
            char fname[256];
            scanf("%255s", fname);
            if (!loadFromFile(&b, fname)) printf("Load failed\n");
        } else if (strcmp(cmd, "f") == 0) {
            if (!shrinkToFit(&b)) printf("Shrink failed\n"); else printf("Shrink ok\n");
        } else if (strcmp(cmd, "q") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
    }

    freeAll(&b);
    return 0;
}
