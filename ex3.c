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

// DFS con rastreo e indentación
static int indent = 0;
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
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
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
Graph makeExercise3(void) {
    Graph G = GRAPHinit(12);
    GRAPHinsertA(G, 0, 4);
    GRAPHinsertA(G, 0, 1);
    GRAPHinsertA(G, 1, 5);
    GRAPHinsertA(G, 1, 2);
    GRAPHinsertA(G, 2, 3);
    GRAPHinsertA(G, 3, 7);
    GRAPHinsertA(G, 4, 8);
    GRAPHinsertA(G, 5, 4);
    GRAPHinsertA(G, 6, 2);
    GRAPHinsertA(G, 6, 10);
    GRAPHinsertA(G, 6, 5);
    GRAPHinsertA(G, 7, 6);
    GRAPHinsertA(G, 7, 11);
    GRAPHinsertA(G, 8, 9);
    GRAPHinsertA(G, 9, 8);
    GRAPHinsertA(G, 9, 5);
    GRAPHinsertA(G, 10, 9);
    GRAPHinsertA(G, 11, 10);
    return G;
}

int main(void) {
    Graph G = makeExercise3();
    printf("Rastreo de DFS:\n\n");
    GRAPHdfs_trace(G);
    printf("\nOrden de descubrimiento (pre[]):\n");
    printPre(G);
    return 0;
}
