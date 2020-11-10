#include "Peixe.h"




Peixe::Peixe(string a, string b) : nome(a), cor(b), peso(10), id(conta++), p(nullptr), vivo(true) {}

void Peixe::comer(int qtd) {
	if (vivo) peso += qtd;

	if (peso >= 50) {

	}
}

Peixe::~Peixe() {}