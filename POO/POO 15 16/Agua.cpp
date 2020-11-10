#include<sstream>
using namespace std;

#include "Agua.h"
#include "Tacho.h"

Agua::Agua(int quant):Ingrediente("Agua", quant) {
}
Ingrediente *   Agua::reageEntradaNoTacho( Tacho * tacho){
    // transfere os seus gramas para o primeiro ingrediente 
    // que tiver o nome agua
    Ingrediente * p = tacho->pesquisaPrimeiroIngComNome("Agua");
    if (p != nullptr && p != this){
        p->acrescentaQuantidade( getQuantidade());
        // e simplesmente desaparece
		setAEliminar(true);
    }
	return nullptr;
}
Ingrediente *   Agua::reageMudancaTemp( Tacho * tacho){
	//Quando o tacho atinge 100 graus, a agua evapora(e removida, desaparecendo)
    if(tacho->getTemperatura() >= 100){
		setAEliminar(true);
    }
	return nullptr;
}

Ingrediente * Agua::duplica()const{
    return new Agua(*this);
}