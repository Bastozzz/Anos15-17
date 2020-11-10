#include <iostream>
#include <string>
#include <sstream>

#pragma once

using namespace std;
class Caderno {
private:
	const string marca;
	const string cor;
	const int paginas, alt, larg;
	string local;
	string texto;
	int fAtual = 1;
	int lAtual = 1;
	bool aberto = false;


public:
	Caderno(string marca, string cor, int paginas, int alt, int larg);

	void abrir();

	void escreve(string texto);

	void viraPagina();

	void setLocal(string local);

	string getMarca();

	string getLocal();

	string getCor();

	string getConteudo();

	int getPalavras();

	string getDescTxt() const;

	~Caderno();
};

