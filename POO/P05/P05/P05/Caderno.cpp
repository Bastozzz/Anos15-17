#include "Caderno.h"


using namespace std;

Caderno::Caderno(string marca, string cor, int paginas, int alt, int larg):marca(marca), cor(cor), paginas(paginas), alt(alt), larg(larg) {
	texto += "PAG 1: \n";
}

void Caderno::abrir(){
	aberto = true;
}

void Caderno::escreve(string texto) {
	for (int i = 0; i < texto.size(); i++) {
		if (i % 49 == 0 && i != 0) {
			this->texto += '\n';
			lAtual++;
		}
		if (lAtual == alt) viraPagina();
			
		this->texto += texto[i];
	}
	this->texto += " \n";
	lAtual++;
	if (lAtual == alt) viraPagina();
}

void Caderno::viraPagina(){
	fAtual += 1;
	texto += "\nPAG " + to_string(fAtual) + ": \n";
	lAtual = 1;
}

void Caderno::setLocal(string local) {
	this->local = local + '\n';
}

string Caderno::getMarca(){
	return marca + '\n';
}

string Caderno::getLocal() {
	return local + '\n';
}

string Caderno::getCor() {
	return cor + '\n';
}

string Caderno::getConteudo() {
	return texto + '\n';
}

int Caderno::getPalavras() {
	unsigned int espacos = 0;

	for (int i = 0; i < texto.size(); i++) {
		if (texto[i] == ' ') espacos++;
	}

	espacos -= fAtual * 2;

	return espacos;
}

string Caderno::getDescTxt() const {
	ostringstream os;

	os << "Marca: " << marca << "\nCor: " << cor << "\nDim: " << 
		larg << "\nFolhas: " << paginas << "\nLocal: " << local << 
		"\nConteudo: " << texto << endl;

	return os.str();
}


Caderno::~Caderno() {}
