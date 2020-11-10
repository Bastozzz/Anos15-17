#include<sstream>
using namespace std;

#include "Batata.h"
#include "Tacho.h"
#include "Pure.h"

Batata::Batata(int quant):Ingrediente("Batata", quant) {
}
Ingrediente *   Batata::reageEntradaNoTacho( Tacho * tacho){
 //   // nao acontece nade de especial se a temperatura for inferior a 50
 //   if (tacho->getTemperatura() < 50){
 //       return nullptr;
 //   }
 //   // Caso a temperatura atinja esse limite
	//setAEliminar(true);
 //   // a batata desaparece (remove-se do tacho, 
 //   // transformando-se no ingrediente Pure, com 80% 
 //   // dos gramas que a batata tinha (o resto evaporou-se).
 //   return new Pure(static_cast<int>(0.8 * getQuantidade()));
	return reageMudancaTemp(tacho);
}
Ingrediente *   Batata::reageMudancaTemp( Tacho * tacho){
    // nao acontece nade de especial se a temperatura for inferior a 50
    if (tacho->getTemperatura() < 50){
        return nullptr;
    }
    // Caso a temperatura atinja esse limite
	setAEliminar(true);
    // a batata desaparece (remove-se do tacho, 
    // transformando-se no ingrediente Pure, com 80% 
    // dos gramas que a batata tinha (o resto evaporou-se).
	return new Pure(static_cast<int>(0.8 * getQuantidade()));
}
Ingrediente * Batata::duplica()const{
    return new Batata(*this);
}
