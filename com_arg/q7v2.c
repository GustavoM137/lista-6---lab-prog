#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MIN (-128)
#define MAX 127

void *alocar_mem(unsigned tam_p, size_t tam_tipo);
void popular_pont(int *const pont, unsigned tam_p);
void binarizar_matriz(int *const *const mat_s, int *const *const mat, unsigned lin, unsigned col, int limiar);
void imprimir_matriz(int *const *const mat, unsigned lin, unsigned col);
void popular_matriz(int *const *const mat, unsigned lin, unsigned col);
int **criar_matriz(unsigned lin, unsigned col);
void liberar_mem(int **mat, unsigned lin);

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("Uso: %s <quantidade_linhas> <quantidade_colunas> <limiar(intervalo [-128,127])>\n", *argv);
        return 1;
    }

    int tam_l = atoi(argv[1]);
    if (tam_l <= 0){
        puts("Quantidade de linhas inválida");
        return 1;
    }
    int tam_c = atoi(argv[2]);
    if (tam_c <= 0){
        puts("Quantidade de colunas inválida");
        return 1;
    }
    unsigned linhas = tam_l, colunas = tam_c;
    
    int t = atoi(argv[3]);
    if (t > MAX || t < MIN){
        puts("Limiar inválido");
        return 1;
    }
    
    int **M = NULL;
    M = criar_matriz(linhas, colunas);
    if (M == NULL){
        puts("Erro ao alocar memória");
        return 1;
    }

    srand(time(NULL));
    popular_matriz(M, linhas, colunas);

    puts("Matriz:");
    imprimir_matriz(M, linhas, colunas);


    int **S = NULL;
    S = criar_matriz(linhas, colunas);
    if (S == NULL){
        puts("Erro ao alocar memória");
        liberar_mem(M, linhas);
        M = NULL;
        return 1;
    }
    
    binarizar_matriz(S, M, linhas, colunas, t);
    puts("Matriz binarizada:");
    imprimir_matriz(S, linhas, colunas);

    liberar_mem(M, linhas);
    M = NULL;
    liberar_mem(S, linhas);
    S = NULL;

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

void binarizar_matriz(int *const *const mat_s, int *const *const mat, unsigned lin, unsigned col, int limiar){
    for (unsigned i = 0; i < lin; i++){
        for (unsigned j = 0; j < col; j++){
            if (*(*(mat + i) + j) > limiar) *(*(mat_s + i) + j) = 1;
            else *(*(mat_s + i) + j) = 0;
        }
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