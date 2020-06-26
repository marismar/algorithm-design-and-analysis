void insertionSort (int *A, int n){
    int *pivo = NULL;
    int j;
    for (int i = 1; i < n; i++){
        pivo = A[i];
        j = i-1;
        while(j>=0 && A[j]>pivo){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = pivo;
    }
}
