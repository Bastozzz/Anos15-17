#include <iostream>

using namespace std;
class Fracao {
	int num, den;
public:
	Fracao(int x = 0, int y = 1);
	void setNum(int x);
	void setDen(int x);
	Fracao& operator*=(const Fracao& x);
	Fracao operator++(int x);
	Fracao& operator++();
	int getNum() const;
	int getDen() const;
	int getRes() const;
	~Fracao();
};

bool operator==(Fracao x, Fracao y);

bool operator!=(Fracao x, Fracao y);

bool operator>=(Fracao x, Fracao y);

bool operator<=(Fracao x, Fracao y);

bool operator>(Fracao x, Fracao y);

bool operator<(Fracao x, Fracao y);

ostream& operator<<(ostream& os, const Fracao& x);

Fracao operator*(Fracao x, Fracao y);

Fracao operator/(Fracao x, Fracao y);


