#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"

// Inicialização do gerador de números aleatórios
void init_rand() {
	srand((unsigned)time(NULL));
}

// Leitura dos parâmetros e dos dados do problema
// Parâmetros de entrada: Nome do ficheiro e matriz a preencher com os dados dos objectos (moedas)
// Parâmetros de saída: Devolve a estrutura com os parâmetros
struct info init_data(char *filename, int mat[]) {
	struct info x;
	FILE *f;
	int i;
	float temp;

	f = fopen(filename, "rt");
	if (!f)
	{
		printf("Ficheiro nao encontrado.\n");
		exit(1);
	}
	// Leitura dos parâmetros do problema
	fscanf(f, " %d", &x.moedasQuant);
	fscanf(f, " %f", &temp);
	x.quantidade = temp * 100;
	x.numGenerations = 50;
	x.popTam = 50;
	x.pm = 0.025;
	x.pr = 0.25;
	x.tsize = 3;
	x.ro = 2.5;
	for (i = 0; i < x.moedasQuant; i++) {
		fscanf(f, " %f", &temp);
		mat[i] = temp * 100;
		printf("%d\n", mat[i]);
	}

	fclose(f);
	// Devolve a estrutura com os parâmetros
	return x;
}

// Simula o número de moedas de cada espécie inicialmente, retornando um valor inteiro aleatório
int aleatorio(struct info d, int valorMoeda, int *quantidadeRest) {
	int random, valorAtual;

	random = rand() % d.quantidade / valorMoeda;
	valorAtual = random * valorMoeda;

	while (valorAtual > *quantidadeRest) {
		random = rand() % d.quantidade / valorMoeda;
		valorAtual = random * valorMoeda;
	}

	*quantidadeRest -= valorAtual;

	return random;
}

// Criacao da populacao inicial. O vector e alocado dinamicamente
// Parâmetro de entrada: Estrutura com parâmetros do problema
// Parâmetro de saída: Preenche da estrutura da população apenas o vector binário com os elementos que estão dentro ou fora da mochila
pchrom init_pop(struct info d, int mat[]) {
	int i, j, quantidadeRest;
	pchrom  indiv;

	quantidadeRest = d.quantidade;

	indiv = malloc(sizeof(chrom)*d.popTam);
	if (indiv == NULL) {
		printf("Erro na alocacao de memoria!\n");
		exit(1);
	}
	printf("For!\n");
	for (i = 0; i < d.popTam; i++) {
		for (j = 0; j < d.moedasQuant; j++) {
			//printf("%d ------ %d\n", i, j);
			//indiv[i].tipoMoedasQuant[j] = 0;
			indiv[i].tipoMoedasQuant[j] = aleatorio(d, mat[j], &quantidadeRest);
			//printf("%d\n", indiv[i].tipoMoedasQuant[j]);
		}
	}
	printf("For!\n");
	return indiv;
}

// Actualiza a melhor solução encontrada
// Parâmetro de entrada: populacao actual (pop), estrutura com parâmetros (d) e a melhor solucao encontrada até a geraçãoo imediatamente anterior (best)
// Parâmetro de saída: a melhor solucao encontrada até a geração actual
chrom get_best(pchrom pop, struct info d, chrom best) {
	int i;

	for (i = 0; i<d.moedasQuant; i++)
	{
		if (best.qualidade > pop[i].qualidade)
			best = pop[i];
	}
	return best;
}

// Devolve um valor inteiro distribuido uniformemente entre min e max
int random_l_h(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Escreve uma solução na consola
// Parâmetro de entrada: populacao actual (pop) e estrutura com parâmetros (d)
void write_best(chrom x, struct info d, int mat[]) {
	int i;
	float moeda;

	printf("\nNumero de moedas utilizadas: %d\n", x.qualidade);
	for (i = 0; i < d.moedasQuant; i++) {
		moeda = mat[i];
		moeda = moeda / 100;
		printf("Quantidade de moedas de %.2f: %d\n", moeda, x.tipoMoedasQuant[i]);
	}
}

// Devolve um valor real distribuido uniformemente entre 0 e 1
float rand_01() {
	return ((float)rand()) / RAND_MAX;
}

// Simula o lançamento de uma moeda, retornando o valor 0 ou 1
int flip()
{
	if ((((float)rand()) / RAND_MAX) < 0.5)
		return 0;
	else
		return 1;
}
