#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "moedas.h"
#include "file_func.h"

#define DEFAULT_RUNS 100

int main() {
	char nomefich[20];
	moeda coins;
	int runs = DEFAULT_RUNS;

	FILE* f;

	printf("Nome do ficheiro:");
	scanf("%s", &nomefich);

	if (!(f = fopen(nomefich, "rt"))) {
		perror("Erro no fopen()");
		return EXIT_FAILURE;
	}
	coins = lefich(f);
	close(f);

	printf("Numero de iteracoes (0 para default):");
	scanf("%d", &runs);

	if(runs == 0) runs = DEFAULT_RUNS;

	return EXIT_SUCCESS;
}

moeda lefich(FILE* f) {
	moeda tmp;
	int i = 0;

	fscanf(f, "%d %f ", &tmp.nmax, &tmp.objetivo);

	while (!feof(f)) {
        fscanf(f, "%f", &tmp.moedas[i]);
        i++;
	}

	return tmp;
}
