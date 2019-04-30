#include "tsp.h"

using namespace std;

int main()
{
    ifstream instancia;
    instancia.open("instancias/instancias_teste/bayg29.txt", ios::in);

    grafo g;
    iniciaGrafo(&g, instancia);
    printMatriz(g);

    int rota[g.n_elementos + 1];
    HVMP(g, rota, calculaNInicial(g, rota));

    printRota(g, rota);

    int a = calculaCusto(g, rota);

    cout << a << endl;

    opt2(g, rota);

    return 0;
}
