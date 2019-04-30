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

    cout << "Hello world!" << endl;

    return 0;
}
