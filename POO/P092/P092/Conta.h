#include "Pessoa.h"

class Conta {
	Pessoa const &titular;
	int saldo;
public:
	Conta(Pessoa &p);
	void variarSaldo(int varia);
	int getSaldo();
	Pessoa getTitular();
	~Conta();
};

