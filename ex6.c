#include <stdio.h>
#include <stdlib.h>

#define MAXV 1000
typedef int vertex;

typedef struct graph {
    int V;
    int adj[MAXV][MAXV]; 
} *Graph;

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    if (!G) { perror("malloc"); exit(EXIT_FAILURE); }
    G->V = V;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            G->adj[i][j] = 0;
    return G;
}

void GRAPHinsertA(Graph G, vertex v, vertex w) {
    if (G->adj[v][w] == 0) {
        G->adj[v][w] = 1;
    }
}

void GRAPHinsertE(Graph G, vertex v, vertex w) {
    GRAPHinsertA(G, v, w);
    GRAPHinsertA(G, w, v);
}

typedef struct {
    vertex *data;
    int top;
} Stack;

Stack STACKinit(int maxV) {
    Stack s;
    s.data = malloc(maxV * sizeof(vertex));
    s.top = 0;
    return s;
}

int STACKempty(Stack *s) {
    return s->top == 0;
}

void STACKpush(Stack *s, vertex v) {
    s->data[s->top++] = v;
}

vertex STACKpop(Stack *s) {
    return s->data[--s->top];
}

static int cnt;
static int pre[MAXV];

void dfs_iter(Graph G, vertex v) {
    Stack S = STACKinit(G->V);
    pre[v] = cnt++;
    STACKpush(&S, v);

    while (!STACKempty(&S)) {
        v = STACKpop(&S);
        for (vertex w = 0; w < G->V; ++w)
            if (G->adj[v][w] == 1)
                if (pre[w] == -1) {
                    pre[w] = cnt++;
                    STACKpush(&S, w);
                }
    }
    free(S.data);
}

void GRAPHdfs_iter(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfs_iter(G, v);
}

static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    for (vertex w = 0; w < G->V; ++w)
        if (G->adj[v][w] == 1 && pre[w] == -1)
            dfsR(G, w);
}

void GRAPHdfs_recursive(Graph G) {
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfsR(G, v);
}

void printPre(Graph G) {
    for (int v = 0; v < G->V; v++)
        printf("pre[%d] = %d\n", v, pre[v]);
}

int main(void) {
    Graph G = GRAPHinit(5);
    GRAPHinsertA(G, 0, 1);
    GRAPHinsertA(G, 0, 2);
    GRAPHinsertA(G, 1, 3);
    GRAPHinsertA(G, 2, 4);

    printf("=== DFS iterativa ===\n");
    GRAPHdfs_iter(G);
    printPre(G);

    printf("\n=== DFS recursiva ===\n");
    GRAPHdfs_recursive(G);
    printPre(G);

    printf("\nObserva que los órdenes de descubrimiento difieren.\n");
    printf("La versión iterativa usa pila pero NO profundiza en el primer vecino inmediatamente.\n");

    free(G);
    return 0;
}