CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
ASAN_FLAGS = -fsanitize=address,undefined -g
DEBUG_FLAGS = -g
LDLIBS = -lm
SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/01-busca-linear.c \
       $(SRC_DIR)/02-busca-binaria.c \
       $(SRC_DIR)/03-selection-sort.c \
       $(SRC_DIR)/04-insertion-sort.c \
       $(SRC_DIR)/05-ordenacao-structs-estabilidade.c \
       $(SRC_DIR)/06-stdlib-qsort-bsearch.c \
       $(SRC_DIR)/07-comparativo-operacional.c

BINS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SRCS))
ASAN_BINS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%_asan,$(SRCS))

all: $(BINS)

asan: $(ASAN_BINS)

$(BUILD_DIR)/%_asan: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ASAN_FLAGS) $< -o $@ $(LDLIBS)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

$(BUILD_DIR):
	mkdir -m 755 -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

test: all
	@echo "=== Executando suite de testes de ordenacao e busca ==="
	@for bin in 01-busca-linear 02-busca-binaria 03-selection-sort \
	           04-insertion-sort 05-ordenacao-structs-estabilidade \
	           06-stdlib-qsort-bsearch 07-comparativo-operacional; do \
		echo "--- Executando $$bin ---"; \
		./$(BUILD_DIR)/$$bin; \
		echo ""; \
	done
	@echo "=== Todos os testes foram executados com sucesso! ==="

busca-linear: $(BUILD_DIR)/01-busca-linear
busca-binaria: $(BUILD_DIR)/02-busca-binaria
selection-sort: $(BUILD_DIR)/03-selection-sort
insertion-sort: $(BUILD_DIR)/04-insertion-sort
estabilidade: $(BUILD_DIR)/05-ordenacao-structs-estabilidade
stdlib: $(BUILD_DIR)/06-stdlib-qsort-bsearch
comparativo: $(BUILD_DIR)/07-comparativo-operacional

.PHONY: all asan clean test busca-linear busca-binaria selection-sort insertion-sort estabilidade stdlib comparativo
