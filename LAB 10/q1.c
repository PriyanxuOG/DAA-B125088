#include <stdio.h>
#include <stdlib.h>

int parent[1005], sz[1005], parity[1005];

int find(int x) {
    if (parent[x] == x)
        return x;

    int p = parent[x];
    parent[x] = find(p);
    parity[x] ^= parity[p];

    return parent[x];
}

int addEdge(int u, int v) {
    int ru = find(u);
    int pu = parity[u];

    int rv = find(v);
    int pv = parity[v];

    if (ru == rv)
        return (pu ^ pv) == 1;

    if (sz[ru] < sz[rv]) {
        int temp = ru;
        ru = rv;
        rv = temp;
    }

    parent[rv] = ru;
    parity[rv] = pu ^ pv ^ 1;
    sz[ru] += sz[rv];

    return 1;
}

int main() {
    int V, E;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);

    for (int i = 1; i <= V; i++) {
        parent[i] = i;
        sz[i] = 1;
        parity[i] = 0;
    }

    for (int i = 0; i < E; i++) {
        int u, v;

        printf("Enter edge: ");
        scanf("%d %d", &u, &v);

        if (addEdge(u, v))
            printf("Edge accepted\n");
        else
            printf("Edge rejected: Graph is not bipartite\n");
    }

    return 0;
}