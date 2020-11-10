void init_rand();

struct info init_data(char *filename, int mat[]);

int aleatorio(struct info d, int valorMoeda, int *quantidadeRest);

pchrom init_pop(struct info d, int mat[]);

chrom get_best(pchrom, struct info, chrom);

int random_l_h(int min, int max);

void write_best(chrom x, struct info d, int mat[]);

float rand_01();

int flip();