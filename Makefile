# Nome do executável
EXEC = teste

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -pthread

# Diretórios
SRC_DIRS = BIBLIOTECAS_SISTEMA BIBLIOTECAS_LISTAS
OBJ_DIR = obj

# Arquivos fonte
SRC = $(wildcard $(addsuffix /*.c, $(SRC_DIRS))) main.c

# Arquivos objeto
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Regra padrão
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

# Regra para criar arquivos objeto
$(OBJ_DIR)/%.o: %.c
    @mkdir -p $(dir $@)
    $(CC) $(CFLAGS) -c -o $@ $<

# Limpeza
clean:
    rm -rf $(OBJ_DIR) $(EXEC)