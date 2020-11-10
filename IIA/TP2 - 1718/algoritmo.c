//
//  algoritmo.c
//  TP2IIA
//
//  Created by Gabs on 12/01/2018.
//  Copyright © 2018 Gabriel Pinheiro nº 21260736. All rights reserved.
//
#include "algoritmo.h"

int trepa_colinas(int *sol,moedas dados,int vert,int num_iter)
{

    int *nova_sol, custo, custo_viz, i;

    // Aloca espaco em memoria para guardar a nova solucao
    nova_sol = malloc(sizeof(int)*vert);

    // Caso n„o consiga fazer a alocacao, envia aviso e termina o programa
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    // Liberta a memoria usada para guardar a nova solucao
    free(nova_sol);

    // Devolve o custo da melhor solcao encontrada
    return custo;
}

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
