/* 
Class: bcs-1c
Roll: 25K-0989
Name: Ali Naqi 

Question 4

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    int popularity;
    long lastAccess; /* larger = more recent */
    int used; /* 0 = empty slot, 1 = used */
} Book;

int findBook(Book *shelf, int cap, int id) {
    int i;
    for (i = 0; i < cap; i++) {
        if (shelf[i].used && shelf[i].id == id) return i;
    }
    return -1;
}

/* find index of least recently used book */
int findLRU(Book *shelf, int cap) {
    int i, idx = -1;
    long min = 0;
    for (i = 0; i < cap; i++) {
        if (shelf[i].used) {
            if (idx == -1 || shelf[i].lastAccess < min) {
                idx = i;
                min = shelf[i].lastAccess;
            }
        }
    }
    return idx;
}

int main(void) {
    int capacity, Q;
    if (scanf("%d %d", &capacity, &Q) != 2) return 0;
    Book *shelf = calloc(capacity, sizeof(Book));
    if (!shelf) return 1;

    long timeCounter = 1;
    char op[16];
    int i;
    for (i = 0; i < Q; i++) {
        if (scanf("%s", op) != 1) break;
        if (strcmp(op, "ADD") == 0) {
            int x, y;
            scanf("%d %d", &x, &y);
            int idx = findBook(shelf, capacity, x);
            if (idx != -1) {
                /* update popularity and mark recent */
                shelf[idx].popularity = y;
                shelf[idx].lastAccess = timeCounter++;
                shelf[idx].used = 1;
            } else {
                /* if space available, add to first empty slot */
                int added = 0;
                int j;
                for (j = 0; j < capacity; j++) {
                    if (!shelf[j].used) {
                        shelf[j].id = x;
                        shelf[j].popularity = y;
                        shelf[j].lastAccess = timeCounter++;
                        shelf[j].used = 1;
                        added = 1;
                        break;
                    }
                }
                if (!added) {
                    /* shelf full: remove LRU and place new book */
                    int lru = findLRU(shelf, capacity);
                    if (lru != -1) {
                        shelf[lru].id = x;
                        shelf[lru].popularity = y;
                        shelf[lru].lastAccess = timeCounter++;
                        shelf[lru].used = 1;
                    }
                }
            }
        } else if (strcmp(op, "ACCESS") == 0) {
            int x;
            scanf("%d", &x);
            int idx = findBook(shelf, capacity, x);
            if (idx == -1) {
                printf("-1\n");
            } else {
                /* update recency and return popularity */
                shelf[idx].lastAccess = timeCounter++;
                printf("%d\n", shelf[idx].popularity);
            }
        } else {
            /* Unknown op, consume rest of line */
            char buf[256];
            fgets(buf, sizeof(buf), stdin);
        }
    }

    free(shelf);
    return 0;
}
