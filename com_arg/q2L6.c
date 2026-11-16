#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
int *endereco_primeiro_par(int *const pont, unsigned tam_p);
int *endereco_ultimo_par(int *const pont, unsigned tam_p);
int **vetor_par(int *const pont, unsigned tam_p);

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

    int **vet_par = vetor_par(vet, n);
    if (vet_par == NULL){
        puts("Erro ao alocar memória");
        free(vet);
        vet = NULL;

        return 1;
    }
    if (*vet_par == NULL){
        puts("O vetor não contém nenhum elemento par");
    }
    else {
        puts("Vetor que contém o primeiro e último elemento par:");
        printf("Primeiro(%d): %p\n", **vet_par, (void *) *vet_par);
        printf("Último(%d): %p\n", **(vet_par + 1), (void *) *(vet_par + 1));
    }

    free(vet);
    vet = NULL;
    free(vet_par);
    vet_par = NULL;

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

int *endereco_primeiro_par(int *const pont, unsigned tam_p){
    for (unsigned i = 0; i < tam_p; i++){
        if (*(pont + i) % 2 == 0) return pont + i;
    }
    return NULL;
}

int *endereco_ultimo_par(int *const pont, unsigned tam_p){
    for (unsigned i = tam_p - 1; i < tam_p; i--){
        if (*(pont + i) % 2 == 0) return pont + i;
    }
    return NULL;
}

int **vetor_par(int *const pont, unsigned tam_p){
    int **vetor_par = (int **) alocar_mem(2, sizeof(int *));
    if (vetor_par == NULL) return NULL;

    *vetor_par = endereco_primeiro_par(pont, tam_p);
    *(vetor_par + 1) = endereco_ultimo_par(pont, tam_p);
    return vetor_par;
}