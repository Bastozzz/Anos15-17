//
//  main.c
//  TP2IIA
//
//  Created by Gabs on 22/12/2017.
//  Copyright © 2017 Gabriel Pinheiro nº 21260736. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"
#define TAM 100

#define DEFAULT_RUNS 10

int main(int argc, const char * argv[])
{
    char nomefich[TAM];
    int vert, num_iter, k, runs, custo, best_custo;
    int *sol, *best, i, j, valores[vert][vert];
    float mbf = 0.0;
    moedas dados;

    // Ler argumentos de entrada
    if(argc == 3)
    {
        runs = atoi(argv[2]);
        strcpy(nomefich, argv[1]);
    }
    else
    {
        // Se o número de execuções do processo não for colocado nos argumentos de entrada, define-o com um valor por defeito
        if (argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nomefich, argv[1]);
        }
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nomefich);
        }
    }

    // Se o numero de execuções do processo for menor ou igual a 0, termina o programa
    if(runs <= 0)
        return 0;

    dados = abreFich(nomefich);

    init_rand();



    return 0;
}
