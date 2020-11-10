#include <iostream>
#include "Livro.h"

using namespace std;
class Disciplina
{
	Livro livro;
	string ficha;
public:
	Disciplina(Livro livro, string ficha);
	string getAutorLivro();
	string getNomeLivro();
	string getFicha();
	~Disciplina();
};

