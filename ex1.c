#include <stdio.h>
#include <stdlib.h>

// - Codigo de Prueba Ejercicio 1 - //

#define MAXV 1000
typedef int vertex;

typedef struct node {
    vertex w;
    struct node *next;
} *link;

typedef struct graph {
    int V;
    int A;
    link adj[MAXV];
} *Graph;

static int cnt;
static int pre[MAXV];

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    for (int v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertA(Graph G, vertex v, vertex w) {
    link a = malloc(sizeof(*a));
    a->w = w;
    a->next = G->adj[v];
    G->adj[v] = a;
    G->A++;
}

static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1)
            dfsR(G, w);
    }
}

void GRAPHdfs(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfsR(G, v);
}

void printPre(Graph G) {
    printf("pre[]: ");
    for (int v = 0; v < G->V; v++)
        printf("%d ", pre[v]);
    printf("\n");
}

int main(void) {
    printf("Caso 1: G->A == 0 (sin aristas)\n");
    Graph G1 = GRAPHinit(4);
    GRAPHdfs(G1);
    printPre(G1);

    printf("\nCaso 2: G->V == 1 (un solo vértice)\n");
    Graph G2 = GRAPHinit(1);
    GRAPHdfs(G2);
    printPre(G2);

    return 0;
}
