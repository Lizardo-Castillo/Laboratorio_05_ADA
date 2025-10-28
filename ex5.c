#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    if (!G) { perror("malloc"); exit(EXIT_FAILURE); }
    G->V = V;
    G->A = 0;
    for (int v = 0; v < V; v++) G->adj[v] = NULL;
    return G;
}

void GRAPHinsertA(Graph G, vertex v, vertex w) {
    link a = malloc(sizeof(*a));
    if (!a) { perror("malloc"); exit(EXIT_FAILURE); }
    a->w = w;
    a->next = G->adj[v];
    G->adj[v] = a;
    G->A++;
}

Graph readAdjFile(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("fopen"); exit(EXIT_FAILURE); }

    int V;
    if (fscanf(f, "%d", &V) != 1 || V <= 0 || V > MAXV) {
        fprintf(stderr, "Error: primera línea inválida (V)\n");
        exit(EXIT_FAILURE);
    }

    Graph G = GRAPHinit(V);
    char line[4096];
    fgets(line, sizeof(line), f);

    for (int i = 0; i < V; i++) {
        if (!fgets(line, sizeof(line), f)) {
            fprintf(stderr, "Error: faltan líneas en el archivo.\n");
            exit(EXIT_FAILURE);
        }
        char *p = line;
        while (isspace((unsigned char)*p)) p++;

        int v, w, read;
        if (sscanf(p, "%d%n", &v, &read) != 1) continue;
        p += read;
        while (sscanf(p, "%d%n", &w, &read) == 1) {
            if (w >= 0 && w < V)
                GRAPHinsertA(G, v, w);
            p += read;
        }
    }

    fclose(f);
    return G;
}

void print_indent(void) {
    for (int i = 0; i < indent; i++) putchar('.');
}

static void dfsR(Graph G, vertex v) {
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
            dfsR(G, w);
        } else {
            printf("\n");
        }
    }

    indent--;
    print_indent();
    printf("%d\n", v);
}

void GRAPHdfs(Graph G) {
    cnt = 0;
    indent = 0;
    for (vertex v = 0; v < G->V; v++) pre[v] = -1;

    for (vertex v = 0; v < G->V; v++) {
        if (pre[v] == -1)
            dfsR(G, v);
    }
}

void printPre(Graph G) {
    printf("pre[]: ");
    for (int v = 0; v < G->V; v++)
        printf("%d ", pre[v]);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s archivo_de_adyacencia.txt\n", argv[0]);
        return 1;
    }

    Graph G = readAdjFile(argv[1]);
    printf("Rastreo de DFS con sangría:\n\n");
    GRAPHdfs(G);

    printf("\nOrden de descubrimiento (pre[]):\n");
    printPre(G);

    return 0;
}
