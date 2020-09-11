#ifndef LEITURA_H
#define LEITURA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Grafo.h"

typedef struct euclidiano{
	int vertice;
	double x;
	double y;
	double z;
}euclidiano;

typedef struct geografico{
	int vertice;
	double x;
	double y;
}geografico;

void coletorDeDados(Grafo* gr, FILE *inp1,int tamanho,char *ewtipo,char *formato);

#endif
