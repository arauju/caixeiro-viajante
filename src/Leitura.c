#include <stdio.h>
#include <stdlib.h>
#include "../headers/Leitura.h"

void coletorDeDados(Grafo* gr, FILE *inp1,int tamanho, char* ewtipo,char *formato){
    int i,j,k;

    if(strcmp(ewtipo,"EUC_2D")==0){
        euclidiano *armazenador = (euclidiano*) malloc (tamanho * sizeof(euclidiano));

        for(i = 0 ; i < tamanho; i++)
            fscanf(inp1,"%d %lf %lf\n",&armazenador[i].vertice,&armazenador[i].x,&armazenador[i].y);

        for( i =0 ; i < tamanho ; i++){
            for (j = i ; j < tamanho ; j++){
                int xd= abs(armazenador[i].x - armazenador[j].x);
                int yd = abs(armazenador[i].y - armazenador[j].y);
                int dij = (nint ( sqrt( xd*xd + yd*yd) )) ;
                insereArestaMATRIZ(gr,i,j,dij,0);
            }
        }
      } else if(strcmp(ewtipo,"EUC_3D")==0){
          euclidiano *armazenador = (euclidiano*) malloc (tamanho * sizeof(euclidiano));

          for(i = 0 ; i < tamanho; i++)
              fscanf(inp1,"%d %lf %lf %lf\n",&armazenador[i].vertice,&armazenador[i].x,&armazenador[i].y,&armazenador[i].z);

          for( i = 0 ; i < tamanho ; i++){
              for (j = i ; j < tamanho ; j++){
                  int xd= abs(armazenador[i].x - armazenador[j].y);
                  int yd = abs(armazenador[i].y - armazenador[j].y);
                  int zd = abs(armazenador[i].z - armazenador[j].z);
                  int dij = nint( sqrt( xd*xd + yd*yd + zd*zd) );
                  insereArestaMATRIZ(gr,i,j,dij,0);
              }
          }
      } else if(strcmp(ewtipo,"GEO") == 0){
          float PI;
          int deg;
          float min;
          float q1,q2,q3;
          float dij;

          geografico *armazenador = (geografico*) malloc (tamanho * sizeof(geografico));

          for(i = 0 ; i < tamanho; i++){
              fscanf(inp1,"%d %lf %lf\n",&armazenador[i].vertice,&armazenador[i].x,&armazenador[i].y);
              PI = 3.141592;
              deg = nint(armazenador[i].x);
              min = armazenador[i].x - deg;
              armazenador[i].x = PI * (deg + 5.0 * min / 3.0 ) / 180.0;
              deg = nint(armazenador[i].y);
              min = armazenador[i].y - deg;
              armazenador[i].y = PI * (deg + 5.0 * min / 3.0 ) / 180.0;
          }

          for( i = 0 ; i < tamanho ; i++){
              for (j = i ; j < tamanho ; j++){
                  int RRR = 6378.388;
                  q1 = cos( armazenador[i].x - armazenador[j].x );
                  q2 = cos( armazenador[i].y- armazenador[j].y );
                  q3 = cos( armazenador[i].x + armazenador[j].x );
                  dij = (int) ( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ) + 1.0);
                  insereArestaMATRIZ(gr,i,j,dij,0);
              }
          }
      }
  }
