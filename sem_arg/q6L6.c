#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(float *const pont, unsigned tam_p);
float erro_medio_quadratico(const float *const pA, const float *const pB, unsigned tam_p);

int main(){
    unsigned n;
    puts("Digite o tamanho do vetor:");
    while(scanf("%u", &n) != 1 || n == 0) puts("Valor inválido, digite novamente:");

    float *A = NULL;
    A = (float *) alocar_mem(n, sizeof(float));
    if (A == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }
    float *B = NULL;
    B = (float *) alocar_mem(n, sizeof(float));
    if (B == NULL){
        puts("Erro ao alocar memória");
        free(A);
        A = NULL;
        return 1;
    }

    srand(time(NULL));
    popular_pont(A, n);
    popular_pont(B, n);

    puts("Vetor A:");
    for (unsigned i = 0; i < n; i++){
        printf("[%.2f] ", *(A + i));
    }
    putchar('\n');
    puts("Vetor B:");
    for (unsigned i = 0; i < n; i++){
        printf("[%.2f] ", *(B + i));
    }
    putchar('\n');

    float erro_mq = erro_medio_quadratico(A, B, n);
    printf("Erro médio quadrático: %.2f\n", erro_mq);

    free(A);
    A = NULL;
    free(B);
    B = NULL;

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

float erro_medio_quadratico(const float *const pA, const float *const pB, unsigned tam_p){
    float emq = 0;

    for (unsigned i = 0; i < tam_p; i++){
        float d = *(pA + i) - *(pB + i);
        emq += d * d;
    }
    return emq / tam_p;
}