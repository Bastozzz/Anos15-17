//
//  Dados.c
//  TP2IIA
//
//  Created by Gabs on 22/12/2017.
//  Copyright © 2017 Gabriel Pinheiro nº 21260736. All rights reserved.
//

#include "Dados.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <locale.h>

moedas abreFich(char nomeFich[])
{

    FILE *f;
    moedas tmp;

    int i = 0;

    f = fopen(nomeFich, "rt");

    if(!f)
    {
        perror("Erro na abertura de ficheiro:");
        exit(1);
    }

    fscanf(f, "%d %f", &tmp.nmax, &tmp.objetivo);

    while(!feof(f))
    {
        tmp.moedas = realloc(tmp.moedas, sizeof(float) * (i+1));
        fscanf(f, "%f", &tmp.moedas[i]);
        i++;
    }

    tmp.vTam = i;

    return tmp;
}

void gera_sol_inicial(int *sol, int v)
{

}

int random_l_h(int min, int max)
{
    return min + rand() % (max);
}







