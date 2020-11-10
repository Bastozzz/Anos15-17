#include "Livro.h"



Livro::Livro(string nome, string autor) : nome(nome), autor(autor){}

string Livro::getNome()
{
	return nome;
}

string Livro::getAutor()
{
	return autor;
}

Livro::~Livro(){}
