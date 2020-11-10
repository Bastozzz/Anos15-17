#include "Fracao.h"

using namespace std;
Fracao::Fracao(int x, int y) : num(x) {
	if (y == 0) den = 1;
	else den = y;
}

void Fracao::setNum(int x) {
	num = x;
}

void Fracao::setDen(int x) {
	if (x != 0) den = x;
}

Fracao& Fracao::operator*=(const Fracao& x) {
	*this = *this * x;

	return *this;
}

Fracao Fracao::operator++(int x) {
	Fracao a = *this;
	this->num += this->den;

	return a;
}

Fracao & Fracao::operator++() {
	this->num += this->den;

	return *this;
}

int Fracao::getNum() const {
	return num;
}

int Fracao::getDen() const {
	return den;
}

int Fracao::getRes() const {
	return num / den;
}

Fracao::~Fracao() {}

bool operator==(Fracao x, Fracao y) {
	return x.getRes() == y.getRes();
}

bool operator!=(Fracao x, Fracao y) {
	return !(x == y);
}

bool operator>=(Fracao x, Fracao y) {
	return x.getRes() >= y.getRes();
}

bool operator<=(Fracao x, Fracao y) {
	return x.getRes() <= y.getRes();
}

bool operator<(Fracao x, Fracao y) {
	return !(x >= y);
}

bool operator>(Fracao x, Fracao y) {
	return !(x <= y);
}

ostream & operator<<(ostream & os, const Fracao& x) {
	os << x.getNum() << "/" << x.getDen();

	return os;
}

Fracao operator*(Fracao x, Fracao y) {
	x.setNum(x.getNum() * y.getNum());
	x.setDen(x.getDen() * y.getDen());

	return x;
}

Fracao operator/(Fracao x, Fracao y) {
	x.setNum(x.getNum() * y.getDen());
	x.setDen(x.getDen() * y.getNum());

	return x;
}