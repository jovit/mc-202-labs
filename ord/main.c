//
// Created by joao on 26/09/16.
//
#include <stdio.h>
int comparacoes = 0;
int trocas = 0;

int main() {
    int vetor[6];
    vetor[0] =2;
    vetor[1] =3;
    vetor[2] =2;
    vetor[3] =4;
    vetor[4] =9;
    vetor[5] =10;
    quick_sort(vetor,0, 5);

    printf("%d\n", comparacoes);
    printf("%d\n", trocas);
}

void troca(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
}

int particionar(int vetor[], int ini, int fim) {
    int pivo;
    pivo = vetor[fim];
    while (ini < fim) {
        while (ini < fim && vetor[ini] <= pivo)
            ini++;
        while (ini < fim && vetor[fim] >= pivo)
            fim--;
        troca(&vetor[ini], &vetor[fim]);
    }
    return ini; // ini é a posição do primeiro elemento grande
}

void quick_sort(int vetor[], int ini, int fim) {
    int pos;
    if (ini < fim){
        pos = particionar(vetor, ini, fim);
        quick_sort(vetor, ini, pos - 1);
        quick_sort(vetor, pos, fim);
    }
}