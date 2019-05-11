#ifndef TSP_H_INCLUDED
#define TSP_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <math.h>

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
vector<int> HVMP(grafo g, int n_inicial);
vector<int> opt2(grafo g, vector<int> rota);
vector<int> swap(grafo g, vector<int> rota);
vector<int> reInsertion(grafo g, vector<int> rota);
vector<int> VND(grafo g, vector<int> rota);
void GRASP(grafo g, int grasp_max);
static vector<int> construcao(grafo g, float alpha);

/*------ FUNCOES AUXILIARES ------*/
static vector<int> flip(grafo g, vector<int> rota, int lim1, int lim2);
static elemento iniciaElemento(grafo g, int linha, int coluna);
static bool ordenaVector (elemento elem1, elemento elem2);
int calculaCusto(grafo g, vector<int> rota);
int calculaNInicial(grafo g);
void printMatriz(grafo g);
void printRota(grafo g, vector<int> rota);

#endif // TSP_H_INCLUDED
