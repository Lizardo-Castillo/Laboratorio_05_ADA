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

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    if (!G) { perror("malloc"); exit(EXIT_FAILURE); }
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

static int cnt;
static int pre[MAXV];

static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;
        if (pre[w] == -1)
            dfsR(G, w);
    }
}

void GRAPHdfs_recursive(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR(G, v);
}

typedef struct {
    vertex v;
    link next;
} Frame;

void dfsR_iter(Graph G, vertex s) {
    Frame *stack = malloc(G->V * sizeof(Frame));
    int top = 0;

    pre[s] = cnt++;
    stack[top].v = s;
    stack[top].next = G->adj[s];
    top++;

    while (top > 0) {
        Frame *f = &stack[top - 1];
        vertex v = f->v;

        if (f->next == NULL) {
            top--;
            continue;
        }

        vertex w = f->next->w;
        f->next = f->next->next;

        if (pre[w] == -1) {
            pre[w] = cnt++;
            stack[top].v = w;
            stack[top].next = G->adj[w];
            top++;
        }
    }

    free(stack);
}

void GRAPHdfs_iterative(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR_iter(G, v);
}

void printPre(Graph G) {
    printf("Orden de descubrimiento (pre[]): ");
    for (int v = 0; v < G->V; v++)
        printf("%d ", pre[v]);
    printf("\n");
}

Graph makeGraphExample(void) {
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
    Graph G = makeGraphExample();

    printf("=== DFS recursiva ===\n");
    GRAPHdfs_recursive(G);
    printPre(G);

    printf("\n=== DFS iterativa (listas de adyacencia) ===\n");
    GRAPHdfs_iterative(G);
    printPre(G);

    printf("\nAmbas versiones deben producir el mismo orden de descubrimiento.\n");

    free(G);
    return 0;
}
