#pragma once
#include <string>
#include "Tarifario.h"

using namespace std;
class Cartao
{
	string numero;
	float saldo;
	Tarifario *tarifario;
public:
	Cartao();
	~Cartao();
};

