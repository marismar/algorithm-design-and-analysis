#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#define INFINITO 9999999

using namespace std;

typedef struct grafo{
    int n_elementos;
    int **elementos;
};


/* FUNCOES ESSENCIAIS */
void iniciaGrafo(grafo *g, ifstream &instancia);
void HVMP(grafo g, int *rota, int n_inicial);
int *opt2(grafo g, int *rota);


/*------ FUNCOES AUXILIARES ------*/
int calculaCusto(grafo g, int *rota);
int calculaNInicial(grafo g, int *rota);
void printMatriz(grafo g);
void printRota(grafo g, int *rota);


#endif // TSP_H_INCLUDED
