
# Variaveis
CC = gcc
CFLAGS = -Wall -g
OBJ = main.o RegistroDeHumor.o ListaDuplamenteEnc.o
EXEC = programa.exe

# Regra padrão (compilar e executar)
all: $(EXEC)
	cmd /c $(EXEC)
	$(MAKE) clean

# Regra para compilar o programa principal
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o programa.exe $(OBJ)

# Compilar main.c
main.o: main.c RegistroDeHumor.h ListaDuplamenteEnc.h
	$(CC) $(CFLAGS) -c main.c

# Compilar RegistroDeHumor.c
RegistroDeHumor.o: RegistroDeHumor.c RegistroDeHumor.h
	$(CC) $(CFLAGS) -c RegistroDeHumor.c

# Compilar ListaDuplamenteEnc.c
ListaDuplamenteEnc.o: ListaDuplamenteEnc.c ListaDuplamenteEnc.h RegistroDeHumor.h
	$(CC) $(CFLAGS) -c ListaDuplamenteEnc.c

# Limpeza dos arquivos objeto e executável
clean:
	cmd /c "del /Q *.o $(EXEC)"