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

    int *rt_teste = new int[g.n_elementos + 1];

    rt_teste = opt2(g, rota);

    printRota(g, rt_teste);
    int a = calculaCusto(g, rt_teste);
    cout << "custo: " << " ";
    cout << a << endl;
    rt_teste = swap(g, rt_teste);
    printRota(g, rt_teste);
    a = calculaCusto(g, rt_teste);
    cout << "custo: " << " ";
    cout << a << endl;
    rt_teste = swap(g, rt_teste);
    printRota(g, rt_teste);
    a = calculaCusto(g, rt_teste);
    cout << "custo: " << " ";
    cout << a << endl;
    rt_teste = opt2(g, rt_teste);

    printRota(g, rt_teste);
    a = calculaCusto(g, rt_teste);
    cout << "custo: " << " ";
    cout << a << endl;
    cout << "OK" << endl;
    
    VND(g, rota);

    printRota(g, rota);
    a = calculaCusto(g, rota);
    cout << "custo: " << " ";
    cout << a << endl;

    return 0;
}
