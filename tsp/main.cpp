#include "tsp.h"

using namespace std;

int main()
{
    ifstream instancia;
    instancia.open("instancias/instancias_teste/bayg29.txt", ios::in);

    grafo g;
    iniciaGrafo(&g, instancia);

    GRASP(g, 2);


    return 0;
}
