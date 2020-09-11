#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definicao do tipo Grafo
typedef struct grafo{
    int nro_vertices;
    int grau_max;
    int** arestas;
    int* grau;
}Grafo;

Grafo* cria_Grafo(int nro_vertices, int grau_max);
void libera_Grafo(Grafo* gr);
void imprime_GrafoMATRIZ(Grafo *gr);
int insereArestaMATRIZ(Grafo* gr, int orig, int dest, float peso, int dir);
void buscaProfundidade(Grafo *T, Grafo *gr, int ini, int *visitado, float peso, float *distTotal, int *cont, int *retorno, int *guardaDest, int *guardaIni, int *curtoc);
void buscaProfundidade_Grafo(Grafo *T, Grafo *gr, int ini, int *visitado);
void Prim_GrafoMATRIZ(Grafo *gr, int orig, int *pai);
int encontraImpares (Grafo *T, int *impar, int total_vert);
void Casamento (Grafo *gr, Grafo *T, int total_impar, int *impar);
int nint (double numero);

#endif
