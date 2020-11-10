#include "funcao.h"

// Calcula a qualidade de uma solu��o
// Par�metros de entrada: Solu��o actual, a, Matriz de adjac�ncias, mat, N�mero de v�rtices, vert
// Par�metros de sa�da: Custo, total - Neste caso, � o n�mero de liga��es que existem entre os v�rtices dos dois grupos
int valida_solucao(int a[], int *mat, int vert)
{
	int total = 0;
	int i, j;

	for (i = 0; i < vert; i++)
		if (a[i] == 0)
		{
			for (j = 0; j < vert; j++)
				if (a[j] == 1 && *(mat+i*vert+j) == 1)
				    total++;
		}
	return total;
}

int calcula_elementos(int a[], int vert) {
	int total = 0;

	for(int i = 0; i < vert; ++i) {
		if(a[i] == 1) total++;
	}

	return total;
}
