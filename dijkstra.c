#include "graph.h"

void DIJKSTRA( Graph G, vertex r) {
   vertex *PAI = malloc(G->V * sizeof(vertex *));
   vertex *CHAVE = malloc(G->V * sizeof(vertex *));
   for (vertex v = 0; v < G->V; ++v) 
      PAI[v] = -1, CHAVE[v] = 0; 
   PAI[r] = r, CHAVE[r] = 0;
   while (true) {
      vertex pai, filho;
      int minimo = INFINITO;
      for (vertex v = 0; v < G->V; ++v) {
         if (PAI[v] == -1) continue;
         for (link a = G->adj[v]; a != NULL; a = a->next) {
            if (PAI[a->w] != -1) continue;
            if (CHAVE[v] + a->cst < minimo) {
               minimo = CHAVE[v] + a->cst;
               pai = v, filho = a->w;
            }
         }
      }
      if (minimo == INFINITO) break;
      PAI[filho] = pai;
      CHAVE[filho] = minimo;
   }
}
