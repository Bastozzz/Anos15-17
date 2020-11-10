#include "Aviso.h"


Aviso::Aviso(string a, Prego *b): txt(a), p(b) {}

void Aviso::mudaAviso(Prego *np) {
	p = np;
}

string Aviso::getLocal(){
	return p->getAsString();
}

Aviso::~Aviso(){}
