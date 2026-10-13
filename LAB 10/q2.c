#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;
int **land;

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

int unite(int x, int y) {
    x = find(x);
    y = find(y);

    if (x == y)
        return 0;

    if (sz[x] < sz[y]) {
        int temp = x;
        x = y;
        y = temp;
    }

    parent[y] = x;
    sz[x] += sz[y];

    return 1;
}

int main() {
    int R, C, K;

    printf("Enter rows, columns and operations: ");
    scanf("%d %d %d", &R, &C, &K);

    int N = R * C;

    parent = (int *)malloc(N * sizeof(int));
    sz = (int *)malloc(N * sizeof(int));

    land = (int **)malloc(R * sizeof(int *));

    for (int i = 0; i < R; i++) {
        land[i] = (int *)calloc(C, sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int islands = 0;

    for (int i = 0; i < K; i++) {
        int r, c;

        scanf("%d %d", &r, &c);

        r--;
        c--;

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid position\n");
            continue;
        }

        if (land[r][c]) {
            printf("%d ", islands);
            continue;
        }

        land[r][c] = 1;
        islands++;

        int id = r * C + c;

        for (int j = 0; j < 4; j++) {
            int nr = r + dr[j];
            int nc = c + dc[j];

            if (nr >= 0 && nr < R &&
                nc >= 0 && nc < C &&
                land[nr][nc]) {

                int nid = nr * C + nc;

                if (unite(id, nid))
                    islands--;
            }
        }

        printf("%d ", islands);
    }

    printf("\n");

    for (int i = 0; i < R; i++)
        free(land[i]);

    free(land);
    free(parent);
    free(sz);

    return 0;
}