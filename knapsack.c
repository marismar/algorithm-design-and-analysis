#include <stdlib.h>

int max(int x, int y){return (x>y) ? x : y;}

int knapsack(int M, int p, int v, int n){
    int k[n][M];    //matriz para salvar os valores das análises já feitas
    for (int i = 0; i <= n; i++){ //varre as linhas da matriz
        for(int m = 0; m < M; m++){ //varre as colunas de cada linha
            if (i == 0 || m == 0){  //no caso da capacidade ser zero ou não ter itens disponiveis
                k[i][m] = 0;  
            } else if (p[i-1] <= m){  
                k[i][m] = max(v[i-1] + k[i-1][m-p[i-1]], k[i-1][m]);  
            } else {  
                k[i][m] = k[i-1][m];
            }
        }
    }
    return k[n][M];
}

