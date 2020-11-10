#ifndef BATATA_H
#define BATATA_H

#include<string>
using namespace std;

#include "Ingrediente.h"

class Batata : public Ingrediente {
public:
    Batata(int quant);
    Ingrediente *   reageEntradaNoTacho( Tacho * tacho) override;
    Ingrediente *   reageMudancaTemp( Tacho * tacho)override;
    Ingrediente * duplica()const override;
};

#endif /* BATATA_H */

