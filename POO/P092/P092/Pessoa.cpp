#include "Pessoa.h"
#include <sstream>


Pessoa::Pessoa(string nome, int cc, int nif): nome(nome), cc(cc), nif(nif) {}

void Pessoa::setNome(string nnome) {
	nome = nnome;
}

string Pessoa::getNome() const {
	return nome;
}

int Pessoa::getCc() const {
	return cc;
}

int Pessoa::getNif() const {
	return nif;
}

string Pessoa::getAsString() const {
	ostringstream os;
	os << nome << ", " << cc << ", " << nif;
	return os.str();
}

Pessoa::~Pessoa(){}
