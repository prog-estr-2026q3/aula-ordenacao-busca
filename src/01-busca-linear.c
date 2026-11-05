/**
 * 01-busca-linear.c
 *
 * Demonstração dos métodos de busca linear em arranjos contíguos:
 * 1. Busca linear iterativa básica (arranjo desordenado)
 * 2. Busca linear com parada antecipada (arranjo ordenado)
 * 3. Busca linear recursiva (decomposição indutiva)
 * 4. Padrão de engenharia com parâmetro de saída (out-parameter)
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

/* 1. Busca linear iterativa padrão: retorno direto com ptrdiff_t */
ptrdiff_t busca_linear(const int arr[], size_t n, int chave) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == chave) {
            return (ptrdiff_t)i;
        }
    }
    return -1;
}

/* 2. Busca linear com parada precoce em arranjos ordenados */
ptrdiff_t busca_linear_ordenada(const int arr[], size_t n, int chave) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == chave) {
            return (ptrdiff_t)i;
        }
        if (arr[i] > chave) {
            break; /* Monotonicidade: nenhum elemento posterior será igual */
        }
    }
    return -1;
}

/* 3. Busca linear recursiva (decomposição indutiva) */
ptrdiff_t busca_linear_rec(const int arr[], size_t n, int chave) {
    if (n == 0) {
        return -1;
    }
    if (arr[0] == chave) {
        return 0;
    }
    ptrdiff_t sub = busca_linear_rec(arr + 1, n - 1, chave);
    return (sub != -1) ? (sub + 1) : -1;
}

/* 4. Variação de engenharia com parâmetro de saída e retorno booleano */
bool busca_linear_out(const int arr[], size_t n, int chave, size_t *pos) {
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == chave) {
            if (pos != NULL) {
                *pos = i;
            }
            return true;
        }
    }
    return false;
}

int main(void) {
    puts("=== 01: Busca Linear em Arranjos ===");

    /* Arranjo desordenado */
    const int dados[] = {42, 17, 88, 23, 95, 12, 64};
    const size_t n = sizeof(dados) / sizeof(dados[0]);

    printf("Arranjo: ");
    for (size_t i = 0; i < n; i++) {
        printf("%d ", dados[i]);
    }
    puts("\n");

    /* Teste da busca linear padrão */
    ptrdiff_t r1 = busca_linear(dados, n, 23);
    ptrdiff_t r2 = busca_linear(dados, n, 99);
    printf("[Linear Padrao] Chave 23: ");
    r1 != -1 ? printf("indice %td\n", r1) : puts("ausente");
    printf("[Linear Padrao] Chave 99: ");
    r2 != -1 ? printf("indice %td\n", r2) : puts("ausente");

    /* Teste com parada antecipada em arranjo ordenado */
    const int ord[] = {10, 20, 30, 40, 50, 60, 70};
    const size_t n_ord = sizeof(ord) / sizeof(ord[0]);
    ptrdiff_t ro = busca_linear_ordenada(ord, n_ord, 25);
    printf("[Parada Antecipada] Chave 25 em arranjo ordenado: ");
    ro != -1 ? printf("indice %td\n", ro) : puts("ausente (interrupcao precoce em 30)");

    /* Teste da versão recursiva */
    ptrdiff_t rec = busca_linear_rec(dados, n, 95);
    printf("[Recursiva] Chave 95: ");
    rec != -1 ? printf("indice %td\n", rec) : puts("ausente");

    /* Teste com padrão de parâmetro de saída (out-parameter) */
    size_t pos_encontrada;
    if (busca_linear_out(dados, n, 12, &pos_encontrada)) {
        printf("[Out-Parameter] Chave 12 localizada no indice %zu\n", pos_encontrada);
    } else {
        puts("[Out-Parameter] Chave 12 nao encontrada.");
    }

    return 0;
}

