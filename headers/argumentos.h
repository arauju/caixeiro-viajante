#ifndef ARGUMENTOS_H
#define ARGUMENTOS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct args{
	char *i, *o, *k;
}arg;

arg leitura_parametro(int argc, char *argv[]);


#endif
