# Define o compilador
CC = gcc

# Define as flags de compilação:
# -Wall: ativa todos os avisos (warnings)
# -Wextra: ativa avisos adicionais
# -std=c11: usa o padrão C11
# -g: inclui informações de depuração para o GDB
# -o: especifica o nome do arquivo de saída
CFLAGS = -Wall -Wextra -std=c11 -g

# Define o nome do executável final
TARGET = sumplete

# Define todos os arquivos .c que compõem o projeto
SRCS = main.c funcoes.c

# Define todos os arquivos de cabeçalho .h
HDRS = funcoes.h cores.h

# Cria a lista de arquivos .o (objetos) a partir dos arquivos .c
OBJS = $(SRCS:.c=.o)

# Regra principal (all) para compilar o executável
all: $(TARGET)

# Regra para vincular os arquivos objeto e criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Regra para compilar cada arquivo .c em seu respectivo arquivo .o
# A dependência é tanto do arquivo .c quanto dos arquivos .h
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos gerados pela compilação
clean:
	rm -f $(OBJS) $(TARGET)