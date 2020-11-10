

#ifndef AGUA_H
#define AGUA_H
#include<string>
using namespace std;

#include "Ingrediente.h"



class Agua  : public Ingrediente{
public:
    Agua(int quant);
    Ingrediente *   reageEntradaNoTacho( Tacho * tacho) override;
    Ingrediente *   reageMudancaTemp( Tacho * tacho)override;
    Ingrediente * duplica()const override;
};

#endif /* AGUA_H */

