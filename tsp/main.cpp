#include "tsp.h"

using namespace std;

int main()
{
    ifstream instancia;
    instancia.open("instancias/instancias_tsp_cup/tsp1.txt", ios::in);

    grafo g;
    iniciaGrafo(&g, instancia);

    GRASP(g, 100);

    return 0;
}
