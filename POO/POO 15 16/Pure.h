#ifndef PURE_H
#define PURE_H

#include<string>
using namespace std;

#include "Ingrediente.h"

class Pure : public Ingrediente {
public:
	Pure(int quant);
	virtual Ingrediente *  reageEntradaNoTacho(Tacho * tacho);
	virtual Ingrediente *  reageMudancaTemp(Tacho * tacho);
	virtual Ingrediente * duplica()const;
};

#endif