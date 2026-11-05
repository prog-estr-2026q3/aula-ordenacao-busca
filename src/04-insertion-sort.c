/**
 * 04-insertion-sort.c
 *
 * Demonstração da Ordenação por Inserção (Insertion Sort):
 * - Mecânica de deslocamento de elementos à direita para abertura de vaga
 * - Demonstração da adaptabilidade: melhor caso (já ordenado) vs. pior caso (inverso)
 * - Uso seguro de ptrdiff_t para evitar underflow no índice de controle j
 */

#include <stdio.h>
#include <stddef.h>

/* Imprime o arranjo formatado */
static void imprime_arranjo(const int arr[], size_t n) {
    printf("[");
    for (size_t i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i + 1 < n) ? ", " : "");
    }
    printf("]\n");
}

/* Insertion Sort com rastreamento de comparações e deslocamentos */
void insertion_sort(int arr[], size_t n, size_t *out_comp, size_t *out_desloc) {
    if (n < 2) return;

    size_t comp = 0;
    size_t desloc = 0;

    for (size_t i = 1; i < n; i++) {
        int chave = arr[i];
        ptrdiff_t j = (ptrdiff_t)i - 1;

        while (j >= 0) {
            comp++;
            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                desloc++;
                j--;
            } else {
                break; /* Posição correta encontrada */
            }
        }
        arr[j + 1] = chave;
    }

    if (out_comp != NULL) *out_comp = comp;
    if (out_desloc != NULL) *out_desloc = desloc;
}

static void testa_caso(const char *descricao, int arr[], size_t n) {
    printf("--- %s ---\n", descricao);
    printf("Antes: ");
    imprime_arranjo(arr, n);

    size_t comp = 0, desloc = 0;
    insertion_sort(arr, n, &comp, &desloc);

    printf("Depois: ");
    imprime_arranjo(arr, n);
    printf("Resultado: %zu comparacoes, %zu deslocamentos\n\n", comp, desloc);
}

int main(void) {
    puts("=== 04: Insertion Sort e Adaptabilidade ===\n");

    /* Caso 1: Entrada aleatória comum */
    int caso_comum[] = {5, 2, 4, 6, 1, 3};
    testa_caso("Caso Medio (Aleatorio)", caso_comum, sizeof(caso_comum) / sizeof(caso_comum[0]));

    /* Caso 2: Melhor caso (Já ordenado) -> Custo Linear estrito O(n) */
    int ja_ordenado[] = {1, 2, 3, 4, 5, 6};
    testa_caso("Melhor Caso (Ja ordenado - custo linear n-1)", ja_ordenado, sizeof(ja_ordenado) / sizeof(ja_ordenado[0]));

    /* Caso 3: Pior caso (Inversamente ordenado) -> n(n-1)/2 deslocamentos */
    int inverso[] = {6, 5, 4, 3, 2, 1};
    testa_caso("Pior Caso (Inversamente ordenado)", inverso, sizeof(inverso) / sizeof(inverso[0]));

    return 0;
}

