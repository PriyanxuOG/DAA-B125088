#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1005

int parent[MAX], sz[MAX];
long long weight[MAX];

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
    weight[u] += weight[v];
}

long long getMaximum(int n, int K) {
    long long ans = LLONG_MIN;

    for (int i = 1; i <= n; i++) {
        if (find(i) == i && sz[i] <= K) {
            if (weight[i] > ans)
                ans = weight[i];
        }
    }

    return ans;
}

int main() {
    int n, m, K;

    printf("Enter vertices, edges and K: ");
    scanf("%d %d %d", &n, &m, &K);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;

        scanf("%lld", &weight[i]);
    }

    for (int i = 0; i < m; i++) {
        int u, v;

        scanf("%d %d", &u, &v);

        unite(u, v);

        long long ans = getMaximum(n, K);

        if (ans == LLONG_MIN)
            printf("No valid component\n");
        else
            printf("%lld\n", ans);
    }

    return 0;
}