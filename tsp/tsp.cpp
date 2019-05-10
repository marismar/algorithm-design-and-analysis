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

vector<int> HVMP(grafo g, int n_inicial){    //Heuristica de construção do vizinho mais proximo
    vector<int> rota;   //define uma rota
    bool elem_adicionados[g.n_elementos];   //array para determinar se o elemento já foi adicionado a lista
    for(int u = 0; u < g.n_elementos; u++) elem_adicionados[u] = false; //inicializa todo mundo igual a false

    rota.push_back((int)(n_inicial));   //adiciona o elemento inicial a lista
    elem_adicionados[n_inicial] = true; //muda o valor do elemento inicial para true

    for(int i = 0; i < g.n_elementos - 1; i++){
        int distancia_min = INFINITO;   //define a distancia minima como infinita
        int n_proximo = -1; //proximo elemento a ser adicionado a lista recebe valor nulo
        for(int j = 0; j < g.n_elementos; j++){
            if((elem_adicionados[j] == false) && (distancia_min > g.elementos[rota[i]][j]) && (i != j)){  //se o elemento nao estiver contido na rota e for a menor distancia
                distancia_min = g.elementos[rota[i]][j];    //atualiza a distancia minima encontrada
                n_proximo = j;  //salva o indice como o proximo elemento em potencial a ser adicionado na rota
            }
        }
        rota.push_back((int)(n_proximo));    //adiciona o proximo a rota
        elem_adicionados[n_proximo] = true; //salva o proximo como adicionado a rota
    }
    rota.push_back((int)(n_inicial));    //adiciona o ponto inicial ao fim da rota para fechar o ciclo hamiltoniano
    return rota;    //retorna a rota
}

vector<int> opt2(grafo g, vector<int> rota){
    int custo_inicial = calculaCusto(g, rota);    //salva o custo da solucao inicial
    vector<int> rt_opt; //define a rota que a funcao ira retornar
    int lim1 = -1, lim2 = -1;   //valores de indice nulos
    int menor_custo = custo_inicial; //menor custo inicializado com um valor muito grande
    for(int i = 1; i < g.n_elementos; i++){
        for(int j = i + 1; j < g.n_elementos; j++){
            int custo_aux = custo_inicial - g.elementos[rota[i-1]][rota[i]] - g.elementos[rota[j]][rota[j+1]]
                                          + g.elementos[rota[i-1]][rota[j]] + g.elementos[rota[i]][rota[j+1]];
            if (custo_aux < menor_custo){
                menor_custo = custo_aux;
                lim1 = i;
                lim2 = j;
            }
        }
    }

    if(lim1 == -1)  rt_opt = rota; //se nao encontrar nenhuma rota mais curta, rt_opt recebe a rota original
    else rt_opt = flip(g, rota, rt_opt, lim1, lim2); //salva a rota mais curta em rt_opt
    return rt_opt; //rota aprimorada, com o custo menor que a rota inicial
}

vector<int> swap(grafo g, vector<int> rota){
    int custo_inicial = calculaCusto(g, rota);
    vector<int> rt_swap;
    rt_swap = rota;
    int indice1 = -1, indice2 = -1; //valores de indice nulos
    int menor_custo = INFINITO; //menor custo inicializado com um valor muito grande
    for(int i = 1; i < g.n_elementos; i++){
        for(int j = i + 1; j < g.n_elementos; j++){
            int custo_aux = custo_inicial - g.elementos[rota[i-1]][rota[i]] - g.elementos[rota[i]][rota[i+1]]
                                          - g.elementos[rota[j-1]][rota[j]] - g.elementos[rota[j]][rota[j+1]]
                                          + g.elementos[rota[i-1]][rota[j]] + g.elementos[rota[j]][rota[i+1]]
                                          + g.elementos[rota[j-1]][rota[i]] + g.elementos[rota[i]][rota[j+1]];
            if (custo_aux < menor_custo){
                menor_custo = custo_aux;
                indice1 = i;
                indice2 = j;
            }
         }
    }
    if (indice1 != -1){ //encontrou uma rota mais curta, entao faz a troca de elementos que equivale ao menor custo
        int aux = rt_swap[indice2];
        rt_swap[indice2] = rt_swap[indice1];
        rt_swap[indice1] = aux;
    }

    return rt_swap;
}

vector<int> reInsertion(grafo g, vector<int> rota){
    int custo_inicial = calculaCusto(g, rota);
    vector<int> rt_rit;
    rt_rit = rota;
    int indice1 = -1, indice2 = -1; //valores de indice nulos
    int menor_custo = INFINITO; //menor custo inicializado com um valor muito grande
    for(int i = 1; i < g.n_elementos; i++){
        for(int j = i + 1; j < g.n_elementos; j++){
            int custo_aux = custo_inicial - g.elementos[rota[i-1]][rota[i]] - g.elementos[rota[i]][rota[i+1]] - g.elementos[rota[j]][rota[j+1]]
                                          + g.elementos[rota[i-1]][rota[i+1]] + g.elementos[rota[j]][rota[i]] + g.elementos[rota[i]][rota[j+1]];
            if (custo_aux < menor_custo){
                menor_custo = custo_aux;
                indice1 = i;
                indice2 = j;
            }
         }
    }
    if (indice1 != -1){
        rt_rit.erase(rt_rit.begin()+indice1);
        rt_rit.insert(rt_rit.begin()+indice2, rota[indice1]);
    }

    return rt_rit;
}

