#include "Pure.h"

Pure::Pure(int quant) :Ingrediente("Pure", quant) {
}
Ingrediente *  Pure::reageEntradaNoTacho(Tacho * tacho) {
	return nullptr;
}
Ingrediente *  Pure::reageMudancaTemp(Tacho * tacho) {
	return nullptr;
}
Ingrediente * Pure::duplica()const {
	return new Pure(*this);
}

