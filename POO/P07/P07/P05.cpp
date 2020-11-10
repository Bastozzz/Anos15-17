#include <iostream>
#include "Ponto.h"

int main() {
	Ponto a(2, 1), b(4, -3);
	const Ponto c(2, 1);

	cout << a.getx() << " " << a.gety() << endl;
	cout << b.getAsString() << endl;

	cout << a.getDistancia(b) << endl;
	a.mover(2, 3).mover(3, -2);

	getchar();
	return 0;
}