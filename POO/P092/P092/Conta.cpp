#include "Conta.h"
#include <iostream>



Conta::Conta(Pessoa &p): titular(p) {
	saldo = 0;
	cout << "Conta criada para " << titular.getNome() << ": " << saldo << endl;
}

void Conta::variarSaldo(int varia) {
	saldo += varia;
}

int Conta::getSaldo() {
	return saldo;
}

Pessoa Conta::getTitular() {
	return titular;
}


Conta::~Conta() {

}
