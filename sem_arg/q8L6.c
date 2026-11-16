#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
void imprimir_matriz(int *const *const mat, unsigned lin, unsigned col);
void popular_matriz(int *const *const mat, unsigned lin, unsigned col);
int **criar_matriz(unsigned lin, unsigned col);
void liberar_mem(int **mat, unsigned lin);
void diagonal_p_soma(int *const *const mat, unsigned d);

int main(){
    unsigned dimensao;
    puts("Digite a dimensão da matriz:");
    while(scanf("%u", &dimensao) != 1 || dimensao == 0) puts("Valor inválido, digite novamente:");

    int **M = NULL;
    M = criar_matriz(dimensao, dimensao);
    if (M == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }

    srand(time(NULL));
    popular_matriz(M, dimensao, dimensao);

    puts("Matriz:");
    imprimir_matriz(M, dimensao, dimensao);

    diagonal_p_soma(M, dimensao);

    liberar_mem(M, dimensao);
    M = NULL;

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

void imprimir_matriz(int *const *const mat, unsigned lin, unsigned col){
    for (unsigned i = 0; i < lin; i++){
        for (unsigned j = 0; j < col; j++){
            printf("[%d] ", *(*(mat + i) + j));
        }
        putchar('\n');
    }
}

void popular_matriz(int *const *const mat, unsigned lin, unsigned col){
    for (unsigned i = 0; i < lin; i++){
        popular_pont(*(mat + i), col);
    }
}

int **criar_matriz(unsigned lin, unsigned col){
    int **mat = (int **) alocar_mem(lin, sizeof(int *));
    if (mat == NULL) return NULL;

    for (unsigned i = 0; i < lin; i++){
        *(mat + i) = (int *) alocar_mem(col, sizeof(int));

        if (*(mat + i) == NULL){
            while (i != 0){
                free(*(mat + i - 1));
                *(mat + i - 1) = NULL;
                i--;
            }
            free(mat);
            mat = NULL;
            return NULL;
        }
    }
    return mat;
}

void liberar_mem(int **mat, unsigned lin){
    for (unsigned i = 0; i < lin; i++){
        free(*(mat + i));
        *(mat + i) = NULL;
    }
    free(mat);
}

void diagonal_p_soma(int *const *const mat, unsigned d){
    int soma = 0;
    for (unsigned i = 0; i < d; i++){
        soma += *(*(mat + i) + i);
    }
    if (soma % 2 == 0) printf("A soma da diagonal principal é par: %d\n", soma);
    else printf("A soma da diagonal principal é ímpar: %d\n", soma);
}