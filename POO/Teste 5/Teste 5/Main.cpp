#include "Disciplina.h"

using namespace std;
int main() {
	Livro a("C++ for Dummies", "Albert Johanson");
	Disciplina POO(a, "POO");

	cout << POO.getNomeLivro() << " " << POO.getAutorLivro() << " " << POO.getFicha() << endl;

	POO.~Disciplina();

	cout << a.getNome();

	getchar();
	return 0;
}