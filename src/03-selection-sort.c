/**
 * 03-selection-sort.c
 *
 * Demonstração da Ordenação por Seleção (Selection Sort):
 * - Função auxiliar modular de troca (swap) via ponteiros
 * - Rastreamento visual passo a passo da fronteira ordenada vs. não ordenada
 * - Contabilização estrita de comparações e trocas
 */

#include <stdio.h>
#include <stddef.h>

/* Troca de valores de duas variáveis via ponteiros */
static void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Imprime o arranjo destacando a fronteira da região ordenada */
static void imprime_rastreio(const int arr[], size_t n, size_t fronteira) {
    printf("  [");
    for (size_t i = 0; i < fronteira; i++) {
        printf("%2d ", arr[i]);
    }
    printf("| ");
    for (size_t i = fronteira; i < n; i++) {
        printf("%2d ", arr[i]);
    }
    printf("]\n");
}

/* Selection Sort modular instrumentado com contadores operacionais */
void selection_sort(int arr[], size_t n, size_t *out_comp, size_t *out_trocas) {
    size_t comp = 0;
    size_t trocas = 0;

    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;

        for (size_t j = i + 1; j < n; j++) {
            comp++;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            troca(&arr[i], &arr[min_idx]);
            trocas++;
        }

        printf("Passo %zu: ", i + 1);
        imprime_rastreio(arr, n, i + 1);
    }

    if (out_comp != NULL) *out_comp = comp;
    if (out_trocas != NULL) *out_trocas = trocas;
}

int main(void) {
    puts("=== 03: Selection Sort com Rastreamento de Fronteira ===");

    int dados[] = {64, 25, 12, 22, 11};
    const size_t n = sizeof(dados) / sizeof(dados[0]);

    printf("Arranjo inicial: ");
    imprime_rastreio(dados, n, 0);
    puts("");

    size_t comp = 0;
    size_t trocas = 0;
    selection_sort(dados, n, &comp, &trocas);

    puts("\nResultado final:");
    printf("Arranjo ordenado: ");
    imprime_rastreio(dados, n, n);
    printf("Metricas operacionais: %zu comparacoes, %zu trocas\n", comp, trocas);
    printf("Formula teorica n(n-1)/2: %zu comparacoes\n", n * (n - 1) / 2);

    return 0;
}

