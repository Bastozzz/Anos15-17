#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "moedas.h"


FILE* abrefich(char nomefich[]);

moeda lefich(FILE* f);

int main() {
	char nomefich[20];
	moeda coins;

	FILE* f;

	printf("Nome do ficheiro:");
	scanf("%s", &nomefich);

	if((f = abrefich(nomefich)) == NULL)
		return EXIT_FAILURE;

	coins = lefich(f);

	printf("%d %f %d %d %d", coins.nmax, coins.objetivo, coins.moedas[0], coins.moedas[1], coins.moedas[2]);
}

FILE* abrefich(char nomefich[]) {
	FILE* f;
	if ((f = fopen(nomefich, "rt")) == NULL)
		printf("Erro ao abrir o ficheiro!");
	return f;
}

moeda lefich(FILE* f) {
	moeda tmp;
	int i = 0;
	fscanf(f, "%d %f", &tmp.nmax, &tmp.objetivo);
	while (fscanf(f, "%f", &tmp.moedas[i])) i++;
	return tmp;
}