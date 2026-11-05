/**
 * 07-comparativo-operacional.c
 *
 * Programa comparativo de desempenho e métricas operacionais:
 * - Submete Selection Sort e Insertion Sort a três cenários de entrada:
 *   1. Arranjo já ordenado (melhor caso)
 *   2. Arranjo inversamente ordenado (pior caso)
 *   3. Arranjo com distribuição pseudoaleatória
 * - Contabiliza rigorosamente comparações de chaves e operações de escrita em memória
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define N 1000

typedef struct {
    size_t comparacoes;
    size_t escritas_memoria;
} Metricas;

/* Selection Sort com contagem de comparações e escritas (3 escritas por troca) */
static Metricas executa_selection_sort(int arr[], size_t n) {
    Metricas m = {0, 0};

    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            m.comparacoes++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            m.escritas_memoria += 3; /* 1 troca = 3 escritas na memória */
        }
    }
    return m;
}

/* Insertion Sort com contagem de comparações e escritas */
static Metricas executa_insertion_sort(int arr[], size_t n) {
    Metricas m = {0, 0};

    for (size_t i = 1; i < n; i++) {
        int chave = arr[i];
        ptrdiff_t j = (ptrdiff_t)i - 1;

        while (j >= 0) {
            m.comparacoes++;
            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                m.escritas_memoria++; /* 1 deslocamento = 1 escrita */
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
        m.escritas_memoria++; /* Inserção final da chave */
    }
    return m;
}

static void gera_cenarios(int ord[], int inv[], int rand_arr[], size_t n) {
    srand(42); /* Semente fixa para reprodutibilidade */
    for (size_t i = 0; i < n; i++) {
        ord[i] = (int)i;
        inv[i] = (int)(n - 1 - i);
        rand_arr[i] = rand() % 10000;
    }
}

int main(void) {
    puts("=== 07: Comparativo Operacional (N = 1000 elementos) ===\n");

    int base_ord[N], base_inv[N], base_rand[N];
    gera_cenarios(base_ord, base_inv, base_rand, N);

    int buffer_sel[N];
    int buffer_ins[N];

    puts("+--------------------+---------------------------+---------------------------+");
    puts("| Cenário de Entrada | Selection Sort            | Insertion Sort            |");
    puts("|                    | Comparacoes | Escritas    | Comparacoes | Escritas    |");
    puts("+--------------------+-------------+-------------+-------------+-------------+");

    /* 1. Já Ordenado */
    memcpy(buffer_sel, base_ord, sizeof(base_ord));
    memcpy(buffer_ins, base_ord, sizeof(base_ord));
    Metricas sel_ord = executa_selection_sort(buffer_sel, N);
    Metricas ins_ord = executa_insertion_sort(buffer_ins, N);
    printf("| Já Ordenado        | %11zu | %11zu | %11zu | %11zu |\n",
           sel_ord.comparacoes, sel_ord.escritas_memoria,
           ins_ord.comparacoes, ins_ord.escritas_memoria);

    /* 2. Inverso */
    memcpy(buffer_sel, base_inv, sizeof(base_inv));
    memcpy(buffer_ins, base_inv, sizeof(base_inv));
    Metricas sel_inv = executa_selection_sort(buffer_sel, N);
    Metricas ins_inv = executa_insertion_sort(buffer_ins, N);
    printf("| Inversamente Ord.  | %11zu | %11zu | %11zu | %11zu |\n",
           sel_inv.comparacoes, sel_inv.escritas_memoria,
           ins_inv.comparacoes, ins_inv.escritas_memoria);

    /* 3. Aleatório */
    memcpy(buffer_sel, base_rand, sizeof(base_rand));
    memcpy(buffer_ins, base_rand, sizeof(base_rand));
    Metricas sel_rand = executa_selection_sort(buffer_sel, N);
    Metricas ins_rand = executa_insertion_sort(buffer_ins, N);
    printf("| Aleatório (Médio)  | %11zu | %11zu | %11zu | %11zu |\n",
           sel_rand.comparacoes, sel_rand.escritas_memoria,
           ins_rand.comparacoes, ins_rand.escritas_memoria);

    return 0;
}
