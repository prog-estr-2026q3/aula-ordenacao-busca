# Exemplos de código - ordenação e busca

Este diretório contém os códigos de exemplo, estudos de caso e análises comparativas apresentados no capítulo 09 (ordenação e busca) das notas de aula da disciplina de programação estruturada (MCTA028-15).

---

## Estrutura do projeto

```
.
├── Makefile
├── README.md
├── .gitignore
├── .devcontainer/   # Configuração de ambiente para dev container / GitHub Codespaces
├── src/             # Códigos-fonte (.c) dos exemplos e estudos comparativos
└── build/           # Executáveis compilados (ignorado pelo git)
```

---

## Como compilar e executar

### 1. Compilar todos os programas

Para compilar todos os programas da coleção:

```bash
make
```

Os binários correspondentes serão gerados no diretório `build/`.

### 2. Executar a suíte de testes rápidos

Para compilar e disparar a execução de todos os programas conceituais e comparativos em sequência:

```bash
make test
```

### 3. Compilação com AddressSanitizer (ASan)

Para compilar todas as fontes instrumentadas com sanitizadores de memória e de comportamento indefinido (`-fsanitize=address,undefined -g`):

```bash
make asan
```

Os executáveis instrumentados receberão o sufixo `_asan` em `build/` (por exemplo, `build/02-busca-binaria_asan`).

### 4. Execução individual de um programa

Após compilar com `make`, você pode executar qualquer binário individualmente a partir do diretório raiz do projeto:

```bash
./build/01-busca-linear
./build/02-busca-binaria
./build/03-selection-sort
./build/04-insertion-sort
./build/05-ordenacao-structs-estabilidade
./build/06-stdlib-qsort-bsearch
./build/07-comparativo-operacional
```

Também é possível compilar alvos específicos diretamente via atalhos do Makefile:

```bash
make busca-linear
make busca-binaria
make selection-sort
make insertion-sort
make estabilidade
make stdlib
make comparativo
```

### 5. Limpar os arquivos compilados

Para remover o diretório `build/` e todos os executáveis gerados:

```bash
make clean
```

---

## Descrição dos exemplos em `src/`

- `01-busca-linear.c`: Implementação de busca linear em arranjos contíguos: abordagem iterativa padrão, busca com parada antecipada explorando monotonicidade em dados ordenados, formulação recursiva indutiva e variação de engenharia com parâmetro de saída (*out-parameter*) e retorno booleano.
- `02-busca-binaria.c`: Implementação de busca binária em tempo $O(\log n)$: versão iterativa imune a transbordamento aritmético no ponto médio (`ini + (fim - ini) / 2`), versão recursiva com limites de intervalo, localização determinística da primeira ocorrência em arranjos com chaves duplicadas, rastreamento instrumentado de divisões e cálculo do ponto exato de inserção ordenada (*lower bound*).
- `03-selection-sort.c`: Algoritmo de ordenação por seleção (*Selection Sort*): função modular de troca (`troca`), rastreamento visual da fronteira entre a subfaixa ordenada e a não ordenada, invariante de laço e contabilização estrita de comparações e trocas (sempre $\Theta(n^2)$ comparações e no máximo $n - 1$ trocas).
- `04-insertion-sort.c`: Algoritmo de ordenação por inserção (*Insertion Sort*): mecânica de deslocamento contíguo à direita para abertura de vaga, tipagem defensiva com `ptrdiff_t` para controle seguro de subfluxo (*underflow*) e demonstração da adaptabilidade (melhor caso linear $O(n)$ em dados já ordenados vs. pior caso quadrático $O(n^2)$ em ordem reversa).
- `05-ordenacao-structs-estabilidade.c`: Análise prática e conceitual do impacto da estabilidade na ordenação de registros compostos (`struct Aluno` com RA, nome e nota): comparação direta demonstrando a instabilidade intrínseca do Selection Sort (que inverte a ordem relativa de chaves idênticas em trocas distantes) contra a estabilidade natural do Insertion Sort, além de ordenação multicritério direta com critério de desempate léxico.
- `06-stdlib-qsort-bsearch.c`: Utilização idiomática e profissional das funções genéricas de busca e ordenação da biblioteca padrão de C (`<stdlib.h>`): ordenação rápida via `qsort` com comparadores defensivos à prova de transbordamento (`va < vb ? -1 : va > vb`), busca binária genérica com `bsearch`, cálculo de índice por aritmética de ponteiros e manipulação de tipos primitivos, cadeias de caracteres e estruturas.
- `07-comparativo-operacional.c`: Estudo comparativo de desempenho e métricas empíricas entre Selection Sort e Insertion Sort submetidos a arranjos de tamanho $N = 1000$ sob três perfis de dados: perfeitamente ordenado, inversamente ordenado e aleatório; contabilização precisa de comparações de chaves e escritas em memória, evidenciando as vantagens adaptativas do Insertion Sort e a economia estrita de escritas do Selection Sort.

---

## Utilização com Docker / Dev Container

Este repositório inclui suporte completo para desenvolvimento em contêineres:

- **VS Code com extensão Dev Containers:** abra esta pasta e selecione **"Reopen in Container"** quando solicitado. O ambiente Alpine Linux com GCC, Make e Musl-Dev será configurado automaticamente.
- **GitHub Codespaces:** crie um ambiente na nuvem com um clique diretamente a partir da interface do repositório no GitHub para compilar, executar e testar os códigos no navegador.
