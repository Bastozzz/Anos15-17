#include "Banco.h"
#include <sstream>

using namespace std;

Banco::Banco(string nome) : nome(nome){}

void Banco::addConta(Conta conta) {
	v.push_back(conta);
}

bool Banco::deposito(int valor, int CC) {
	bool resultado = false;

	for (Conta &conta : v) {
		if (conta.getTitular().getCc() == CC) {
			conta.variarSaldo(valor);
			resultado = true;
		}
	}

	return resultado;
}

Conta * Banco::obterConta(int CC) {
	for (Conta &conta : v) {
		if (conta.getTitular().getCc() == CC) {
			return &conta;
		}
	}
	return nullptr;
}

void Banco::eliminaConta(int CC) {
	for (size_t i = 0; i < v.size(); i++) {
		if (v.at(i).getTitular().getCc() == CC) {
			v.erase(v.begin() + i);
			return;
		}
	}
}

string Banco::getNomes() {
	ostringstream os;
	for (Conta &conta : v) {
		os << conta.getTitular().getNome() << endl;
	}
	return os.str();
}

int Banco::getTotalDepositos() {
	int total = 0;

	for (Conta &conta : v) {
		total += conta.getSaldo();
	}

	return total;
}

Banco::~Banco()
{
}
