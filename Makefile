# ==========================================
# Makefile para libdimas (Static Library)
# ==========================================

# 1. Variáveis de Compilação
CC = gcc
CFLAGS = -I./include -Wall -Wextra -g

# Comando para criar a biblioteca estática (Archiver)
AR = ar
ARFLAGS = rcs

# 2. Estrutura de Diretórios
SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
LIB_DIR = lib

# 3. Arquivos Finais
# O executável de teste
TARGET_APP = $(BIN_DIR)/app_teste
# A nossa biblioteca estática final
TARGET_LIB = $(LIB_DIR)/libdimas.a

# ==========================================
# Regras de Construção
# ==========================================

# Regra padrão: Cria diretórios, a lib e depois o app de teste
all: directories $(TARGET_LIB) $(TARGET_APP)

# ------------------------------------------
# 1. Criação da Biblioteca Estática (.a)
# ------------------------------------------
$(TARGET_LIB): $(OBJ_DIR)/libdimas.o
	@echo "Empacotando a biblioteca estática $(TARGET_LIB)..."
	$(AR) $(ARFLAGS) $@ $^
# Explicação: 'ar' cria o arquivo. 'rcs' significa:
# r = replace (substitui arquivos antigos), c = create (cria se não existir), s = index (cria índice para acesso rápido)

# ------------------------------------------
# 2. Criação do Executável (Linkando com a Lib)
# ------------------------------------------
$(TARGET_APP): $(OBJ_DIR)/main.o $(TARGET_LIB)
	@echo "Linkando o app com a biblioteca..."
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR) -ldimas -o $@
# Explicação das flags cruciais:
# -L$(LIB_DIR) -> "GCC, procure bibliotecas na pasta 'lib'"
# -ldimas      -> "GCC, use o arquivo libdimas.a (ele adiciona 'lib' e '.a' sozinho)"

# ------------------------------------------
# 3. Compilação dos Objetos (.o)
# ------------------------------------------
$(OBJ_DIR)/main.o: $(TEST_DIR)/main.c $(INC_DIR)/libdimas.h
	@echo "Compilando main.c..."
	$(CC) $(CFLAGS) -c $(TEST_DIR)/main.c -o $@

$(OBJ_DIR)/libdimas.o: $(SRC_DIR)/libdimas.c $(INC_DIR)/libdimas.h
	@echo "Compilando libdimas.c..."
	$(CC) $(CFLAGS) -c $(SRC_DIR)/libdimas.c -o $@

# ------------------------------------------
# Utilitários
# ------------------------------------------
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(LIB_DIR)

clean:
	@echo "Limpando tudo..."
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR)

.PHONY: all clean directories