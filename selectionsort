void selectionSort(int *A, int n){
    int i_min;
    for (int i = 0; i<n; i++){
        i_min = i;
        for(int j = i+1; j<n; j++)
            if (A[j]<A[i_min]) i_min=j;
        if (A[i] != A[i_min]){
            int temp = A[i];
            A[i] = A[i_min];
            A[i_min]= temp;
        }
    }
}
