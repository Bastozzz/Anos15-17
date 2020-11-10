#include <iostream>
#include "Panda.h"

using namespace std;

class Produto {
	string nome;
	int preco;
public:
	Produto(string s, int pr) {
		nome = s;
		preco = pr;
	}
};

class Encomenda {
	Produto prod;
	int quantidade;
public:
	Encomenda(string nome, int preco, int quant): prod(nome, preco){
		quantidade = quant;
	}
};



int main() {
	cout << "Existem: " << Panda::quantosExistem() << endl;
	{
		Panda a(10, "Portugal");
		Panda b(12);
		cout << b.getAsString();
		cout << "Existem: " << Panda::quantosExistem() << endl;
	}
	cout << "Existem: " << Panda::quantosExistem();

	getchar();
	return 0;
}