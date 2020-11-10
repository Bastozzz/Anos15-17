#include <iostream>
#include <string>
#include "Caderno.h"

using namespace std;
int main() {
	Caderno a("Bloco", "Verde", 50, 50, 25);

	a.setLocal("ISEC");
	a.abrir();
	a.escreve("Ola, mundo!");
	a.escreve("Esta frase tem cinco palavras");
	a.viraPagina();
	a.escreve("1 de Outubro");
	cout << a.getDescTxt() << a.getPalavras() << " palavras escritas" << endl;

	return 0;
}

