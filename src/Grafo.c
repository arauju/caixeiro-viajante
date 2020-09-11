#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/Grafo.h"
Grafo* cria_Grafo(int nro_vertices, int grau_max){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nro_vertices = nro_vertices;
        gr->grau_max = grau_max;
        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->arestas = (int**) malloc(nro_vertices * sizeof(int*));
        for(i = 0; i < nro_vertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));
    }
    return gr;
}

void libera_Grafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i = 0; i < gr->nro_vertices; i++)
        free(gr->arestas[i]);
        free(gr->arestas);
        free(gr->grau);
        free(gr);
    }
}

int insereArestaMATRIZ(Grafo* gr, int orig, int dest, float peso, int dir){
    if(gr == NULL) //verifica se o grafo é valido
        return 0;
    if(orig < 0 || orig >= gr->nro_vertices) //verifica se origem e destino sao validos
        return 0;
    if(dest < 0 || dest >= gr->nro_vertices)
        return 0;

    gr->arestas[orig][dest] = peso; //adiciona a aresta

    //chama a função novamente, por não ser direcionado
    if (dir == 0)
        insereArestaMATRIZ(gr, dest, orig, peso, 1);
    return 1;
}

void imprime_GrafoMATRIZ(Grafo *gr){
    int i, j;
    if(gr == NULL)
        return;
    printf("    ");
    for (i = 0; i < gr->nro_vertices; i++){
        printf ("%d ", i);
        if (i <= 9)
            printf(" ");
    }
    printf ("\n");
    for(i = 0; i < gr->nro_vertices; i++){
        if (i <= 9)
            printf(" ");
        printf("%d ", i);
        for(j = 0; j < gr->nro_vertices; j++){
            if (gr->arestas[i][j] <= 9)
                printf(" ");
            printf("%d ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}

void Prim_GrafoMATRIZ(Grafo *gr, int orig, int *pai){
    int i, j, dest, primeiro, NV = gr->nro_vertices;
    double menorPeso;
    for (i = 0; i < NV; i++)
        pai[i] = -1; // sem pai
    pai[orig] = orig;
    while (1){
        primeiro = 1;
        //percorre todos os vertices
        for (i = 0; i < NV; i++){
            //achou vertices já visitados
            if (pai[i] != -1){
              //percorre os vizinhos do vertice visitados
              for (j = 0; j < NV; j++){
                  //procurar menor peso
                  if (pai[j] == -1 && gr->arestas[i][j] != 0){
                      if (primeiro){ //procura aresta de menor peso
                          menorPeso = gr->arestas[i][j];
                          orig = i;
                          dest = j;
                          primeiro = 0;
                          } else {
                          if (menorPeso > gr->arestas[i][j]){
                              menorPeso = gr->arestas[i][j];
                              orig = i;
                              dest = j;
                            }
                        }
                    }
                }
            }
        }
        if (primeiro == 1)
            break;
        pai[dest] = orig;
    }
}

int encontraImpares (Grafo *T, int *impar, int total_vert){
    int total_impar = 0, i, j, k;
    for (i = 0; i < total_vert; i++){
        k = 0;
        for (j = 0; j < total_vert; j++){
            if (T->arestas[i][j] != 0.0){
                k++;
            }
        }
        if (k%2 != 0){
            impar[total_impar] = i;
            total_impar++;
        }
    }
    return total_impar;
}

void Casamento (Grafo *gr, Grafo *T, int total_impar, int *impar){
    int i, j, guardaJ, menorDist, dist;
    for (i = 0; i < total_impar - 1; i++){
        while (impar[i] < 0)
            i++;
        j = i + 1;
        while (impar[j] < 0)
            j++;
        guardaJ = j;
        if (i < total_impar && j < total_impar)
            menorDist = gr->arestas[impar[i]][impar[j]];
        for (j = i + 1; j < total_impar - 1; j++){
            if (impar[j] >= 0){
                dist = gr->arestas[impar[i]][impar[j]];
                if (dist < menorDist){
                    menorDist = dist;
                    guardaJ = j;
                }
            }
        }
        if (i < total_impar && guardaJ < total_impar){
            insereArestaMATRIZ (T, impar[i], impar[guardaJ], gr->arestas[impar[i]][impar[guardaJ]], 0);
            impar[guardaJ] = -1;
        }
    }
}

void buscaProfundidade(Grafo *T, Grafo *gr, int ini, int *visitado, float peso, float *distTotal, int *cont, int *retorno, int *guardaDest, int *guardaIni, int *curtoc){
    int i, contMais;
    visitado[ini] = *cont;
    if (*curtoc == 0){
        *distTotal += peso;
    }
    *curtoc = 0;
    for(i = 0; i < T->nro_vertices; i++){
        if(visitado[i] == 0 && T->arestas[ini][i] != 0){
          *guardaIni = i;

        //curto circuito
        if (*guardaDest != -1){
            *distTotal += gr->arestas[*guardaIni][*guardaDest];
            *guardaDest = -1;
            *retorno = -1;
            *curtoc = 1;
        }
        contMais = *cont+1;
        buscaProfundidade(T, gr, i, visitado, T->arestas[ini][i], distTotal, &contMais, retorno, guardaDest, guardaIni, curtoc);
        *cont = contMais;
        *retorno = *retorno + 1;
        if (*retorno == 0)
            *guardaDest = i;
        }
    }
}

void buscaProfundidade_Grafo(Grafo *T, Grafo *gr, int ini, int *visitado){
    int i, cont = 1, retorno = -1, guardaDest = -1, guardaIni = -1, ultVisitadoV = 0, ultVisitadoP, curtoc = 0;
    float distTotal = 0, peso = 0;
    for(i = 0; i < T->nro_vertices; i++)
        visitado[i] = 0;
    buscaProfundidade(T, gr, ini, visitado, peso, &distTotal, &cont, &retorno, &guardaDest, &guardaIni, &curtoc);

    for(i = 0; i < T->nro_vertices; i++){
        if (visitado[i] > ultVisitadoP){
            ultVisitadoV = i;
            ultVisitadoP = visitado[i];
        }
    }
    distTotal += gr->arestas[ini][ultVisitadoV];
    printf ("Distancia total percorrida: %.2f\n", distTotal);
}

 int nint(double numero){
    int inteiro_int = (long double) numero;
    long double inteiro = (int) inteiro_int;
    if(numero - inteiro > 0.5){
        return inteiro +1;
    }
    return inteiro;
}
