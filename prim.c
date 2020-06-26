#include "graph.h"  //biblioteca da definição

#define INFINITO 10000  //Define uma constante com um valor maior do que qualquer aresta presente no grafo

void MSTPRIM(Graph G, vertex r){
    vertex *PAI = malloc(G->V * sizeof(vertex *));  //Definição de uma lista de ponteiros para vértice
    for (vertex u = 0; u < G->V; u++)   //Utilizada para apontar para o pai de cada vertice
        PAI[u] = -1;    //Inicia com -1(valor nulo) para cada vertice u
    PAI[r] = r; //Pai do vertice origem resetado com ele mesmo
    while(1){
        vertex pai, filho;
        int minimo = INFINITO;  //Utilizado para salvar o menor custo das arestas adjacentes
        for (vertex v = 0; v<G->V; ++v){    //repetição para análise de cada vertice v de G
            if (PAI[v] == -1) continue;     //se o pai do vertice em analise for nulo continua
            for (link a = G->adj[v]; a!=NULL; a=a->next){   //varredura da lista de adjacência do vertice v
                if(minimo>a->cst){  //se o custo da aresta analisada for menor do que o minimo
                    minimo = a->cst;    //atualiza o valor do minimo
                    pai = v, filho = a->w;  //seta pai como v e filho como o elemento adjacente a v
                }
            }
            if (minimo == INFINITO) break;  //se não houver nenhuma aresta com custo menor, quebre o laço
            PAI[filho] = pai;   //seta v como pai de seu vertice adjacente, com menor valor de aresta
        }
    }
}
