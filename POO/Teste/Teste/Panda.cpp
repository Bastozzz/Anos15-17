#include "Panda.h"

Panda::Panda(int idade, string pais, string especie) : idade(idade), pais(pais), especie(especie) {
	this->nPandas++;
}

int Panda::quantosExistem() {
	return nPandas;
}

string Panda::getAsString() {
	ostringstream oss;

	oss << "Especie: " << especie << " Origem: " << pais << " Idade: " << idade << endl;

	return oss.str();
}

Panda::~Panda()
{
}

int Panda::nPandas = 0;
