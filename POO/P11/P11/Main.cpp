#include <iostream>
#include "Fracao.h"

using namespace std;
int main() {
	Fracao a(4, 3), b(1, 2), c(2, 4);

	cout << (a == b) << endl;

	cout << (b != c) << endl;

	cout << (1 == b) << endl;

	getchar();
	return 0;
}