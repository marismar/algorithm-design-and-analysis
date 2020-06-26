void merge(int *vetor, int inicio, int meio, int fim){
    int n1 = 0, n2 = 0;  //indices dos vetores temporarios
    int *metade1 = malloc(sizeof(int)*(meio-inicio+1));
    int *metade2 = malloc(sizeof(int)*(fim-meio));
    if(metade1 == NULL || metade2 == NULL)
        exit(EXIT_FAILURE);

    for (int i = 0; i < (meio-inicio+1); i++)
        metade1[i] = vetor[inicio+i];
    for (int i = 0; i < (fim-meio); i++)
        metade2[i] = vetor[meio+i+1];

    for (int k = inicio; k <= fim; k++){
        if (n1 < (meio-inicio+1) && n2 < (fim-meio)){
            if (metade1[n1] <= metade2[n2]){
                vetor[k] = metade1[n1];
                n1++;
            } else {
                vetor[k] = metade2[n2];
                n2++;
            }
        } else if (n1 < (meio-inicio+1)){
            vetor[k] = metade1[n1];
            n1++;
        } else if (n2 < (fim-meio)){
            vetor[k] = metade2[n2];
            n2++;
        }
    }
    free(metade1);
    free(metade2);
}

void mergeSort(int *vetor, int inicio, int fim){
    if(inicio<fim){
        int meio = (int) (inicio+fim)/2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
}
