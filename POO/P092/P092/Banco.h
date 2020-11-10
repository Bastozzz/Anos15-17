#include <string>
#include <vector>
#include "Conta.h"

using namespace std;
class Banco {
	string nome;
	vector<Conta> v;
public:
	Banco(string nome);
	void addConta(Conta conta);
	bool deposito(int valor, int CC);
	Conta* obterConta(int CC);
	void eliminaConta(int CC);
	string getNomes();
	int getTotalDepositos();
	~Banco();
};

