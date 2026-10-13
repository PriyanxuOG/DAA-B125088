#include <stdio.h>
#include <stdlib.h>

#define MAX 1005

int parent[MAX], sz[MAX];
long long sum[MAX], weight[MAX];

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
    sum[u] += sum[v];
}

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &weight[i]);

        parent[i] = i;
        sz[i] = 1;
        sum[i] = 0;
    }

    int **adj = (int **)malloc((n + 1) * sizeof(int *));

    int *degree = (int *)calloc(n + 1, sizeof(int));
    int *capacity = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++) {
        capacity[i] = 2;
        adj[i] = (int *)malloc(capacity[i] * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        if (degree[u] == capacity[u]) {
            capacity[u] *= 2;
            adj[u] = (int *)realloc(
                adj[u], capacity[u] * sizeof(int));
        }

        if (degree[v] == capacity[v]) {
            capacity[v] *= 2;
            adj[v] = (int *)realloc(
                adj[v], capacity[v] * sizeof(int));
        }

        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }

    int *p = (int *)malloc(n * sizeof(int));
    int *active = (int *)calloc(n + 1, sizeof(int));
    long long *ans = (long long *)calloc(n, sizeof(long long));

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    long long maximum = 0;

    for (int i = n - 1; i >= 0; i--) {
        /* State after deleting p[i]:
           p[i] is still inactive in this state. */
        ans[i] = maximum;

        int u = p[i];

        active[u] = 1;
        sum[u] = weight[u];

        if (weight[u] > maximum)
            maximum = weight[u];

        for (int j = 0; j < degree[u]; j++) {
            int v = adj[u][j];

            if (active[v]) {
                unite(u, v);

                int root = find(u);

                if (sum[root] > maximum)
                    maximum = sum[root];
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf("%lld ", ans[i]);

    printf("\n");

    for (int i = 1; i <= n; i++)
        free(adj[i]);

    free(adj);
    free(degree);
    free(capacity);
    free(p);
    free(active);
    free(ans);

    return 0;
}