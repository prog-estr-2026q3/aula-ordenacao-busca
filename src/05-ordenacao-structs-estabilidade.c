/**
 * 05-ordenacao-structs-estabilidade.c
 *
 * Demonstração prática do impacto da estabilidade na ordenação de registros:
 * - Comportamento com struct Aluno { int ra; char nome[40]; float nota; }
 * - Comparação empírica: Selection Sort (instável) vs. Insertion Sort (estável)
 * - Ordenação multicritério direta (nota decrescente com desempate por nome)
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    int ra;
    char nome[40];
    float nota;
} Aluno;

/* Imprime a tabela de alunos formatada */
static void imprime_turma(const char *titulo, const Aluno arr[], size_t n) {
    printf("%s\n", titulo);
    puts("  +-----+------------+------+");
    puts("  | RA  | Nome       | Nota |");
    puts("  +-----+------------+------+");
    for (size_t i = 0; i < n; i++) {
        printf("  | %-3d | %-10s | %4.1f |\n", arr[i].ra, arr[i].nome, arr[i].nota);
    }
    puts("  +-----+------------+------+\n");
}

/* Troca de registros Aluno */
static void troca_aluno(Aluno *a, Aluno *b) {
    Aluno temp = *a;
    *a = *b;
    *b = temp;
}

/* Selection Sort por nota (Instável: saltos a longa distância invertem empatados) */
void selection_sort_por_nota(Aluno arr[], size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[j].nota < arr[min_idx].nota) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            troca_aluno(&arr[i], &arr[min_idx]);
        }
    }
}

/* Insertion Sort por nota (Estável: preserva a ordem relativa dos empatados) */
void insertion_sort_por_nota(Aluno arr[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        Aluno chave = arr[i];
        ptrdiff_t j = (ptrdiff_t)i - 1;

        /* Desloca estritamente se arr[j].nota > chave.nota (empates não são deslocados) */
        while (j >= 0 && arr[j].nota > chave.nota) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

/* Critério composto: nota decrescente com desempate alfabético por nome */
static int precede_multicriterio(const Aluno *a, const Aluno *b) {
    if (a->nota > b->nota) return 1; /* Maior nota vem primeiro */
    if (a->nota < b->nota) return 0;
    return strcmp(a->nome, b->nome) < 0; /* Desempate alfabético */
}

void insertion_sort_multicriterio(Aluno arr[], size_t n) {
    for (size_t i = 1; i < n; i++) {
        Aluno chave = arr[i];
        ptrdiff_t j = (ptrdiff_t)i - 1;

        while (j >= 0 && !precede_multicriterio(&arr[j], &chave)) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

int main(void) {
    puts("=== 05: Estabilidade na Ordenacao de Estruturas ===");

    /* Dados iniciais (idênticos à Tabela 9.1 das notas de aula) */
    const Aluno turma_original[4] = {
        {139, "Mariana", 8.0f},
        {124, "Carlos",  9.5f},
        {113, "Beatriz", 7.0f},
        {123, "Ana",     9.5f}
    };
    const size_t n = 4;

    imprime_turma("(a) Entrada original (desordenada)", turma_original, n);

    /* Pré-ordenação por RA: Ana (123) precede Carlos (124) */
    Aluno ordenado_por_ra[4];
    memcpy(ordenado_por_ra, turma_original, sizeof(turma_original));
    /* Ordenando manualmente por RA para ilustrar o estado prévio */
    for (size_t i = 1; i < n; i++) {
        Aluno chave = ordenado_por_ra[i];
        ptrdiff_t j = (ptrdiff_t)i - 1;
        while (j >= 0 && ordenado_por_ra[j].ra > chave.ra) {
            ordenado_por_ra[j + 1] = ordenado_por_ra[j];
            j--;
        }
        ordenado_por_ra[j + 1] = chave;
    }
    imprime_turma("(b) Previamente ordenado por RA (123 Ana antes de 124 Carlos)", ordenado_por_ra, n);

    /* Experimento 1: Reordenar por nota com Selection Sort (Instável) */
    Aluno teste_selection[4];
    memcpy(teste_selection, ordenado_por_ra, sizeof(ordenado_por_ra));
    selection_sort_por_nota(teste_selection, n);
    imprime_turma("(c) Apos Selection Sort por Nota [NAO ESTAVEL! Note RA 124 antes de 123]", teste_selection, n);

    /* Experimento 2: Reordenar por nota com Insertion Sort (Estável) */
    Aluno teste_insertion[4];
    memcpy(teste_insertion, ordenado_por_ra, sizeof(ordenado_por_ra));
    insertion_sort_por_nota(teste_insertion, n);
    imprime_turma("(d) Apos Insertion Sort por Nota [ESTAVEL! RA 123 preservado antes de 124]", teste_insertion, n);

    /* Experimento 3: Ordenação multicritério direta */
    Aluno teste_multi[4];
    memcpy(teste_multi, turma_original, sizeof(turma_original));
    insertion_sort_multicriterio(teste_multi, n);
    imprime_turma("(e) Ordenacao multicriterio (Nota decrescente, desempate por nome alfabético)", teste_multi, n);

    return 0;
}

