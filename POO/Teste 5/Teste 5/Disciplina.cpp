#include "Disciplina.h"



using namespace std;
Disciplina::Disciplina(Livro livro, string ficha) : livro(livro), ficha(ficha){}

string Disciplina::getAutorLivro()
{
	return livro.getAutor();
}

string Disciplina::getNomeLivro()
{
	return livro.getNome();
}

string Disciplina::getFicha()
{
	return ficha;
}

Disciplina::~Disciplina()
{
	cout << "FUI!" << endl;
}
