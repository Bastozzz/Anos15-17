#define MAX_OBJ 1000		// Numero maximo de objectos

// Estrutura para armazenar parametros
struct info
{
	// Tamanho da população
	int popTam;
    // Quantidade de moedas
    int moedasQuant;
    // Quantidade a atingir em moedas
    int quantidade;
	// Probabilidade de mutação
	float pm;
	// Probabilidade de recombinação
	float pr;
	// Tamanho do torneio para seleção do pai da próxima geração
	int tsize;
	// Constante para avaliação com penalização
	float ro;
	// Número de gerações
	int numGenerations;
};

// Individuo (solução)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Quantidade de moedas aleatórias de cada tipo
    int tipoMoedasQuant[MAX_OBJ];
	// Diferença entre o número de moedas propostas e as atuais
	int qualidade;
	// 1 se for uma solução válida e 0 se não for
	int valido;
};

void tournament(pchrom pop, struct info d, pchrom parents);

void genetic_operators(pchrom parents, struct info d, pchrom offspring, int mat[], char metodo2[], char metodo3[]);

void crossover(pchrom parents, struct info d, pchrom offspring);

void mutation(pchrom offspring, struct info d, int mat[]);

void recombinacao_dois_pontos_corte(pchrom parents, struct info d, pchrom offspring);

void recombinacao_uniforme(pchrom parents, struct info d, pchrom offspring);

void mutacao_por_troca(pchrom offspring, struct info d);

int trepa_colinas(pchrom pop, struct info d, int mat[]);

int calcula_fit(int a[], int *mat, int coins);

void gera_vizinho(int a[], int b[], struct info d);

void substitui(int a[], int b[], int n);

int avalia_valor(int a[], int *mat, struct info d);