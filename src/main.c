/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
* Ciência da Computação - UFSJ
* Algoritmos e Estrutura de Dados III
* Trabalho Prático 3I -  TSP
* Data : 10/11/16
* Criado por : João Augusto da Cruz & Juliana Araújo
_._._._._._._._._._._._._._._._._._._._._.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/argumentos.h"
#include "../headers/Grafo.h"
#include "../headers/Leitura.h"
#include "../headers/tempo.h"

int main(int argc, char *argv[]){

    //Variaveis para calcular tempo
    Tempo t;
    double tempoU,tempoS;
    struct timeval inicioU, inicioS, fimU, fimS;
    iniciaTempo(&t);

    int i, j, total_vert, total_impar = 0;
    float dist, menorDist;

    arg entrada = leitura_parametro(argc,argv);
    FILE *inp1 = fopen(entrada.i,"r");

    char buffer[50],formato[40],tipo[20],ewtipo[20];
    int tamanho;

    //leitura do cabeçalho
    while(1) {
        fscanf(inp1, "%s", buffer);
        if(strcmp(buffer,"COMMENT:") == 0)
            fgets(buffer, 50, inp1);
        else if(strcmp(buffer,"DIMENSION:") == 0){
            fscanf(inp1," %d", &tamanho);
        }
        else if(strcmp(buffer,"COMMENT") == 0){
            fscanf(inp1," : ");
            fgets(buffer, 50, inp1);
        }
        else if(strcmp(buffer,"NAME") == 0){
            fscanf(inp1," : ");
            fgets(buffer,50,inp1);
        }
        else if(strcmp(buffer,"NAME:") == 0){
            fgets(buffer,50,inp1);
        }
        else if(strcmp(buffer,"TYPE:") == 0){
            fgets(tipo,20,inp1);
        }
        else if(strcmp(buffer,"DIMENSION") == 0){
            fscanf(inp1," : %d", &tamanho);
        }
        else if(strcmp(buffer,"TYPE:") == 0){
            fgets(tipo,20,inp1);
        }
        else if(strcmp(buffer,"EDGE_WEIGHT_FORMAT:") == 0){
            fscanf(inp1," %s",formato);
        }
        else if(strcmp(buffer,"EDGE_WEIGHT_FORMAT") == 0){
            fscanf(inp1," : %s",formato);
        }
        else if(strcmp(buffer,"EDGE_WEIGHT_TYPE:") == 0){
            fscanf(inp1," %s",ewtipo);
        }
        else if(strcmp(buffer,"EDGE_WEIGHT_TYPE") == 0){
            fscanf(inp1," : %s",ewtipo);
        }
        else if(strcmp(buffer,"EDGE_WEIGHT_SECTION") == 0)
            break;
        else if(strcmp(buffer,"NODE_COORD_SECTION") == 0)
          break;
    }

    //cria o grafo
    Grafo* gr = cria_Grafo(tamanho,tamanho);

    coletorDeDados(gr,inp1,tamanho,ewtipo,formato);

    int *pai = (int*) malloc(tamanho * sizeof(int));
    int *impar = (int*) malloc(tamanho * sizeof(int));
    int *visitado = (int*) malloc(tamanho * sizeof(int));

    total_vert = tamanho;

    //Encontra a AGM
    Prim_GrafoMATRIZ(gr, 0, pai);

    //cria um novo gravo
    Grafo* T = cria_Grafo (total_vert, total_vert);

    //insere a AGM T no grafo
    for (i = 0; i < total_vert; i++)
        insereArestaMATRIZ (T, i, pai[i], gr->arestas[i][pai[i]], 0);

    //encontra impares
    total_impar = encontraImpares(T, impar, total_vert);

    //casamento de vertices impares
    Casamento (gr, T, total_impar, impar);

    //busca em profundidade com casamento mínimo
    buscaProfundidade_Grafo(T,gr, 0, visitado);

    libera_Grafo(gr);
    libera_Grafo(T);
    free(pai);
    free(impar);
    free(visitado);

    //finalização e impressão dos tempos
    finalizaTempo(&t, &tempoU, &tempoS);
    printf ("Tempo usuario: %f, tempo de sistema: %f", tempoU, tempoS);
    return 0;
}
