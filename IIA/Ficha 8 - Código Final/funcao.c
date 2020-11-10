#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  100
#define PROBGERAVIZ     1.0

// Calcula a qualidade de uma solução
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}
	if (sum_weight > d.capacity)
	{
        // Solução inválida
		*v = 0;
		return 0;
	}
	else
	{
        // Solução válida
		*v = 1;
		return sum_profit;
	}
}

// Calcula a qualidade de uma solução com penalização
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual_penalizado(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
            // Obtem o melhor ro
            if (d.ro < (float)mat[i][1]/mat[i][0])
                d.ro = (float)mat[i][1]/mat[i][0];
		}
	}
	if (sum_weight > d.capacity)
	{
        // Solução inválida
		*v = 0;
		return sum_profit-(sum_weight-d.capacity)*d.ro; // Solucao com penalização
	}
	else
	{
        // Solução válida
		*v = 1;
		return sum_profit;
	}
}

// Calcula a qualidade de uma solução com reparação aleatória
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual_reparado1(int sol[], struct info d, int mat[][2], int *v)
{
	int     i;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}
	// Processo de reparacao
    while (sum_weight > d.capacity)
    {
        // escolhe um objeto aleatoriamente
        i = random_l_h(0, d.numGenes-1);
        // Se esse objeto estiver na mochila, retira-o e ajusta os somatórios do peso e lucro
        if (sol[i] == 1)
        {
            sol[i] = 0;
            sum_weight -= mat[i][0];
            sum_profit -= mat[i][1];
        }
    }
    *v = 1;
	return sum_profit;
}

// Calcula a qualidade de uma solução com reparação de acordo com uma heirística sofrega
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
float eval_individual_reparado2(int sol[], struct info d, int mat[][2], int *v)
{
	int     i, mv, pos;
	float   sum_weight, sum_profit;

	sum_weight = sum_profit = 0;
	// Percorre todos os objectos
	for (i=0; i < d.numGenes; i++)
	{
        // Verifica se o objecto i esta na mochila
		if (sol[i] == 1)
		{
            // Actualiza o peso total
			sum_weight += mat[i][0];
            // Actualiza o lucro total
			sum_profit += mat[i][1];
		}
	}
	// Processo de reparacao 2
    while (sum_weight > d.capacity)
    {
        pos = -1;
        for (i=0; i < d.numGenes; i++)
        {
            if (sol[i] == 1)
            {
                if  (pos == -1 || mv > mat[i][1])
                {
                    mv = mat[i][1];
                    pos = i;
                }
            }
        }
        sol[pos] = 0;
        sum_weight -= mat[pos][0];
        sum_profit -= mat[pos][1];
    }
    *v = 1;
	return sum_profit;
}

// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, int mat[][2])
{
	int i;

	for (i=0; i<d.popsize; i++)
		pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
        // Exercício 4.2(a)
//		pop[i].fitness = eval_individual_penalizado(pop[i].p, d, mat, &pop[i].valido);
        // Exercício 4.2(b)
//		pop[i].fitness = eval_individual_reparado1(pop[i].p, d, mat, &pop[i].valido);
        // Exercício 4.2(c)
//		pop[i].fitness = eval_individual_reparado2(pop[i].p, d, mat, &pop[i].valido);
}

void gera_vizinho(int sol[], int solViz[], int mat[][2], int nGenes)
{
    int i, menorCustoIn, maiorCustoOut, p1, p2;

    // Copia a solução para a solução vizinha
    for (i=0; i < nGenes; i++)
        solViz[i] = sol[i];
    if (rand_01() < PROBGERAVIZ)
    {
        // escolhe um objeto aleatoriamente
        i = random_l_h(0, nGenes-1);
        solViz[i] = !solViz[i];
    }
    else
    {
        menorCustoIn = MAX_OBJ;
        maiorCustoOut = 0;
        for (i=0; i < nGenes; i++)
        {
            if (sol[i] == 1 && menorCustoIn > mat[i][1])
            {
                menorCustoIn = mat[i][1];
                p1 = i;
            }
            if (sol[i] == 0 && maiorCustoOut < mat[i][1])
            {
                maiorCustoOut = mat[i][1];
                p2 = i;
            }
        }
        solViz[p1] = 0;
        solViz[p2] = 1;
    }
}

void trepa_colinas(pchrom pop, struct info d, int mat[][2])
{
    int     i, j;
    chrom   vizinho;

    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<GENERATIONS_TC; j++)
        {
            gera_vizinho(pop[i].p, vizinho.p, mat, d.numGenes);
            vizinho.fitness = eval_individual(vizinho.p, d, mat, &vizinho.valido);
            if (vizinho.fitness >= pop[i].fitness)
                pop[i] = vizinho;
        }
    }
}
