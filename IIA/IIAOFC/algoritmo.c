#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
	int i, x1, x2;

	// Realiza popsize torneios
	for (i=0; i<d.moedasQuant;i++)
	{
		x1 = random_l_h(0, d.moedasQuant-1);
		do
			x2 = random_l_h(0, d.moedasQuant-1);
		while (x1==x2);
		if (pop[x1].qualidade > pop[x2].qualidade)		// Problema de maximizacao
			parents[i] = pop[x1];
		else
			parents[i] = pop[x2];
	}
}

// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament_geral(pchrom pop, struct info d, pchrom parents)
{
	int i, j, k, sair, best, *pos;

	pos = malloc(d.tsize*sizeof(int));
	// Realiza popsize torneios
	for(i=0; i<d.popTam;i++)
	{
	    // Seleciona tsize soluções diferentes para entrarem em torneio de seleção
		for(j=0; j<d.tsize; j++)
        {
            do
            {
                pos[j] = random_l_h(0, d.popTam-1);
                // Verifica se a nova posição escolhida é igual a alguma das outras posições escolhidas
                sair = 0;
                for (k=0; k<j; k++)
                {
                    if (pos[k]==pos[j])
                        sair = 1;
                }
            }
            while (sair);
            // Guarda a posição da melhor solução de todas as que entraram em torneio
            if (j==0 || pop[pos[j]].valido > pop[pos[best]].valido)		// Problema de maximizacao
                best = j;
        }
        parents[i] = pop[pos[best]];
	}
	free(pos);
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void genetic_operators(pchrom parents, struct info d, pchrom offspring, int mat[], char metodo2[], char metodo3[])
{
	if (!strcmp(metodo2, "C")) {
		// Recombinação com um ponto de corte
		crossover(parents, d, offspring);
	}
	else if (!strcmp(metodo2, "R2P")) {
		// Recombinação com dois pontos de corte
		recombinacao_dois_pontos_corte(parents, d, offspring);
	}
	else if (!strcmp(metodo2, "RU")) {
		// Recombinação uniforme
		recombinacao_uniforme(parents, d, offspring);
	}
	else {
		printf("Valor do Metodo de Recombinacao invalido!\n");
		exit(1);
	}

	if (!strcmp(metodo3, "MB")) {
		// Mutação binária
		mutation(offspring, d, mat);
	}
	else if (!strcmp(metodo3, "MT")) {
		// Mutação por troca
		mutacao_por_troca(offspring, d);
	}
	else {
		printf("Valor do Metodo de Mutacao invalido!\n");
		exit(1);
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação com um ponto de corte
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void crossover(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point;

	for (i=0; i<d.moedasQuant; i+=2)
	{
		if (rand_01() < d.pr)
		{
			point = random_l_h(0, d.moedasQuant-1);
			for (j=0; j<point; j++)
			{
				offspring[i].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
				offspring[i + 1].tipoMoedasQuant[j] = parents[i + 1].tipoMoedasQuant[j];
			}
			for (j=point; j<d.moedasQuant; j++)
			{
				offspring[i].tipoMoedasQuant[j] = parents[i+1].tipoMoedasQuant[j];
				offspring[i+1].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação com dois pontos de corte
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void recombinacao_dois_pontos_corte(pchrom parents, struct info d, pchrom offspring)
{
	int i, j, point1, point2;

	for (i=0; i<d.moedasQuant; i+=2)
	{
		if (rand_01() < d.pr)
		{
			point1 = random_l_h(0, d.moedasQuant-2);
			point2 = random_l_h(point1+1, d.moedasQuant-1);
			for (j=0; j<point1; j++)
			{
				offspring[i].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
				offspring[i+1].tipoMoedasQuant[j] = parents[i+1].tipoMoedasQuant[j];
			}
			for (j=point1; j<point2; j++)
			{
				offspring[i].tipoMoedasQuant[j]= parents[i+1].tipoMoedasQuant[j];
				offspring[i+1].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
			}
			for (j=point2; j<d.moedasQuant; j++)
			{
				offspring[i].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
				offspring[i+1].tipoMoedasQuant[j] = parents[i+1].tipoMoedasQuant[j];
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Preenche o vector descendentes com o resultado da operação de recombinação uniforme
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)
void recombinacao_uniforme(pchrom parents, struct info d, pchrom offspring)
{
	int i, j;

	for(i=0; i<d.popTam; i+=2)
	{
		if(rand_01() < d.pr)
		{
			for(j=0; j<d.moedasQuant; j++)
			{
                if (flip() == 1)
                {
                    offspring[i].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
                    offspring[i+1].tipoMoedasQuant[j] = parents[i+1].tipoMoedasQuant[j];
                }
                else
                {
                    offspring[i].tipoMoedasQuant[j] = parents[i+1].tipoMoedasQuant[j];
                    offspring[i+1].tipoMoedasQuant[j] = parents[i].tipoMoedasQuant[j];
                }
			}
		}
		else
		{
			offspring[i] = parents[i];
			offspring[i+1] = parents[i+1];
		}
	}
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, struct info d, int mat[])
{
	int i, j, quantidadeRest;

	quantidadeRest = d.quantidade;

	for (i = 0; i < d.popTam; i++) {
		for (j = 0; j < d.moedasQuant; j++) {
			if (rand_01() < d.pm) {
				for (i = 0; i < d.popTam; i++) {
					for (j = 0; j < d.moedasQuant; j++) {
						offspring[i].tipoMoedasQuant[j] = aleatorio(d, mat[j], &quantidadeRest);
					}
				}
			}
		}
	}
}

// Mutação por troca
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutacao_por_troca(pchrom offspring, struct info d)
{
	int i, pos1, pos2, aux;

	for (i=0; i<d.popTam; i++)
        if (rand_01() < d.pm)
        {
            do
                pos1 = random_l_h(0, d.moedasQuant-1);
            while (offspring[i].tipoMoedasQuant[pos1] == 1);
            do
                pos2 = random_l_h(0, d.moedasQuant-1);
            while (offspring[i].tipoMoedasQuant[pos2] == 0);
            aux = offspring[i].tipoMoedasQuant[pos1];
            offspring[i].tipoMoedasQuant[pos1] = offspring[i].tipoMoedasQuant[pos2];
            offspring[i].tipoMoedasQuant[pos2] = aux;
        }
}

// Trepa-colinas
// Parâmetros de entrada: 
int trepa_colinas(pchrom pop, struct info d, int mat[]) 
{
	int *nova_sol, custo, custo_viz, i;

	nova_sol = malloc(sizeof(int)*d.moedasQuant);
	if (nova_sol == NULL) {
		printf("Erro na alocacao de memoria");
		exit(1);
	}

	custo = calcula_fit(pop->tipoMoedasQuant, mat, d.quantidade);
	for (i = 0; i < 100; i++) {
		// Gera vizinho
		gera_vizinho(pop->tipoMoedasQuant, nova_sol, d);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, d.moedasQuant);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
		if (custo_viz <= custo && avalia_valor(nova_sol, mat, d)) {
			substitui(pop->tipoMoedasQuant, nova_sol, d.moedasQuant);
			custo = custo_viz;
		}
	}
	free(nova_sol);
	return custo;
}

int calcula_fit(int a[], int *mat, int coins)
{
	int total = 0;

	for (int i = 0; i < coins; i++)
		total += a[i];
	return total;
}

void gera_vizinho(int a[], int b[], struct info d)
{
	int i, p1, p2, n;

	n = d.moedasQuant;

	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}
	p1 = random_l_h(0, d.moedasQuant- 1);
	p2 = p1 + 3;
	b[p1] = b[p1] - 10;
	b[p2]++;
}

void substitui(int a[], int b[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		a[i] = b[i];
}

int avalia_valor(int a[], int *mat, struct info d) {
	int k = 0;
	int sum = 0;
	for (k = 0; k < d.moedasQuant; k++) {
		if (a[k] >= 0)
			sum += a[k] * mat[k];
		else return 0;
	}
	if (sum == d.quantidade)
		return 1;



	return 0;
}