#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int parent[MAX], sz[MAX];

int compareInt(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find(int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = find(parent[x]);
}

void unite(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
        return;

    if (sz[u] < sz[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    parent[v] = u;
    sz[u] += sz[v];
}

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    int A[MAX], ans[MAX];

    for (int i = 1; i <= n; i++) {
        scanf("%d", &A[i]);

        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;

        scanf("%d %d", &u, &v);

        unite(u, v);
    }

    int *indices[MAX];
    int *values[MAX];
    int count[MAX] = {0};

    for (int i = 1; i <= n; i++) {
        indices[i] = (int *)malloc(n * sizeof(int));
        values[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 1; i <= n; i++) {
        int root = find(i);

        indices[root][count[root]] = i;
        values[root][count[root]] = A[i];

        count[root]++;
    }

    for (int i = 1; i <= n; i++) {
        if (count[i] == 0)
            continue;

        int k = count[i];

        qsort(indices[i], k, sizeof(int), compareInt);
        qsort(values[i], k, sizeof(int), compareInt);

        for (int j = 0; j < k; j++) {
            ans[indices[i][j]] = values[i][j];
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);

    printf("\n");

    for (int i = 1; i <= n; i++) {
        free(indices[i]);
        free(values[i]);
    }

    return 0;
}