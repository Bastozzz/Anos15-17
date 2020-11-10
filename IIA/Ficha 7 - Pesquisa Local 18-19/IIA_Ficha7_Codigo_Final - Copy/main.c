#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"

#define DEFAULT_RUNS 10

int main(int argc, char *argv[])
{
    char    nome_fich[100];
    int     vert, num_iter, k, runs, custo, best_custo;
    int     *grafo, *sol, *best;
	float   mbf = 0.0;

    // L� os argumentos de entrada
	if (argc == 3)
	{
		runs = atoi(argv[2]);
		strcpy(nome_fich, argv[1]);
	}
	else
        // Se o n�mero de execu��es do processo n�o for colocado nos argumentos de entrada, define-o com um valor por defeito
        if (argc == 2)
        {
            runs = DEFAULT_RUNS;
            strcpy(nome_fich, argv[1]);
        }
        // Se o nome do ficheiro de informa��es n�o for colocado nos argumentos de entrada, pede-o novamente
        else
        {
            runs = DEFAULT_RUNS;
            printf("Nome do Ficheiro: ");
            gets(nome_fich);
        }
    // Se o n�mero de execu��es do processo for menor ou igual a 0, termina o programa
	if (runs <= 0)
		return 0;
    //Inicializa a gera��o dos n�meros aleat�rios
	init_rand();
    // Preenche matriz de adjacencias, o n�mero de v�rtices a usar e o n�mero de itera��es a fazer com o trepa colinas
    grafo = init_dados(nome_fich, &vert, &num_iter);
	// Aloca espa�o em mem�ria para guardar uma solu��o
	sol = malloc(sizeof(int)*vert);
	// Aloca espa�o em mem�ria para guardar a melhor solu��o
	best = malloc(sizeof(int)*vert);
	// Caso n�o consiga fazer as aloca��es, envia aviso e termina o programa
	if(sol == NULL || best == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	// Faz um ciclo com o n�mero de execu��es definidas
	for(k=0; k<runs; k++)
	{
		// Gera a solucao inicial
		gera_sol_inicial(sol, vert);
		// Mostra a solucao inicial
		escreve_sol(sol, vert);
		// Executa o algoritmo do trepa colinas
		custo = trepa_colinas_probabilistico(sol, grafo, vert, num_iter);
        // Ficha 7 - 4.4
//		custo = trepa_colinas_probabilistico(sol, grafo, vert, num_iter);
        // Ficha 7 - 4.5
//		custo = recristalizacao_simulada(sol, grafo, vert, num_iter);
		// Mostra a solu��o encontrada na repeti��o k e o seu custo
		printf("\nRepeticao %d:", k);
		escreve_sol(sol, vert);
		printf("Custo final: %2d\n", custo);
		// Acumula o custo das solu��es encontradas
		mbf += custo;
		// Guarda a melhor solu��o encontrada
		if(k==0 || best_custo > custo)
		{
			best_custo = custo;
			substitui(best, sol, vert);
		}
    }
	// Calcula e mostra a m�dia dos custos de todas as melhores solu��es encontradas
	printf("\n\nMBF: %f\n", mbf/k);
	// Mostra a melhor solu��o encontrada e o seu respectivo custo
	printf("\nMelhor solucao encontrada");
	escreve_sol(best, vert);
	printf("Custo final: %2d\n", best_custo);
	// Liberta a mem�ria usada
	free(grafo);
    free(sol);
	free(best);
    return 0;
}
