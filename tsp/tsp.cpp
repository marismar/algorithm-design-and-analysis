#include "tsp.h"

void iniciaGrafo(grafo *g, ifstream &instancia){
    instancia >> g->n_elementos;

    g->elementos = new int*[g->n_elementos];
    for (int u = 0; u < g->n_elementos; u++) g->elementos[u] = new int[g->n_elementos];

    string valor;
    for(int i = 0; i < g->n_elementos; i++){
        for(int j = 0; j < g->n_elementos; j++){
            instancia >> valor;
            g->elementos[i][j] = atoi(valor.c_str());
        }
    }
}

void HVMP(grafo g, int *rota, int n_inicial){    //Heuristica de construção do vizinho mais proximo
    bool elem_adicionados[g.n_elementos];
    for(int u = 0; u < g.n_elementos; u++) elem_adicionados[u] = false;

    elem_adicionados[n_inicial] = true;
    rota[0] = n_inicial;

    for(int i = 0; i < g.n_elementos; i++){
        int distancia_min = INFINITO;
        int n_proximo;

        for(int j = 0; j < g.n_elementos; j++){
            if((elem_adicionados[j] == false) && (distancia_min > g.elementos[rota[i]][j]) && (i != j)){  //se o elemento nao já estiver contido na rota, e for a menor distancia
                distancia_min = g.elementos[rota[i]][j];
                n_proximo = j;
            }
        }
        rota[i + 1] = n_proximo;    //adiciona o proximo a rota
        elem_adicionados[n_proximo] = true; //salva o proximo como adicionado a rota
    }
    rota[g.n_elementos] = n_inicial;    //retorna ao ponto inicial ao fim da rota
}

int *opt2(grafo g, int *rota){
    int custo = calculaCusto(g, rota);
    cout << "custo inicial :" << " ";
    cout << custo << endl;
    int *rt_opt = new int[g.n_elementos + 1];
    copiaArray(rt_opt, rota, g.n_elementos);
    for(int i = 1; i < g.n_elementos - 1; i++){
        for (int j = i + 1; j < g.n_elementos; j++){
            int *rt_aux = new int[g.n_elementos + 1];
            copiaArray(rt_aux, rota, g.n_elementos);
            flip(g.n_elementos, rota, rt_aux, i, j);
            if (custo > calculaCusto(g, rt_aux)){
                custo = calculaCusto(g, rt_aux);
                copiaArray(rt_opt, rt_aux, g.n_elementos);
            }
        }
    }
    printRota(g, rt_opt);
    cout << "custo final: " << " ";
    cout << custo << endl;

    return rt_opt; //rota aprimorada, com o custo menor que a rota inicial
}

int *swap(grafo g, int *rota){
    int custo = calculaCusto(g, rota);
    int *rt_swap = new int[g.n_elementos + 1];
    copiaArray(rt_swap, rota, g.n_elementos);
    for(int i = 1; i < g.n_elementos; i++){
        int *rt_aux = new int[g.n_elementos + 1];
        copiaArray(rt_aux, rota, g.n_elementos);
        for(int j = i + 1; j < g.n_elementos; j++){
            int aux = rt_aux[j];
            rt_aux[j] = rt_aux[i];
            rt_aux[i] = aux;
            if (custo > calculaCusto(g, rt_aux)){
                custo = calculaCusto(g, rt_aux);
                copiaArray(rt_swap, rt_aux, g.n_elementos);
            }
        }
    }
    return rt_swap;
}

static void flip(int n_elementos, int *rota, int *rt_aux, int lim1, int lim2){
    for(int a = 0; a < lim1; a++) rt_aux[a] = rota[a];
    for(int a = lim1, b = 0; a <= lim2; a++, b++)  rt_aux[a] = rota[lim2 - b];
    for(int a = lim2 + 1; a < n_elementos; a++) rt_aux[a] = rota[a];
}

static void copiaArray(int *destino, int *origem, int n_elementos){
    for (int u = 0; u <= n_elementos; u++)  destino[u] = origem[u];
}

int calculaCusto(grafo g, int *rota){
    int custo = 0;
    for (int u = 0; u < g.n_elementos - 1; u++) custo += g.elementos[rota[u]][rota[u + 1]];
    return custo;
}

int calculaNInicial(grafo g, int *rota){
    int n_inicial;
    int custo_min = INFINITO;
    for(int u = 0; u < g.n_elementos; u++){
        HVMP(g, rota, u);
        int custo = calculaCusto(g, rota);
        cout << "n_inicial:" << " ";
        cout << u << endl;
        cout << "custo:" << " ";
        cout << custo << endl;
        if (custo_min > custo){
            custo_min = custo;
            n_inicial = u;
        }
    }
    cout << "custo minimo:" << " ";
    cout << custo_min << endl;
    cout << "n_inicial_final:" << " ";
    cout << n_inicial << endl;
    return n_inicial;
}

void printMatriz(grafo g){
    cout << "Matriz de adjacencias: " << endl;
    for(int i = 0; i < g.n_elementos; i++){
        for(int j = 0; j < g.n_elementos; j++) cout << g.elementos[i][j] << " ";
        cout << endl;
    }
}

void printRota(grafo g, int *rota){
    cout << "Rota: " << endl;
    for(int u = 0; u <= g.n_elementos; u++) cout << rota[u] << " ";
    cout << endl;
}
