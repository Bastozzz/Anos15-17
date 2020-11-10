#include "Prego.h"
#include <iostream>
#include <sstream>

using namespace std;
Prego::Prego(int a, int b): x(a), y(b) {
	cout << "A construir Prego em " << a << ", " << b << endl;
}

void Prego::mudaDeSitio(int nx, int ny) {
	x = nx;
	y = ny;
}

string Prego::getAsString() const{
	ostringstream os;
	os << "( " << x << ", " << y << ")";
	return os.str();
}

Prego::~Prego(){
	cout << "Destruir Prego: " << x << ", " << y << endl;
}
