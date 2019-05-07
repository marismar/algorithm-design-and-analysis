#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

#define INFINITO 9999999

using namespace std;

typedef struct grafo{
    int n_elementos;
    int **elementos;
};

typedef struct elemento{
    int custo;
    int id;
};


/*------ FUNCOES ESSENCIAIS ------*/
void iniciaGrafo(grafo *g, ifstream &instancia);
void HVMP(grafo g, int *rota, int n_inicial);
int *opt2(grafo g, int *rota);
int *swap(grafo g, int *rota);
int *VND(grafo g, int *rota);
int *GRASP(grafo g, int grasp_max, int *rota);
static vector<int> construcao(grafo g, int alpha);

/*------ FUNCOES AUXILIARES ------*/
static void flip(int n_elementos, int *rota, int *rt_aux, int lim1, int lim2);
static elemento iniciaElemento(grafo g, int linha, int coluna);
static custoMaxMin(vector<elemento> LC, int *minimo, int *maximo);
static void copiaArray(int *destino, int *origem, int n_elementos);
int calculaCusto(grafo g, int *rota);
int calculaNInicial(grafo g, int *rota);
void printMatriz(grafo g);
void printRota(grafo g, int *rota);

#endif // TSP_H_INCLUDED