vector<int> VND(grafo g, vector<int> rota){
    //int n_estruturas = 2, estrutura = 1;
    int n_estruturas = 3, estrutura = 1;
    vector<int> rt_vnd;
    while(estrutura <= n_estruturas){
        //rt_vnd = (estrutura == 1 ? opt2(g, rota):swap(g, rota));
        if(estrutura == 1) rt_vnd = opt2(g, rota);
        else if(estrutura == 2) rt_vnd = swap(g, rota);
        else rt_vnd = reInsertion(g, rota);

        if(calculaCusto(g, rt_vnd) < calculaCusto(g, rota)){
            rota = rt_vnd;
            estrutura = 1;
        } else {
            estrutura++;
        }
    }
    return rota;
}

void GRASP(grafo g, int grasp_max){
    int custo = INFINITO;
    vector<int> solucao;
    for(int i = 0; i < grasp_max; i++){
        vector<int> rt_grasp;
        rt_grasp = construcao(g, 0.2);
        rt_grasp = VND(g, rt_grasp);
        if (custo > calculaCusto(g, rt_grasp)){
            custo = calculaCusto(g, rt_grasp);
            solucao = rt_grasp;

        }
    }
    printRota(g, solucao);
    cout << "custo da solucao final: ";
    cout << custo << endl;
}

static vector<int> flip(grafo g, vector<int> rota, vector<int> rt_opt, int lim1, int lim2){
    for(int a = 0; a < lim1; a++) rt_opt.push_back(rota[a]);
    for(int a = lim1, b = 0; a <= lim2; a++, b++)  rt_opt.push_back(rota[lim2 - b]);
    for(int a = lim2 + 1; a <= g.n_elementos; a++) rt_opt.push_back(rota[a]);
    return rt_opt;
}

static vector<int> construcao(grafo g, float alpha){
    vector<int> rota;   //define a solucao a ser construida
    srand (time(NULL)); //para que a cada compilação, novos valores aleatorios sejam gerados
    int n_inicial = rand() % g.n_elementos; //seleciona uma origem aleatoriamente
    rota.push_back((int)(n_inicial)); //adiciona a origem a rota

    vector<elemento> LC;    //define a lista de candidatos
    for(int j = 0; j < g.n_elementos; j++){ //inicializa a lista de candidatos para o vertice inicial
        if (j != n_inicial) LC.push_back(iniciaElemento(g, n_inicial, j));
    }

    sort(LC.begin(), LC.end(), ordenaVector);  //ordena a lista de candidatos

    while (LC.size() != 0){ //enquanto a lista de candidatos não for vazia
        int minimo = LC[0].custo;   //como a lc esta ordenada o custo minimo será o primeiro elemento da lista
        int maximo = LC[LC.size() - 1].custo; //assim como o valor maximo será o ultimo elemento
        int restricao = minimo + alpha*(maximo - minimo); //calculo do valor da restricao

        vector<int> LCR; //define a lista de candidatos restritos

        for(int i = 0; i < LC.size(); i++){
            if(LC[i].custo <= restricao) LCR.push_back(LC[i].id); //adiciona a lrc todos os elementos da lc que respeitam a restricao
        }

      	int indice_n =  rand() % LCR.size();  //seleciona aleatoriamente um elemento de lcr para adicionar a solucao
        rota.push_back(LCR[indice_n]);  //adiciona o elemento a solucao
        LCR.clear(); //limpa a lista de candidatos restrito

      	for(int i = 0; i < LC.size(); i++){
            LC[i].custo = g.elementos[LC[indice_n].id][LC[i].id];   //atualiza os custo dos elementos da lista de candidatos
        }

        LC.erase(LC.begin()+indice_n);  // exclui da lista de candidatos o elemento já adicionado a rota
        sort(LC.begin(), LC.end(), ordenaVector);  //ordena a lista atualizada
    }

    rota.push_back(rota[0]); //adiciona o primeiro elemento ao final para fechar o ciclo hamiltoniano
    return rota;
}

static elemento iniciaElemento(grafo g, int linha, int coluna){
    elemento elem;
    elem.id = coluna;
    elem.custo = g.elementos[linha][coluna];
    return elem;
}

static bool ordenaVector (elemento elem1, elemento elem2){
    return (elem1.custo < elem2.custo);
}

int calculaCusto(grafo g, vector<int> rota){
    int custo = 0;
    for (int u = 0; u < g.n_elementos; u++) custo += g.elementos[rota[u]][rota[u + 1]];
    return custo;
}

int calculaNInicial(grafo g){
    int n_inicial;
    int menor_custo = INFINITO;
    vector<int> rota;
    for(int u = 0; u < g.n_elementos; u++){
        rota = HVMP(g, u);
        int custo = calculaCusto(g, rota);
        if (menor_custo > custo){
            menor_custo = custo;
            n_inicial = u;
        }
    }
    return n_inicial;
}

void printMatriz(grafo g){
    cout << "Matriz de adjacencias: " << endl;
    for(int i = 0; i < g.n_elementos; i++){
        for(int j = 0; j < g.n_elementos; j++) cout << g.elementos[i][j] << " ";
        cout << endl;
    }
}

void printRota(grafo g, vector<int> rota){
    cout << "Rota: " << endl;
    for(int u = 0; u < rota.size(); u++) cout << rota[u] << " ";
    cout << endl;
}
