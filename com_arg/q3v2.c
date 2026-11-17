#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
int min_pont(const int *const pont, unsigned tam_p);
int max_pont(const int *const pont, unsigned tam_p);
void normalizar_vet(float *const pont_norm, const int *const pont, unsigned tam_p, int menor, int maior);

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Uso: %s <tamanho_vetor>\n", *argv);
        return 1;
    }

    int tam = atoi(argv[1]);
    if (tam <= 0){
        puts("Valor inválido");
        return 1;
    }
    unsigned n = tam;

    int *x = NULL;
    x = (int *) alocar_mem(n, sizeof(int));
    if (x == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }

    srand(time(NULL));
    popular_pont(x, n);

    puts("Vetor:");
    for (unsigned i = 0; i < n; i++){
        printf("[%d] ", *(x + i));
    }
    putchar('\n');

    int min = min_pont(x, n);
    int max = max_pont(x, n);
    if (min == max){
        puts("Não é possível normalizar, min(x) = max(x)");
        free(x);
        x = NULL;

        return 0;
    }

    float *x_norm = NULL;
    x_norm = (float *) alocar_mem(n, sizeof(float));
    if (x_norm == NULL){
        puts("Erro ao alocar memória");
        free(x);
        x = NULL;
        
        return 1;
    }

    normalizar_vet(x_norm, x, n, min, max);
    puts("Vetor normalizado:");
    for(unsigned i = 0; i < n; i++){
        printf("[%.2f] ", *(x_norm + i));
    }
    putchar('\n');

    free(x);
    x = NULL;
    free(x_norm);
    x_norm = NULL;

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

int min_pont(const int *const pont, unsigned tam_p){
    int menor = *pont;

    for (unsigned i = 1; i < tam_p; i++){
        if (*(pont + i) < menor) menor = *(pont + i);
    }

    return menor;
}

int max_pont(const int *const pont, unsigned tam_p){
    int maior = *pont;

    for (unsigned i = 1; i < tam_p; i++){
        if (*(pont + i) > maior) maior = *(pont + i);
    }

    return maior;
}

void normalizar_vet(float *const pont_norm, const int *const pont, unsigned tam_p, int menor, int maior){
    for (unsigned i = 0; i < tam_p; i++){
        *(pont_norm + i) = (float) (*(pont + i) - menor) / (maior - menor);
    }
}