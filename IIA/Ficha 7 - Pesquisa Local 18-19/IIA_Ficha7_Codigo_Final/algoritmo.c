#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

// Gera um vizinho � dist�ncia 1 (troca um v�rtice de cada grupo)
// Par�metros de entrada: Solu��o actual, a, Solu��o vizinha, b, N�mero de v�rtices, n
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    // Copia a solu��o atual para a solu��o vizinha
    for(i = 0; i < n; i++)
        b[i] = a[i];

	// Encontra aleatoriamente a posi��o de um v�rtice com valor 0
    do
        p1 = random_l_h(0, n-1);
    while(b[p1] != 0);

	// Encontra aleatoriamente a posi��o de um v�rtice com valor 1
    do
        p2 = random_l_h(0, n-1);
    while(b[p2] != 1);

	// Troca os valores dos v�rtices das posi��es encontradas
    b[p1] = 1;
    b[p2] = 0;
}

// Trepa colinas first-choice
// Par�metros de entrada: Solucao, sol, Matriz de adjacencias, mat, N�mero de v�rtices, vert, N�mero de itera��es, num_iter
// Par�metros de sa�da: Custo da melhor solu��o encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter)
{
    int *nova_sol, elementos, elementos_viz, i;
    int conta = 0;

	// Aloca espa�o em mem�ria para guardar a nova solu��o
	nova_sol = malloc(sizeof(int)*vert);

	// Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
    if (nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

	// Avalia solu��o inicial
    elementos = calcula_elementos(sol, vert);
    for(i = 0; i < num_iter; i++)
    {
		// Gera solu��o vizinha
        do {
		    gera_vizinho(sol, nova_sol, vert);
		    conta++;
        } while (valida_solucao(nova_sol, mat, vert) != 0 && conta < 100);

		// Avalia solu��o vizinha
		if(conta != 100)
            elementos_viz = calcula_elementos(nova_sol, vert);
        else
            elementos_viz = 0;

		// Fica com a solu��o vizinha se o custo diminuir (problema de minimiza��o) em rela��o � solu��o atual
        if (elementos_viz > elementos)
        {
			substitui(sol, nova_sol, vert);
			elementos = elementos_viz;
        }
    }
	// Liberta a mem�ria usada para guardar a nova solu��o
    free(nova_sol);

	// Devolve o custo da melhor solu��o encontrada
    return elementos;
}
