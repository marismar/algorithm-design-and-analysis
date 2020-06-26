int countingSort(int *A, int *B, int k, int n){
    int *C = malloc(sizeof(int)*10);
    for(int x = 0; x <= 10; x++){
        C[x] = 0;
    }
    for(int x = 0; x < 10; x++) {
        C[A[x]] = C[A[x]] + 1;
    }
    for(int i = 1; i <= 10; i++){
        C[i] = C[i] + C[i+1];
    }
    for (int j = 9; j >= 0; j--){
        B[C[A[j]] - 1] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }
    return 0;
}
