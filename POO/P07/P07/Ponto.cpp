#include "Ponto.h"
#include <sstream>



Ponto::Ponto(int x, int y) : x(x), y(y) {}

int Ponto::getx() {
	return x;
}

int Ponto::gety() {
	return y;
}

int Ponto::getDistancia(Ponto a) {
	return sqrt((((x - a.getx()) * (x - a.getx())) + ((y - a.gety()) * (y - a.gety()))));
}

Ponto & Ponto::mover(int newx, int newy) {
	x += newx;
	y += newy;
	return *this;
}


string Ponto::getAsString() const {
	ostringstream os;
	os << "(" << x << ", " << y << ")";
	return os.str();
}

Ponto::~Ponto() {

}
