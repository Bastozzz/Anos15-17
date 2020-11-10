#include <string>
#include "Aquario.h"

using namespace std;
class Peixe {
	string nome;
	string cor;
	int peso, id;
	static int conta;
	Aquario *p;
	bool vivo;
public:
	Peixe(string a, string b = "Dourado");
	void comer(int qtd);
	virtual ~Peixe();
};