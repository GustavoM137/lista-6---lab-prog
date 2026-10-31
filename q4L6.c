#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(float *const pont, unsigned tam_p);
void soma_elementos(float *const s, const float *const p, unsigned tam_p);

int main(){
    unsigned n;
    puts("Digite o tamanho do vetor:");
    while(scanf("%u", &n) != 1 || n == 0) puts("Valor inválido, digite novamente:");

    float *vet = NULL;
    vet = (float *) alocar_mem(n, sizeof(float));
    if (vet == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }

    srand(time(NULL));
    popular_pont(vet, n);

    float soma = 0;
    soma_elementos(&soma, vet, n);

    puts("Vetor de float:");
    for (unsigned i = 0; i < n; i++){
        printf("[%.2f] ", *(vet + i));
    }
    putchar('\n');

    printf("Soma dos elementos: %.2f\n", soma);

    free(vet);
    vet = NULL;

    return 0;
}

void *alocar_mem(unsigned tam_p, size_t tam_tipo){
    return malloc(tam_p * tam_tipo);
}

void popular_pont(float *const pont, unsigned tam_p){
    for (unsigned i = 0; i < tam_p; i++){
        *(pont + i) = MIN + (float) rand() / ((float) RAND_MAX / (float) (MAX - MIN));
    }
}

void soma_elementos(float *const s, const float *const p, unsigned tam_p){
    *s = 0;
    for (unsigned i = 0; i < tam_p; i++){
        *s += *(p + i);
    }
}