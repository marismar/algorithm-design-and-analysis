#define vertex int  //Definição de um tipo inteiro para representação dos vértices

typedef struct node *link;  //Definição de um ponteiro do tipo node 
struct node{    //Estrutura de uma lista encadeada para representação das lista de adjacências
    vertex w;   //Vértice atual
    link next;  //Próximo vértice
    int cst;   //Custo da aresta entre w e next
};

typedef struct graph *Graph;
struct graph {
   int V;   //Número de vertices do grafo
   int A;   //Número de arestas do grafo
   link *adj;   //Listas de adjacências dos vértices
};

static link NEWnode(vertex w, link next, int cst){
    link a = malloc(sizeof (struct node));
    a->w;
    a->next = next;
    a->cst = cst;
    return a;
}

Graph GRAPHinit(int V){
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; ++v)
        G->adj[v] = NULL;   //Define como null cada 
    return G;
}

void GRAPHinsertArc( Graph G, vertex v, vertex w, int cst) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode( w, G->adj[v], cst);
    G->A++;
}
