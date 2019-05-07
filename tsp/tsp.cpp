#include "tsp.h"

void iniciaGrafo(grafo *g, ifstream &instancia){
    instancia >> g->n_elementos;


    /*int i , j[100], Total, k, l, mult;
    string text;

	if (instancia.is_open() && instancia.good()){

			getline(instancia, text);
			//instancia >> text;
			//cout<<text;
			for (i = 0, k=0; i < text.length(); i++){

    			cout << text[i] << " - " << (int)text[i] << endl;
    			if((int)text[i]>=48  && (int)text[i]<=57){
    				j[k]=(int)text[i]-48;
    				cout<<"      "<<k<<" - "<<j[k]<<endl;
    				k++;
				}
			}cout<<endl<<k<<endl;
            for(i=0, Total=0, mult=0; k>0; k--, i++){
                cout<<(j[i])<< " ";
                for(l=0, mult=1; l<k-1; l++){
                    mult*=10;
                }
                //if(mult!=0)
                    Total+=(j[i])*(mult);
                //else
                //	Total+=j[i];

                cout<<" -> "<<mult<<" = "<< Total<<endl;
            }
                        cout<<endl<<endl <<Total<< endl;
		}

    g->n_elementos = Total;*/

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
    for(int i = 1; i < g.n_elementos; i++){ //nao troca o valor inicial
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

int *VND(grafo g, int *rota){
    int n_estruturas = 2, estrutura = 1;
    int *rt_vnd = new int[g.n_elementos + 1];
    copiaArray(rt_vnd, rota, g.n_elementos);

    while(estrutura <= n_estruturas){
        rt_vnd = (estrutura == 1 ? opt2(g, rota):swap(g, rota));
        if(calculaCusto(g, rota) > calculaCusto(g, rt_vnd)){
            copiaArray(rota, rt_vnd, g.n_elementos);
            estrutura = 1;
        } else {
            estrutura++;
        }
    }
    printRota(g, rota);
    int a = calculaCusto(g, rota);
    cout << "custo: " << " ";
    cout << a << endl;
    return rota;
}

/*int *GRASP(grafo g, int grasp_max, int *rota){
    custo = INFINITO;
    for(int interacao = 0; interacao < grasp_max; interacao++){
        int *rt_grasp = new int[g.n_elementos + 1];
        rt_grasp = VND(g, construcao(g, alpha, rota));
        if (custo > calculaCusto(g, rt_grasp){
            copiaArray(rota, rt_grasp, g.n_elementos);
            custo = calculaCusto(g, rt_grasp);
        }
    }
    copiaArray(rt)
    return rota;
}*/

static void flip(int n_elementos, int *rota, int *rt_aux, int lim1, int lim2){
    for(int a = 0; a < lim1; a++) rt_aux[a] = rota[a];
    for(int a = lim1, b = 0; a <= lim2; a++, b++)  rt_aux[a] = rota[lim2 - b];
    for(int a = lim2 + 1; a < n_elementos; a++) rt_aux[a] = rota[a];
}

vector<int> construcao(grafo g, int alpha){
    vector<int> rota;
    srand (time(NULL));
    int n_inicial = rand() % g.n_elementos;
    rota.push_back((int)(n_inicial));

    vector<elemento> LC;
    for(int j = 0; j < g.n_elementos; j++){ //inicializa a lc para o vertice inicial
        if (j != n_inicial) LC.push_back(iniciaElemento(g, rota[rota.size() - 1], j));
    }

    while (LC.size() != 0){
        int *minimo, *maximo;
        custoMaxMin(LC, minimo, maximo);
        int restricao = *minimo - alpha * (*maximo - *minimo);
        vector<int> LCR;
        for(int i = 0; i < LC.size(); i++){
            if (LC[i].custo <= restricao)   LCR.push_back(LC[i].id);
        }
        rota.push_back(LCR[rand() % LCR.size()]);
    }

    rota.push_back(rota[0]); //adiciona o primeiro elemento ao final para fechar o ciclo hamiltoniano
    return rota;
/*    int origem = rand()%(g.n_elementos - 1);

    int max = 0, min = INFINITO, LCR_tam=0, s, sol;
    int LCR_vector[g.n_elementos];
    int *rt_aux = new int[g.n_elementos + 1];
    for (int u = 0; u < g.n_elementos; u++){
        if(g.elementos[origem][u] != 0) rt_aux[u] = g.elementos[origem][u];
    }
    for (int i = 0; i < g.n_elementos; i++){
        for(int u = 0; u <g.n_elementos; u++){
            if (rt_aux[u] > max) max = rt_aux[u];
            if (rt_aux[u] < min) min = rt_aux[u];
        }
        int LCR = min + alpha*(max-min);
        for(int i=0; i<g.n_elementos; i++){
            if(re_aux[i]<= LCR){
                LCR_vector[LCR_tam] = re_aux[i];
                LCR_tam++;
        }
        srand(time(0));
        s = rand()%(LCR_tam-1);
        sol = LCR_vector[s];
    }
    return sol;
}*/
}

static elemento iniciaElemento(grafo g, int linha, int coluna){
    elemento elem;
    elem.id = coluna;
    elem.custo = g.elementos[linha][coluna];
    return elem;
}

static void copiaArray(int *destino, int *origem, int n_elementos){
    for (int u = 0; u <= n_elementos; u++)  destino[u] = origem[u];
}

int calculaCusto(grafo g, int *rota){
    int custo = 0;
    for (int u = 0; u < g.n_elementos; u++) custo += g.elementos[rota[u]][rota[u + 1]];
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
