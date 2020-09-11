# Makefile


SH = bash
CFLAGS = -g
LDFLAGS = -lm 
CC = gcc

all: main 

main: main.o Grafo.o Leitura.o argumentos.o tempo.o 
	$(CC) $(LDFLAGS) $^ -o tp3 -lm
main.o: ./src/main.c ./headers/Grafo.h ./headers/Leitura.h ./headers/argumentos.h ./headers/tempo.h
	$(CC) -c $(CFLAGS) $< -o $@

Grafo.o: ./src/Grafo.c ./headers/argumentos.h ./headers/Grafo.h ./headers/tempo.h
	$(CC) -c $(CFLAGS) $< -o $@

Leitura.o: ./src/Leitura.c ./headers/argumentos.h ./headers/Leitura.h ./headers/tempo.h
	$(CC) -c $(CFLAGS) $< -o $@

argumentos.o: ./src/argumentos.c ./headers/argumentos.h ./headers/tempo.h
	$(CC) -c $(CFLAGS) $< -o $@

tempo.o: ./src/tempo.c ./headers/tempo.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean lint test

clean:
	rm -rf *.o
	rm -rf tp3 

lint:
	for f in *.c; do echo $$f; splint -standard $$f; done;
