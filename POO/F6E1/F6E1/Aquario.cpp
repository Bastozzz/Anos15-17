#include "Aquario.h"

Aquario::Aquario(string a) : nome(a) {}

void Aquario::alimenta(int alimento) {
	for (Peixe *p : v) {
		p->comer(alimento);
	}
}

void Aquario::addPeixe(Peixe * p) {
	v.push_back(p);
}

Aquario::~Aquario() {}
