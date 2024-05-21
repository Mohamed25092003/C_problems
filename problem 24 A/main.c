#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_N 64
#define MAX_M 1024
#define MAX_WAYS 1024
#define MAX_GRID 4096
#define BASE 1024

int n, m, golygons;
char g[MAX_GRID][MAX_GRID] = {}, g2[MAX_GRID][MAX_GRID] = {};
char path[MAX_N];
int x[MAX_M], y[MAX_M];
char sdir[] = "nsew";
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int ways_count = 0;
char ways[MAX_WAYS][MAX_N];

typedef struct {
    int x;
    int y;
} pair_t;

pair_t make_pair(int x, int y) {
    pair_t p = {x, y};
    return p;
}

int pair_cmp(const void* p1, const void* p2) {
    pair_t* pp1 = (pair_t*) p1;
    pair_t* pp2 = (pair_t*) p2;
    if (pp1->x != pp2->x) {
        return pp1->x - pp2->x;
    } else {
        return pp1->y - pp2->y;
    }
}

int pair_equal(const void* p1, const void* p2) {
    pair_t* pp1 = (pair_t*) p1;
    pair_t* pp2 = (pair_t*) p2;
    return (pp1->x == pp2->x) && (pp1->y == pp2->y);
}

typedef struct {
    pair_t arr[MAX_M];
    int size;
} set_t;

void set_init(set_t* s) {
    s->size = 0;
}

void set_insert(set_t* s, pair_t p) {
    s->arr[s->size] = p;
    s->size++;
}

int set_find(set_t* s, pair_t p) {
    int i;
    for (i = 0; i < s->size; i++) {
        if (pair_equal(&s->arr[i], &p)) {
            return 1;
        }
    }
    return 0;
}

void set_clear(set_t* s) {
    s->size = 0;
}

void dfs(int x, int y, int dir, int step) {
    if (abs(x - 0) + abs(y - 0) > (step + n) * (n - step + 1) / 2) {
        return;
    }
    if (step == n + 1) {
        if (x == 0 && y == 0) {
            path[step - 1] = '\0';
            strcpy(ways[ways_count], path);
            ways_count++;
            golygons++;
        }
        return;
    }
    if (dir != 0) {
        int i;
        for (i = 0; i < 2; i++) {
            int tx = x, ty = y, ok = 1;
            int j;
            for (j = 0; j < step; j++) {
                tx = tx + dx[i], ty = ty + dy[i];
                assert(BASE + tx >= 0 && BASE + ty >= 0);
                assert(BASE + tx < MAX_GRID && BASE + ty < MAX_GRID);
                if (g[BASE + tx][BASE + ty]) {
                    ok = 0;
                    break;
                }
            }
            if (ok && g2[BASE + tx][BASE + ty] == 0) {
                g2[BASE + tx][BASE + ty] = 1;
                path[step - 1] = sdir[i];
                dfs(tx, ty, 0, step + 1);
                g2[BASE + tx][BASE + ty] = 0;
            }
        }
    }
    if (dir != 1) {
        int i;
        for (i = 2; i < 4; i++) {
            int tx = x, ty = y, ok = 1;
            int j;
            for (j = 0; j < step; j++) {
                tx = tx + dx[i], ty = ty + dy[i];
                assert(BASE + tx >= 0 && BASE + ty >= 0);
                assert(BASE + tx < MAX_GRID && BASE + ty < MAX_GRID);
                if (g[BASE + tx][BASE + ty]) {
                    ok = 0;
                    break;
                }
            }
            if (ok && g2[BASE + tx][BASE + ty] == 0) {
                g2[BASE + tx][BASE +ty] = 1;
                path[step - 1] = sdir[i];
                dfs(tx, ty, 1, step + 1);
                g2[BASE + tx][BASE + ty] = 0;
            }
        }
    }
}

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        // read input
        scanf("%d %d", &n, &m);

        set_t ban;
        set_init(&ban);
        int i;
        for (i = 0; i < m; i++) {
            scanf("%d %d", &x[i], &y[i]);
            set_insert(&ban, make_pair(x[i], y[i]));
            g[BASE + x[i]][BASE + y[i]] = 1;
        }

        // solve problem
        ways_count = 0;
        dfs(0, 0, -1, 1);
        qsort(ways, ways_count, MAX_N, pair_cmp);

        // output results
        for (i = 0; i < ways_count; i++) {
            printf("%s\n", ways[i]);
        }

        printf("Found %d golygon(s).\n\n", ways_count);

        // clear variables for next test case
        for (i = 0; i < m; i++) {
            g[BASE + x[i]][BASE + y[i]] = 0;
        }
        set_clear(&ban);
    }
    return 0;
}

