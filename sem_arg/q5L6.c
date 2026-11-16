#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
float media_vetor(const int *const p, unsigned tam_p);
float mediana_vetor(const int *const p, unsigned tam_p);
int moda_vetor(const int *const p, unsigned tam_p);
void ordenar_vetor(int *const p, unsigned tam_p);

int main(){
    unsigned n;
    puts("Digite o tamanho do vetor:");
    while(scanf("%u", &n) != 1 || n == 0) puts("Valor inválido, digite novamente:");

    int *vet = NULL;
    vet = (int *) alocar_mem(n, sizeof(int));
    if (vet == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }

    srand(time(NULL));
    popular_pont(vet, n);

    puts("Vetor:");
    for (unsigned i = 0; i < n; i++){
        printf("[%d] ", *(vet + i));
    }
    putchar('\n');

    ordenar_vetor(vet, n);
    float media = media_vetor(vet, n);
    float mediana = mediana_vetor(vet, n);
    int moda = moda_vetor(vet, n);

    printf("Média: %.2f\nMediana: %.2f\nModa: %d\n", media, mediana, moda);

    free(vet);
    vet = NULL;

    return 0;
}

void *alocar_mem(unsigned tam_p, size_t tam_tipo){
    return malloc(tam_p * tam_tipo);
}

void popular_pont(int *const p, unsigned tam_p){
    for (unsigned i = 0; i < tam_p; i++){
        *(p + i) = MIN + rand() % (MAX - MIN + 1);
    }
}

float media_vetor(const int *const p, unsigned tam_p){
    float soma = 0;

    for (unsigned i = 0; i < tam_p; i++){
        soma += *(p + i);
    }
    return soma / tam_p;
}

float mediana_vetor(const int *const p, unsigned tam_p){
    if (tam_p % 2 == 0) return (float) (*(p + (tam_p / 2)) + *(p + ((tam_p / 2) - 1))) / 2;
    else return (float) *(p + ((tam_p - 1) / 2));
}

int moda_vetor(const int *const p, unsigned tam_p){
    // o vetor deve estar ordenado
    int moda, freq_moda, atual, freq_atual;
    moda = atual = *p;
    freq_moda = freq_atual = 1;

    for (unsigned i = 1; i < tam_p; i++){
        if (*(p + i) == atual) freq_atual++;
        else{
            atual = *(p + i);
            freq_atual = 1;
        }
        if (freq_atual > freq_moda){
            moda = atual;
            freq_moda = freq_atual;
        }
    }
    return moda;
}

void ordenar_vetor(int *const p, unsigned tam_p){
    unsigned char flag;
    for (unsigned i = 1; i < tam_p; i++){
        flag = 1;
        for (unsigned j = 0; j < tam_p - i; j++){
            if (*(p + j) > *(p + (j + 1))){
                int temp = *(p + j);
                *(p + j) = *(p + (j + 1));
                *(p + (j + 1)) = temp;

                flag = 0;
            }
        }
        if (flag) break;
    }
}