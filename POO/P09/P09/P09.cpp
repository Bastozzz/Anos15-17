#include <iostream>
#include "Aviso.h"

using namespace std;
int main() {
	Prego p1(2, 4);
	Prego p2(10, 4);

	Aviso a1("FECHADO", &p1);
	Aviso a2("FORA DE SERVICO", &p1);

	cout << a1.getLocal() << endl;

	p1.mudaDeSitio(4, 5);
	a1.mudaAviso(&p2);

	cout << a1.getLocal() << endl;
	cout << a2.getLocal() << endl;

	return 0;
}