/**
 * 02-busca-binaria.c
 *
 * Demonstração dos métodos de busca binária em C:
 * 1. Implementação iterativa padrão com cálculo seguro do ponto médio
 * 2. Implementação recursiva indutiva
 * 3. Localização da primeira ocorrência em arranjos com chaves duplicadas
 * 4. Busca binária instrumentada com contagem de iterações/divisões
 * 5. Ponto exato de inserção ordenada (lower bound)
 */

#include <stdio.h>
#include <stddef.h>

/* 1. Busca binária iterativa imune a transbordamento aritmético */
ptrdiff_t busca_binaria(const int arr[], size_t n, int chave) {
    ptrdiff_t ini = 0;
    ptrdiff_t fim = (ptrdiff_t)n - 1;

    while (ini <= fim) {
        ptrdiff_t meio = ini + (fim - ini) / 2;

        if (arr[meio] == chave) {
            return meio;
        }
        if (arr[meio] < chave) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

/* 2. Busca binária recursiva com limites de intervalo */
static ptrdiff_t busca_bin_rec_interna(const int arr[], ptrdiff_t ini, ptrdiff_t fim, int chave) {
    if (ini > fim) {
        return -1;
    }
    ptrdiff_t meio = ini + (fim - ini) / 2;

    if (arr[meio] == chave) {
        return meio;
    }
    if (arr[meio] < chave) {
        return busca_bin_rec_interna(arr, meio + 1, fim, chave);
    }
    return busca_bin_rec_interna(arr, ini, meio - 1, chave);
}

ptrdiff_t busca_binaria_rec(const int arr[], size_t n, int chave) {
    if (n == 0) {
        return -1;
    }
    return busca_bin_rec_interna(arr, 0, (ptrdiff_t)n - 1, chave);
}

/* 3. Busca binária para primeira ocorrência em arranjos com duplicatas */
ptrdiff_t busca_binaria_primeira(const int arr[], size_t n, int chave) {
    ptrdiff_t ini = 0;
    ptrdiff_t fim = (ptrdiff_t)n - 1;
    ptrdiff_t resultado = -1;

    while (ini <= fim) {
        ptrdiff_t meio = ini + (fim - ini) / 2;

        if (arr[meio] == chave) {
            resultado = meio;  /* Candidato: continua investigando à esquerda */
            fim = meio - 1;
        } else if (arr[meio] < chave) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return resultado;
}

/* 4. Busca binária instrumentada com contador de passos */
ptrdiff_t busca_binaria_contando(const int arr[], size_t n, int chave, size_t *divisoes) {
    ptrdiff_t ini = 0;
    ptrdiff_t fim = (ptrdiff_t)n - 1;
    size_t passos = 0;

    while (ini <= fim) {
        passos++;
        ptrdiff_t meio = ini + (fim - ini) / 2;

        if (arr[meio] == chave) {
            if (divisoes != NULL) *divisoes = passos;
            return meio;
        }
        if (arr[meio] < chave) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    if (divisoes != NULL) *divisoes = passos;
    return -1;
}

/* 5. Lower bound: índice onde inserir a chave mantendo a ordenação */
ptrdiff_t lower_bound(const int arr[], size_t n, int chave) {
    ptrdiff_t ini = 0;
    ptrdiff_t fim = (ptrdiff_t)n;

    while (ini < fim) {
        ptrdiff_t meio = ini + (fim - ini) / 2;
        if (arr[meio] < chave) {
            ini = meio + 1;
        } else {
            fim = meio;
        }
    }
    return ini;
}

int main(void) {
    puts("=== 02: Busca Binaria em Arranjos Ordenados ===");

    const int dados[] = {12, 25, 38, 47, 56, 63, 79, 88, 91};
    const size_t n = sizeof(dados) / sizeof(dados[0]);

    printf("Arranjo ordenado (%zu elementos): ", n);
    for (size_t i = 0; i < n; i++) printf("%d ", dados[i]);
    puts("\n");

    /* Teste busca binária iterativa */
    ptrdiff_t p1 = busca_binaria(dados, n, 63);
    ptrdiff_t p2 = busca_binaria(dados, n, 50);
    printf("[Iterativa] Chave 63: ");
    p1 != -1 ? printf("indice %td\n", p1) : puts("ausente");
    printf("[Iterativa] Chave 50: ");
    p2 != -1 ? printf("indice %td\n", p2) : puts("ausente");

    /* Teste busca recursiva */
    ptrdiff_t pr = busca_binaria_rec(dados, n, 12);
    printf("[Recursiva] Chave 12: ");
    pr != -1 ? printf("indice %td\n", pr) : puts("ausente");

    /* Demonstração de convergência logarítmica com contagem de iterações */
    size_t divisoes = 0;
    ptrdiff_t pc = busca_binaria_contando(dados, n, 88, &divisoes);
    printf("[Contagem] Chave 88: localizada no indice %td com apenas %zu divisoes!\n", pc, divisoes);

    /* Teste de primeira ocorrência em arranjo com repetidos */
    const int repetidos[] = {10, 20, 20, 20, 30, 40, 40, 50};
    const size_t n_rep = sizeof(repetidos) / sizeof(repetidos[0]);
    printf("\nArranjo com duplicatas: ");
    for (size_t i = 0; i < n_rep; i++) printf("%d ", repetidos[i]);
    puts("");

    ptrdiff_t p_primeira = busca_binaria_primeira(repetidos, n_rep, 20);
    printf("[Primeira Ocorrencia] Chave 20: primeiro indice = %td\n", p_primeira);

    /* Teste de Lower Bound (ponto de inserção) */
    ptrdiff_t lb1 = lower_bound(repetidos, n_rep, 20);
    ptrdiff_t lb2 = lower_bound(repetidos, n_rep, 25);
    printf("[Lower Bound] Chave 20 deve ficar no indice: %td\n", lb1);
    printf("[Lower Bound] Chave 25 (ausente) deve ser inserida no indice: %td\n", lb2);

    return 0;
}

