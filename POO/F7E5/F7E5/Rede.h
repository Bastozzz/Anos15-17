#pragma once
#include "Tarifario.h"
#include "Cartao.h"
#include <vector>

using namespace std;
class Rede
{
	vector<Cartao*> vc;
	vector<Tarifario*> vt;
public:
	Rede(initializer_list<Tarifario*> a);
	~Rede();
};

