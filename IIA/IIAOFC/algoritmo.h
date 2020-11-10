#define MAX_OBJ 1000		// Numero maximo de objectos

// Estrutura para armazenar parametros
struct info
{
	// Tamanho da popula��o
	int popTam;
    // Quantidade de moedas
    int moedasQuant;
    // Quantidade a atingir em moedas
    int quantidade;
	// Probabilidade de muta��o
	float pm;
	// Probabilidade de recombina��o
	float pr;
	// Tamanho do torneio para sele��o do pai da pr�xima gera��o
	int tsize;
	// Constante para avalia��o com penaliza��o
	float ro;
	// N�mero de gera��es
	int numGenerations;
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Quantidade de moedas aleat�rias de cada tipo
    int tipoMoedasQuant[MAX_OBJ];
	// Diferen�a entre o n�mero de moedas propostas e as atuais
	int qualidade;
	// 1 se for uma solu��o v�lida e 0 se n�o for
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