#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Leitura do ficheiro de input
// Par�metros de entrada: Nome do ficheiro, nome, N�mero de v�rtices, n, N�mero de itera��es, iter
// Par�metros de sa�da: Matriz de adjac�ncias, p
int* init_dados(char *nome, int *n, int *iter) {
	int     *mat, *q;
	int     arestas, e1, e2;
	int     size = 1024, pos;
	int     vert;
    int     c;
    int     a;
	char    *buffer = (char *)malloc(size);
	char    palavra[10];

    FILE *f = fopen(nome, "r");
    if(f) {
      do { // read all lines in file
        pos = 0;
        do{ // read one line
          c = fgetc(f);
          if(c != EOF) buffer[pos++] = (char)c;
          if(pos >= size - 1) { // increase buffer length - leave room for 0
            size *=2;
            buffer = (char*)realloc(buffer, size);
          }
        }while(c != EOF && c != '\n');
        buffer[pos] = 0;
        // line is now in buffer
        if(buffer[0] == 'p') {
            sscanf(buffer, "%c %s %d %d", &a, palavra, &vert, &arestas);

            *n = vert;

            mat = malloc(sizeof(int)*(*n)*(*n));\

            if (!mat)
            {
                printf("Erro na alocacao de memoria\n");
                exit(1);
            }

            q = mat;

            for(int i = 0; i < *n; ++i) {
                for(int j = 0; j < *n; ++j) {
                    q[i*vert + j] = 0;
                }
            }
        }

        if(buffer[0] == 'e') {
            sscanf(buffer, "%c %d %d", &a, &e1, &e2);

            e1--;
            e2--;

            q[e1*vert + e2] = 1;
            q[e2*vert + e1] = 1;
        }
      } while(c != EOF);
      fclose(f);
    }
    free(buffer);

	// Devolve a matriz de adjac�ncias
	return mat;
}

// Gera a solu��o inicial
// Par�metros de entrada: Solu��o, sol, N�mero de vertices, v
void gera_sol_inicial(int *sol, int v)
{
	for(int i = 0; i < v; i++)
	{
		float n = rand_01();

	    if(n < 0.5) *(sol + i) = 0;
	    else *(sol + i) = 1;
	}
}

// Escreve solu��o no ecr�
// Par�metros de entrada: Solu��o, sol, N�mero de vertices, vert
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nConjunto: ");
	for (i = 0; i < vert; i++)
		if(sol[i] == 1)
			printf(" %d", i + 1);

}

// copia vector b para a (tamanho n)
// Par�metros de entrada: Solu��o que ser� substitu�da, a, Solu��o que ir� substituir, b, N�mero de vertices, n
void substitui(int a[], int b[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        a[i] = b[i];
}

// Inicializa o gerador de n�meros aleat�rios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Gera um valor inteiro aleat�rio entre min e max
// Par�metros de entrada: Valor inferior do intervalo, min, Valor superior do intervalo, max
// Par�metros de sa�da: Valor aleat�rio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max - min + 1);
}

// Gera um valor inteiro aleat�rio entre 0 e 1
// Par�metros de sa�da: Valor aleat�rio entre 0 e 1
float rand_01()
{
	return ((float)rand()) / RAND_MAX;
}
