#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  100
#define PROBGERAVIZ     1.0

// Calcula a qualidade de uma solução com reparação de acordo com uma heirística sofrega
// Parâmetros de entrada: solução (sol), capacidade da mochila (d), matriz com dados do problema (mat) e numero de objectos (v)
// Parâmetros de saída: qualidade da solução (se a capacidade for excedida devolve 0)
int eval_individual_reparado(int sol[], struct info d, int mat[], int *v)
{
	int i, pos, soma_quantidade, soma_moedas, acrescento, menor;

	soma_quantidade = soma_moedas = acrescento = pos = 0;
	// Percorre todos os objectos
	for (i = 0; i < d.moedasQuant; i++) {
		// Actualiza o peso total
		soma_quantidade += (sol[i] * mat[i]);
		if (i == 0) {
			menor = mat[i];
		}
		else if (menor > mat[i]) {
			menor = mat[i];
			pos = i;
		}
		soma_moedas += sol[i];
	}
	// Processo de reparacao
    while (soma_quantidade < d.quantidade) {
		sol[pos]++;
		soma_quantidade += menor;
		soma_moedas++;
    }
	if (soma_quantidade == d.quantidade) {
		*v = 1;
	}
	else {
		*v = 0;
	}
	return soma_moedas;
}

// Avaliacao da população
// Parâmetros de entrada: populacao (pop), estrutura com parametros (d) e matriz com dados do problema (mat)
// Parâmetros de saída: Preenche pop com os valores de fitness e de validade para cada solução
void evaluate(pchrom pop, struct info d, int mat[])
{
	int i;

	for (i = 0; i < d.moedasQuant; i++) {
		pop[i].qualidade = eval_individual_reparado(pop->tipoMoedasQuant, d, mat, &pop[i].valido);
	}
}
