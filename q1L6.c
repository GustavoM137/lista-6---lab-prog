#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
int *endereco_primeiro_par(const int *const pont, unsigned tam_p);

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

    int *primeiro_par = endereco_primeiro_par(vet, n);
    if (primeiro_par == NULL){
        puts("O vetor não contém nenhum elemento par");
        free(vet);
        vet = NULL;

        return 0;
    }
    printf("Endereço do primeiro par (%d): [%p]\n", *primeiro_par, (void *) primeiro_par);

    free(vet);
    vet = NULL;

    return 0;
}

void *alocar_mem(unsigned tam_p, size_t tam_tipo){
    return malloc(tam_p * tam_tipo);
}

void popular_pont(int *const pont, unsigned tam_p){
    for (unsigned i = 0; i < tam_p; i++){
        *(pont + i) = MIN + rand() % (MAX - MIN + 1);
    }
}

int *endereco_primeiro_par(const int *const pont, unsigned tam_p){
    for (unsigned i = 0; i < tam_p; i++){
        if (*(pont + i) % 2 == 0) return pont + i;
    }
    return NULL;
}