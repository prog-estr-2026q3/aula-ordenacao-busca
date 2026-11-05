/**
 * 06-stdlib-qsort-bsearch.c
 *
 * Uso profissional das funções genéricas de <stdlib.h>:
 * - qsort: ordenação genérica com comparadores seguros contra transbordamento
 * - bsearch: busca binária genérica e cálculo do índice via aritmética de ponteiros
 * - Aplicação sobre tipos primitivos, cadeias de caracteres e estruturas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* Comparador defensivo para inteiros (evita falha de subtração com INT_MIN) */
static int compara_inteiros(const void *a, const void *b) {
    int va = *(const int *)a;
    int vb = *(const int *)b;

    if (va < vb) return -1;
    if (va > vb) return  1;
    return 0;
}

/* Comparador para arranjo de ponteiros de strings */
static int compara_strings(const void *a, const void *b) {
    const char *str_a = *(const char * const *)a;
    const char *str_b = *(const char * const *)b;
    return strcmp(str_a, str_b);
}

typedef struct {
    int ra;
    char nome[40];
    float nota;
} Aluno;

/* Comparador para Aluno por RA (para bsearch por RA) */
static int compara_aluno_por_ra(const void *a, const void *b) {
    const Aluno *aluno_a = (const Aluno *)a;
    const Aluno *aluno_b = (const Aluno *)b;

    if (aluno_a->ra < aluno_b->ra) return -1;
    if (aluno_a->ra > aluno_b->ra) return  1;
    return 0;
}

/* Comparador composto: nota decrescente, desempate por nome alfabético */
static int compara_aluno_composto(const void *a, const void *b) {
    const Aluno *aluno_a = (const Aluno *)a;
    const Aluno *aluno_b = (const Aluno *)b;

    if (aluno_a->nota > aluno_b->nota) return -1; /* Maior nota precede */
    if (aluno_a->nota < aluno_b->nota) return  1;
    return strcmp(aluno_a->nome, aluno_b->nome);
}

int main(void) {
    puts("=== 06: Uso Profissional de qsort e bsearch (<stdlib.h>) ===");

    /* 1. Ordenação e Busca Binária em Inteiros */
    puts("--- 1. Inteiros ---");
    int numeros[] = {89, 12, 45, 23, 78, 34};
    size_t n_num = sizeof(numeros) / sizeof(numeros[0]);

    qsort(numeros, n_num, sizeof(numeros[0]), compara_inteiros);
    printf("Numeros ordenados via qsort: ");
    for (size_t i = 0; i < n_num; i++) printf("%d ", numeros[i]);
    puts("");

    int chave_busca = 45;
    const int *ptr_num = bsearch(&chave_busca, numeros, n_num, sizeof(numeros[0]), compara_inteiros);
    if (ptr_num != NULL) {
        ptrdiff_t idx = ptr_num - numeros; /* Aritmética de ponteiros */
        printf("bsearch: valor %d encontrado no indice %td (endereco %p)\n\n", chave_busca, idx, (const void *)ptr_num);
    }

    /* 2. Ordenação de Strings */
    puts("--- 2. Cadeias de Caracteres ---");
    const char *linguagens[] = {"Python", "C", "Rust", "Java", "Go", "Haskell"};
    size_t n_ling = sizeof(linguagens) / sizeof(linguagens[0]);

    qsort(linguagens, n_ling, sizeof(linguagens[0]), compara_strings);
    printf("Linguagens em ordem alfabetica: ");
    for (size_t i = 0; i < n_ling; i++) printf("%s ", linguagens[i]);
    puts("\n");

    /* 3. Ordenação e Consulta de Registros (struct Aluno) */
    puts("--- 3. Colecao de Estruturas (struct Aluno) ---");
    Aluno turma[] = {
        {139, "Mariana", 8.0f},
        {124, "Carlos",  9.5f},
        {113, "Beatriz", 7.0f},
        {123, "Ana",     9.5f}
    };
    size_t n_alunos = sizeof(turma) / sizeof(turma[0]);

    /* Ordena primeiramente por RA para permitir bsearch */
    qsort(turma, n_alunos, sizeof(turma[0]), compara_aluno_por_ra);
    puts("Turma ordenada por RA:");
    for (size_t i = 0; i < n_alunos; i++) {
        printf("  RA: %d | Nome: %-10s | Nota: %4.1f\n", turma[i].ra, turma[i].nome, turma[i].nota);
    }

    /* Consulta por RA usando bsearch */
    Aluno chave_aluno = {.ra = 124};
    const Aluno *res_aluno = bsearch(&chave_aluno, turma, n_alunos, sizeof(turma[0]), compara_aluno_por_ra);
    if (res_aluno != NULL) {
        ptrdiff_t idx = res_aluno - turma;
        printf("bsearch localizou discente RA 124 no indice %td: %s (Nota: %.1f)\n\n",
               idx, res_aluno->nome, res_aluno->nota);
    }

    /* Reordena por critério multicritério: Nota decrescente com desempate por Nome */
    qsort(turma, n_alunos, sizeof(turma[0]), compara_aluno_composto);
    puts("Turma classificada por Nota (desempate por Nome alfabético):");
    for (size_t i = 0; i < n_alunos; i++) {
        printf("  %zu. Nome: %-10s | Nota: %4.1f | RA: %d\n", i + 1, turma[i].nome, turma[i].nota, turma[i].ra);
    }

    return 0;
}

