#include <iostream>
#include "Banco.h"

using namespace std;
int main() {
	Pessoa p1("Ana Silva", 111, 222);
	Pessoa p2("Carlos Santos", 333, 444);
	Banco b1("CGD"), b2("BES");
	
	b1.addConta(Conta(p1));
	b1.addConta(Conta(p2));
	b2.addConta(Conta(p1));

	b1.deposito(100, 333);

	cout << b1.getNomes() << endl;
	cout << b1.getTotalDepositos() << endl;

	const Conta *p = b1.obterConta(333);

	b1.eliminaConta(111);

	cout << b1.getNomes() << endl;

	getchar();
	return 0;
}