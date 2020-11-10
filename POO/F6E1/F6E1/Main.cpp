#include <iostream>
#include "Aquario.h"

using namespace std;
int main() {
	Peixe *p1 = new Peixe("Nemo", "Vermelho");
	Peixe *p2 = new Peixe("Dora");

	Aquario a("ISEC");

	a.addPeixe(p1);
	a.addPeixe(p2);

	a.alimenta(25);

	cout << a << endl;
}