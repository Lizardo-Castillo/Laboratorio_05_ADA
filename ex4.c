#include <stdio.h>
#include <stdlib.h>

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
static int indent;

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

void GRAPHinsertE(Graph G, vertex v, vertex w) {
    GRAPHinsertA(G, v, w);
    GRAPHinsertA(G, w, v);
}

void print_indent(void) {
    for (int i = 0; i < indent; i++) putchar('.');
}

static void dfsR_trace(Graph G, vertex v) {
    print_indent();
    printf("%d dfsR(G,%d)\n", v, v);
    indent++;
    pre[v] = cnt++;

    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        print_indent();
        printf("%d-%d", v, w);
        if (pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            dfsR_trace(G, w);
        } else {
            printf("\n");
        }
    }

    indent--;
    print_indent();
    printf("%d\n", v);
}

void GRAPHdfs_trace(Graph G) {
    cnt = 0;
    indent = 0;
    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR_trace(G, v);
}

void printPre(Graph G) {
    printf("pre[]: ");
    for (int v = 0; v < G->V; v++)
        printf("%d ", pre[v]);
    printf("\n");
}

// Construcción del grafo
Graph makeExercise4(void) {
    Graph G = GRAPHinit(10);
    GRAPHinsertE(G, 3, 7);
    GRAPHinsertE(G, 1, 4);
    GRAPHinsertE(G, 7, 8);
    GRAPHinsertE(G, 0, 5);
    GRAPHinsertE(G, 5, 2);
    GRAPHinsertE(G, 3, 8);
    GRAPHinsertE(G, 2, 9);
    GRAPHinsertE(G, 0, 6);
    GRAPHinsertE(G, 4, 9);
    GRAPHinsertE(G, 2, 6);
    GRAPHinsertE(G, 6, 4);
    return G;
}

int main(void) {
    Graph G = makeExercise4();
    printf("Rastreo de DFS:\n\n");
    GRAPHdfs_trace(G);
    printf("\nOrden de descubrimiento (pre[]):\n");
    printPre(G);
    return 0;
}
